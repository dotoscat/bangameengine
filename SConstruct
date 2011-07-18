#Don't touch
#===========

BANGELIBS = ["physfs", "lua5.1", "sfml-system", "sfml-window", "sfml-graphics"]
BANGECCFLAGS = ""

if ARGUMENTS.get("debug", 0):
    BANGECCFLAGS += "-g"

Program("bange", Glob("source/*.cpp"), CPPPATH=["./include"], LIBS=BANGELIBS, CCFLAGS=BANGECCFLAGS)
