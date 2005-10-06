SUBDIRS = basic core parser util $(NCURSESSUBDIR) .
bin_PROGRAMS = mvm
mvm_SOURCES = mvm.cpp
mvm_LDADD = basic/libmvm_basic.a core/libmvm_core.a parser/libmvm_parser.a util/libmvm_util.a $(NCURSESOBJS) @NCURSES_LIBS@
mvm_DEPENDENCIES = basic/libmvm_basic.a core/libmvm_core.a parser/libmvm_parser.a util/libmvm_util.a $(NCURSESOBJS)
