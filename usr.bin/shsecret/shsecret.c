/* shsecret.c - Secret sharing algorithm */
/* Written by David Madore <david.madore@ens.fr> */
/* 2000/06/19 - Public Domain */

/* This program implements a secret sharing algorithm.  In other
 * words, given a file (secret), it can produce N files of the same
 * size ("shares") such that knowing any M shares among N will be
 * sufficient to recover the secret (using this very program again)
 * whereas knowing less than M shares will yield _absolutely no
 * information_ on the secret, even with infinite computing power.
 * This program does both the sharing and the unsharing (it actually
 * does a little more than that).  N can be anywhere up to 255.  M can
 * be anywhere up to N. */

/* Features:
 * + Small is beautiful.
 * + Efficient (for small MN).
 * + No bignum arithmetic (only eight-bit calculations).
 * + Completely portable (only assumes input chars are eight-bit).
 * + No dynamic memory allocation whatsoever (roughly 70k static).
 * + Completely brain-dead command line syntax. */

/* How to use:
 * To share a secret:
   shsecret -secret.txt 1-/dev/urandom 2-/dev/urandom [...] \
      1+share1.dat 2+share2.dat 3+share3.dat [...]
   where the number of '-' command line arguments is M-1 and where the
   number of '+' command line arguments is N.
     If your system has no /dev/urandom-like random number generator,
   then write (cryptographically strong) random data in share1.dat,
   share2.dat and so on (M-1 of them), each one being the same size
   as secret.txt (at least) and run:
   shsecret -secret.txt 1-share1.dat 2-share2.dat [...] \
      M+shareM.dat [...]
   (that is, use a '-' for the first M-1 and a '+' for the following
   ones).  Then share1.dat through shareN.dat are the N shares.
 * To unshare a secret:
   shsecret 1-share1.dat 3-share3.dat 4-share4.dat [...] +secret.txt
   Enough shares must be given (i.e. at least M), but which are given
   is unimportant. */

/* Detailed instructions:
 * Syntax is "shsecret [point][+-][file] [...]"
 * Where [point] is an integer between 0 and 255 (if missing, counted
 * as 0; [+-] is either '+' for an output file or '-' for an input
 * file; and [file] is a file name.
 * This computes the so-called "Lagrange interpolating polynomial" on
 * the input files through the given input points and outputs its
 * values at the given output points in the given output files.  The
 * Lagrange interpolating polynomial, if defined by M input points, is
 * completely determined by its value at _any_ M points.
 * In particular, if shsecret is run with secret.txt as input file for
 * point 0 and M-1 sets of random data for points 1 to M-1, it will
 * create a Lagrange interpolating polynomial of degree M which is
 * random except that its value at 0 is given by secret.txt; its value
 * at any point other than 0 is random.  Given M such values, the
 * polynomial can be recovered, hence, in particular, its value at 0
 * (the secret). */

