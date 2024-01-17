/* WOTD : Wisdom Of The Day, version 1.0.2 */

/* Copyright (C) 1999 by
 *   David Madore <david.madore@ens.fr>
 *   Benjamin Lerman <quisar@mail.dotcom.fr>
 */

/* You may freely use, copy, modify and redistribute this file under
 * the terms of the GNU General Public License, but you are granted
 * ABSOLUTELY NO WARRANTY: see the file COPYING for more details. */

/* See the file README for instructions on how to compile. */

#include <stdio.h>
#include <sys/types.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include <md5.h>

#if 1
#define MAGIC_PHRASE \
"Never let your sense of morals prevent you from doing what is right."
#endif

static int start = 1;

void
newprintf (const char *pre, const char *data)
{
  if ( start )
    {
      printf ("%c", toupper (data[0]));
      printf (pre, data + 1);
      start = 0;
    }
  else
    {
      printf (pre, data);
    }
}

const char *magic_phrase = MAGIC_PHRASE;

const char *tab_adv[0x10] = {
  "sometimes", "often", "generally", "in some cases,",
  "according to some people,", "as a matter of fact,", "in truth,", "I believe",
  "without doubt,", "in my opinion,", "as always,", "in my dreams,",
  "in many cases,", "in all cases,", "to be honest,", "to tell the truth,",
};

const char *tab_qual[0x10] = {
  "little", "a little", "too little", "some",
  "much", "too much", "far too much", "a lot of",
  "no", "some", "a kind of", "a sort of",
  "a form of", "the truth behind", "the essence of", "the opposite of",
};

const char *tab_subst[0x80] = {
  "patience", "impatience", "diligence", "laziness",
  "humility", "hubris", "time", "space",
  "love", "hatred", "compassion", "liberty",
  "distance", "proximity", "courage", "cowardice",
  "honor", "dishonor", "honesty", "dishonesty",
  "valor", "control", "passion", "temperance",
  "spirituality", "singularity", "dependence", "independence",
  "serenity", "stress", "freedom", "bondage",
  "politeness", "uncouthness", "regularity", "irregularity",
  "sex", "abstinence", "faithfulness", "unfaithfulness",
  "thought", "action", "calm", "excitement",
  "harmony", "discord", "balance", "imbalance",
  "justice", "injustice", "quiet", "disquiet",
  "wisdom", "ignorance", "intelligence", "stupidity",
  "righteousness", "unrighteousness", "happiness", "sorrow",
  "sacrifice", "selfishness", "deftness", "undeftness",
  "karma", "ethics", "will", "frustration",
  "humor", "seriousness", "silence", "noise",
  "light", "darkness", "mysticism", "rationality",
  "illumination", "twilight", "memory", "forgetfulness",
  "esoterism", "scientificism", "wellness", "sickness",
  "technology", "magic", "science", "art",
  "knowledge", "ignorance", "fright", "angst",
  "joy", "grief", "energy", "synergy",
  "insight", "oblivion", "hope", "doom",
  "truth", "falsehood", "peace", "war",
  "spirit", "wit", "dream", "reality",
  "rage", "meditation", "imagination", "dullness",
  "boredom", "excitation", "humanity", "cruelty",
  "cluefulness", "cluelessness", "certainty", "doubt",
  "emotion", "stability", "creation", "destruction",
  "hell", "heaven", "damnation", "salvation",
};

const char *tab_verb[0x80] = {
  "is", "is not", "can be", "can't be",
  "might be", "might not be", "could be", "couldn't be",
  "may be", "may not be", "should be", "shouldn't be",
  "will be", "won't be", "has been", "hasn't been",
  "leads to", "doesn't lead to", "can lead to", "can't lead to",
  "might lead to", "might not lead to", "could lead to", "couldn't lead to",
  "may lead to", "may not lead to", "should lead to", "shouldn't lead to",
  "will lead to", "won't lead to", "has lead to", "hasn't lead to",
  "causes", "doesn't cause", "can cause", "can't cause",
  "might cause", "might not cause", "could cause", "couldn't cause",
  "may cause", "may not cause", "should cause", "shouldn't cause",
  "will cause", "won't cause", "has caused", "hasn't caused",
  "prevents", "doesn't prevent", "can prevent", "can't prevent",
  "might prevent", "might not prevent", "could prevent", "couldn't prevent",
  "may prevent", "may not prevent", "should prevent", "shouldn't prevent",
  "will prevent", "won't prevent", "has prevented", "hasn't prevented",
  "yields", "doesn't yield", "can yield", "can't yield",
  "might yield", "might not yield", "could yield", "couldn't yield",
  "may yield", "may not yield", "should yield", "shouldn't yield",
  "will yield", "won't yield", "has yielded", "hasn't yielded",
  "helps avoid", "doesn't help avoid", "can help avoid", "can't help avoid",
  "might help avoid", "might not help avoid", "could help avoid", "couldn't help avoid",
  "may help avoid", "may not help avoid", "should help avoid", "shouldn't help avoid",
  "will help avoid", "won't help avoid", "has helped avoid", "hasn't helped avoid",
  "distracts from", "doesn't distract from", "can distract from", "can't distract from",
  "might distract from", "might not distract from", "could distract from", "couldn't distract from",
  "may distract from", "may not distract from", "should distract from", "shouldn't distract from",
  "will distract from", "won't distract from", "has distracted from", "hasn't distracted from",
  "helps understand", "doesn't help understand", "can help understand", "can't help understand",
  "might help understand", "might not help understand", "could help understand", "couldn't help understand",
  "may help understand", "may not help understand", "should help understand", "shouldn't help understand",
  "will help understand", "won't help understand", "has helped understand", "hasn't helped understand",
};

int
main (void)
{
  time_t t;
  unsigned long day;
  struct MD5Context context;
  int i;
  unsigned char b;
  unsigned char digest[16];

  /* Get number of seconds since January 1, 1970 */
  t = time (NULL);
  /* Calculate Julian Day number */
  day = ((t/43200)+4881175)/2;
#if 0
  fprintf (stderr, "Julian day number is %lu\n", day);
#endif
  /* Calculate its MD5 (number is treated as little-endian so we can
   * increase number of bytes arbitrarily). */
  MD5Init (&context);
  MD5Update (&context, (const unsigned char *)magic_phrase,
	     strlen (magic_phrase));
  for ( i=0 ; day>>i ; i+=8 )
    {
      b = (day>>i)&0xff;
      MD5Update (&context, &b, 1);
    }
  MD5Final (digest, &context);
  /* Print wisdom of the day */
  if ( digest[0]&0x80 )
    newprintf ("%s ", tab_adv[digest[0]&0xf]);
  if ( digest[1]&0x80 )
    newprintf ("%s ", tab_qual[digest[1]&0xf]);
  newprintf ("%s ", tab_subst[digest[3]&0x7f]);
  printf ("%s ", tab_verb[digest[5]&0x7f]);
  if ( digest[8]&0x80 )
    printf ("%s ", tab_qual[digest[8]&0xf]);
  printf ("%s.\n", tab_subst[digest[9]&0x7f]);
  return 0;
}
