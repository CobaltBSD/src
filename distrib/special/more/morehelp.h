const char *more_help = "\n\
Most commands optionally preceded by integer argument k.  Defaults in brackets.\n\
Star (*) indicates argument becomes new default.\n\
-------------------------------------------------------------------------------\n\
<space>			Display next k lines of text [current screen size]\n\
z			Display next k lines of text [current screen size]*\n\
<return>		Display next k lines of text [1]*\n\
d or ctrl-D		Scroll k lines [current scroll size, initially 11]*\n\
q or Q or <interrupt>	Exit from more\n\
s			Skip forward k lines of text [1]\n\
f			Skip forward k screenfuls of text [1]\n\
b or ctrl-B		Skip backwards k screenfuls of text [1]\n\
'			Go to place where previous search started\n\
=			Display current line number\n\
/<regular expression>	Search for kth occurrence of regular expression [1]\n\
n			Search for kth occurrence of last r.e [1]\n\
!<cmd> or :!<cmd>	Execute <cmd> in a subshell\n\
v			Start up /usr/ucb/vi at current line\n\
ctrl-L			Redraw screen\n\
:n			Go to kth next file [1]\n\
:p			Go to kth previous file [1]\n\
:f			Display current file name and line number\n\
.			Repeat previous command\n\
-------------------------------------------------------------------------------\n\
";