/* Concise mathematical details (you may skip this but read below):
 * We work in the Galois field F256 with 256 elements represented by
 * the integers from 0 to 255.  The two operations ("addition" and
 * "multiplication") of the field are the exclusive or and the Conway
 * multiplication.  Exclusive or can be defined (by induction) as
 *   a xor b = the smallest n not equal to a' xor b for a'<a
 *             nor to a xor b' for b'<b
 * Similarly, Conway multiplication can be defined as
 *   a conmul b = the smallest n not equal to
 *                (a' conmul b) xor (a' conmul b') xor (a conmul b')
 *                for some a'<a and b'<b
 * Note that 0 and 1 in the field are the true 0 and 1.
 * Note that the field has characteristic 2, so substraction is
 * precisely the same thing as addition (namely, exclusive or);
 * nevertheless I will write + and - as needed in what follows for
 * greater clarity.
 * Suppose zi are the output points and xj the input points (for
 * various values of i and j); suppose yj is the input data for input
 * point xj (i.e. one byte of the corresponding input file).  We wish
 * to compute the output data ti corresponding to zi.  The polynomial
 * (Conway) product of the (X-xk) for k not equal to j is equal to 0
 * at every xk except xj where it is not zero; we call in_cross[j] its
 * value at xj.  If we (Conway) divide the product of the (X-xk) by
 * in_cross[j] we get a polynomial which is 1 at xj and 0 at every
 * other xk: call it Pj.  The sum (i.e. XOR) of the yj Pj is the
 * Lagrange interpolating polynomial: it takes value yj at each xj.
 * So its value at zi is the sum of the yj Pj(zi).  Now Pj(zi) is the
 * product of the (zi-xk) for k not equal to j, divdided by
 * in_cross[j].  Call out_cross[i] the product of the (zi-xk) for
 * _every_ k.  Then Pj(zi) is out_cross[i] divided by the product of
 * (zi-xj) by in_cross[j].  This is expression is the horrible
 * conmul_tab[out_cross[i]][coninv_tab[conmul_tab[in_cross[j]]
 *     [out_points[i]^in_points[j]]]]
 * further down in this program (here out_points[i] is zi,
 * in_points[j] is xj and ^ is the XOR operation; and conmul_tab is
 * the table giving the Conway multiplication and coninv_tab is the
 * table giving the Conway inverse operation). */

/* Note: your secret sharing system will only be secure provided you
 * feed the program with _cryptographically secure random numbers_. */

/* Note: all input and output files are open simultaneously.  Your
 * system must have enough file descriptors. */

/* Speed estimation: circa 350kB/s on an Intel PIII-600 running Linux
 * with NM=30.  Speed decreases linearly in proportion with NM.  Thus
 * we have a theoretical speed of circa 10MB/s. */

/* Plea: although I put this file in the Public Domain, I would very
 * much appreciate getting credit if credit is due.  Thank you. */

#include <stdio.h>
#include <stdlib.h>

/* Multiplication table for the first 8 powers of two under Conway
 * multiplication.  DO NOT CHANGE THIS UNDER ANY CIRCUMSTANCES. */
static const unsigned char conmul_powtab[8][8] = {
  {   1,   2,   4,   8,  16,  32,  64, 128, },
  {   2,   3,   8,  12,  32,  48, 128, 192, },
  {   4,   8,   6,  11,  64, 128,  96, 176, },
  {   8,  12,  11,  13, 128, 192, 176, 208, },
  {  16,  32,  64, 128,  24,  44,  75, 141, },
  {  32,  48, 128, 192,  44,  52, 141, 198, },
  {  64, 128,  96, 176,  75, 141, 103, 185, },
  { 128, 192, 176, 208, 141, 198, 185, 222, },
};

/* Calculate a Conway product using the previous table. */
static unsigned char
calc_conmul (unsigned char a, unsigned char b)
{
  unsigned char n;
  int i, j;

  n = 0;
  for ( i=0 ; a>>i ; i++ )
    for ( j=0 ; b>>j ; j++ )
      if ( ((a>>i)&1) && ((b>>j)&1) )
	n ^= conmul_powtab[i][j];
  return n;
}

/* Multiplication table for the Conway product up to 255 (to be
 * computed) */
static unsigned char conmul_tab[256][256];

/* Compute the previous table. */
static void
fill_conmul_tab (void)
{
  int i, j;

  for ( i=0 ; i<256 ; i++ )
    for ( j=0 ; j<256 ; j++ )
      conmul_tab[i][j] = calc_conmul (i, j);
}

/* Inversion table for the Conway multiplication (to be computed) */
static unsigned char coninv_tab[256];

/* Compute the previous table. */
static void
fill_coninv_tab (void)
{
  int i, j;

  coninv_tab[0] = 0;  /* Meaningless */
  for ( i=1 ; i<256 ; i++ ) {
    for ( j=1 ; conmul_tab[i][j]!=1 ; j++ ) /* nothing */ ;
    coninv_tab[i] = j;
  }
}

/* Number of input points and output points */
int in_num;
int out_num;

