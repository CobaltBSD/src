AR=ar
ARFLAGS=-rv
AS=as
CC?=tcc
OBJC=tcc
CXX=c++
CPP=$(CC) -E
LEX=lex
YACC=yacc
RM=rm -f
INSTALL=install
MAKE=make -j4

BUILDUSER?=build

# These variables will be removed once Cobalt is entirely LLVM-independent
CLANG=clang
CLANGXX=clang++
LD?=$(CC)

#    "LINK.o", "$(CC) $(LDFLAGS) $(TARGET_ARCH)",
#    "COMPILE.c", "$(CC) $(CFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c",
#    "LINK.c", "$(CC) $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)",
#    "COMPILE.m", "$(OBJC) $(OBJCFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c",
#    "LINK.m", "$(OBJC) $(OBJCFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)",
#    "COMPILE.cc", "$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(TARGET_ARCH) -c",
#    /* On case-insensitive filesystems, treat *.C files as *.c files,
#       to avoid erroneously compiling C sources as C++, which will
#       probably fail.  */
#    "COMPILE.cpp", "$(COMPILE.cc)",
#    "LINK.cc", "$(CXX) $(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_ARCH)",
#    "LINK.cpp", "$(LINK.cc)",
#    "YACC.y", "$(YACC) $(YFLAGS)",
#    "LEX.l", "$(LEX) $(LFLAGS) -t",
#    "YACC.m", "$(YACC) $(YFLAGS)",
#    "LEX.m", "$(LEX) $(LFLAGS) -t",
#    "LINK.s", "$(CC) $(ASFLAGS) $(LDFLAGS) $(TARGET_MACH)",
#    "COMPILE.s", "$(AS) $(ASFLAGS) $(TARGET_MACH)",
#    "LINK.S", "$(CC) $(ASFLAGS) $(CPPFLAGS) $(LDFLAGS) $(TARGET_MACH)",
#    "COMPILE.S", "$(CC) $(ASFLAGS) $(CPPFLAGS) $(TARGET_MACH) -c",
#    "PREPROCESS.S", "$(CPP) $(CPPFLAGS)",

.c.o:
	$(CC) ${CFLAGS} -c ${@:.o=.c} -o $(dir $@)/$(notdir $@)
#    ".o",
#    "$(LINK.o) $^ $(LOADLIBES) $(LDLIBS) -o $@",
#    ".s",
#    "$(LINK.s) $^ $(LOADLIBES) $(LDLIBS) -o $@",
#    ".S",
#    "$(LINK.S) $^ $(LOADLIBES) $(LDLIBS) -o $@",
#    ".c",
#    "$(LINK.c) $^ $(LOADLIBES) $(LDLIBS) -o $@",
#    ".cc",
#    "$(LINK.cc) $^ $(LOADLIBES) $(LDLIBS) -o $@",
#    ".C",
#    "$(LINK.C) $^ $(LOADLIBES) $(LDLIBS) -o $@",
#    ".cpp",
#    "$(LINK.cpp) $^ $(LOADLIBES) $(LDLIBS) -o $@",
#    ".s.o",
#    "$(COMPILE.s) -o $@ $<",
#    ".S.o",
#    "$(COMPILE.S) -o $@ $<",
#    ".c.o",
#    "$(COMPILE.c) $(OUTPUT_OPTION) $<",
#    ".cc.o",
#    "$(COMPILE.cc) $(OUTPUT_OPTION) $<",
#    ".cpp.o",
#    "$(COMPILE.cpp) $(OUTPUT_OPTION) $<",

.S.o:
	$(CC) ${CFLAGS} -c ${@:.o=.S} -o $(dir $@)/$(notdir $@)

.l.o:
	$(LEX) -o $(basename $@).yy.c $(basename $@).l
	$(CC) ${CFLAGS} -c ${@:.o=.yy.c} -o $(dir $@)/$(notdir $@)

.y.o:
	$(YACC) -o $(basename $@).tab.c -d $(basename $@).y
	$(CC) ${CFLAGS} -c ${@:.o=.tab.c} -o $(dir $@)/$(notdir $@)
