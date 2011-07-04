DEBUG = False #Set True or False

#Don't touch
#===========

BANGELIBS = ["physfs", "lua5.1", "chipmunk", "sfml-system", "sfml-window", "sfml-graphics"]
BANGECCFLAGS = ""

if DEBUG:
    BANGECCFLAGS += "-g"

Program("bange", Glob("source/*.cpp"), CPPPATH=["./include"], LIBS=BANGELIBS, CCFLAGS=BANGECCFLAGS)