/* Input and output points */
unsigned char in_points[256];
unsigned char out_points[256];

/* Product of the (xi-xj) with j not equal to i, where xi are input
 * points */
unsigned char in_cross[256];
/* Product of the (zi-xj) where zi are output points and xj are input
 * points */
unsigned char out_cross[256];

/* Compute the previous table. */
void
precalc (void)
{
  int i, j;
  unsigned char n;

  for ( i=0 ; i<in_num ; i++ )
    {
      n = 1;
      for ( j=0 ; j<in_num ; j++ )
	if ( j != i )
	  n = conmul_tab[n][in_points[i]^in_points[j]];
      in_cross[i] = n;
    }
  for ( i=0 ; i<out_num ; i++ )
    {
      n = 1;
      for ( j=0 ; j<in_num ; j++ )
	n = conmul_tab[n][out_points[i]^in_points[j]];
      out_cross[i] = n;
    }
}

/* Input and output values */
unsigned char in_data[256];
unsigned char out_data[256];

/* Process one byte from all input files */
void
do_point (void)
{
  int i, j;
  unsigned char n;

  for ( i=0 ; i<out_num ; i++ )
    {
      n = 0;
      if ( ! out_cross[i] ) /* Output point is an input point */
	{
	  for ( j=0 ; j<in_num ; j++ )
	    if ( out_points[i] == in_points[j] )
	      n = in_data[j];
	}
      else
	for ( j=0 ; j<in_num ; j++ )
	  n ^= conmul_tab[in_data[j]][conmul_tab[out_cross[i]][coninv_tab[conmul_tab[in_cross[j]][out_points[i]^in_points[j]]]]];
      out_data[i] = n;
    }
}

/* Input and output file names */
const char *in_fn[256];
const char *out_fn[256];

/* Input and output streams */
FILE *in_f[256];
FILE *out_f[256];

void
error (const char *errmsg)
{
  fprintf (stderr, "%s\n", errmsg);
  exit (EXIT_FAILURE);
}

int
main (int argc, const char *argv[])
{
  int k;

  fill_conmul_tab ();
  fill_coninv_tab ();
  in_num = 0;
  out_num = 0;
  /* Read command line arguments */
  for ( k=1 ; k<argc ; k++ )
    {
      int l, p;

      p = 0;
      for ( l=0 ; argv[k][l]>='0' && argv[k][l]<='9' ; l++ )
	{
	  p = p*10 + (argv[k][l]-'0');
	  if ( p >= 256 )
	    error ("Point value too large.");
	}
      if ( argv[k][l] == '-' )
	{
	  int m;

	  for ( m=0 ; m<in_num ; m++ )
	    if ( in_points[m] == p )
	      error ("Duplicate input point.");
	  in_points[in_num] = p;
	  in_fn[in_num] = argv[k]+l+1;
	  in_f[in_num] = fopen (in_fn[in_num], "r");
	  if ( ! in_f[in_num] )
	    error ("Failed to open input file.");
	  in_num++;
	}
      else if ( argv[k][l] == '+' )
	{
	  if ( out_num >= 256 )
	    error ("Too many output points.");
	  out_points[out_num] = p;
	  out_fn[out_num] = argv[k]+l+1;
	  out_f[out_num] = fopen (out_fn[out_num], "w");
	  if ( ! out_f[out_num] )
	    error ("Failed to open input file.");
	  out_num++;
	}
      else
	error ("Bad argument syntax.");
    }
  if ( ! in_num )
    error ("No input files.");
  if ( ! out_num )
    error ("No output files.");
  precalc ();
  /* Process data */
  while ( 1 )
    {
      for ( k=0 ; k<in_num ; k++ )
	{
	  int ch;

	  ch = getc (in_f[k]);
	  if ( ch == EOF )
	    exit (EXIT_SUCCESS);
	  in_data[k] = ch;
	}
      do_point ();
      for ( k=0 ; k<out_num ; k++ )
	putc (out_data[k], out_f[k]);
    }
  return 0;  /* Never reached */
}
