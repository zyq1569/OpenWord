# ----------------------------------------------------
# 
# ------------------------------------------------------

# This is a reminder that you are using a generated .pro file.
# Remove it when you are finished editing this file.
#message("You are running qmake on a generated .pro file. This may not work!")

HEADERS +=  \
            generated/simpleParser.h \
            drawstyle.h \
            writer.h \
            ODrawToOdf.h \
#            shapes.h \
#            shapes2.h \
            pictures.h \
            pole.h \
            MsoUtils.h \
            NumberFormatParser.h


SOURCES += generated/simpleParser.cpp \
            drawstyle.cpp \
            writer.cpp \
            ODrawToOdf.cpp \
            shapes.cpp \
            shapes2.cpp \
            pictures.cpp \
            pole.cpp \
            MsoUtils.cpp \
            NumberFormatParser.cpp
