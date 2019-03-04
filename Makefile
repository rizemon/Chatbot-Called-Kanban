##############################################################################
#
# ICT1002 Assignment 2, 2018-19 Trimester 2.
#
# You can use this file to build the ICT1002 Chatbot using nmake (on Windows)
# or make (on Unix and MacOS X).
#
# Use the top settings for Microsoft compilers (i.e. Visual Studio) and the
# lower settings for GNU compilers (MacOS X, MinGW and Linux). Use the #
# character to comment out whichever settings you don't want.
#
###############################################################################

#
# Use the following settings for Microsoft compilers (Visual Studio).
#
#CC       = cl
#CFLAGS   = /nologo /c /Fo:
#LD       = link
#LDFLAGS  = /nologo /out:
#LDLIBS   = user32.lib
#RM       = del
#O        = .obj
#X        = .exe

#
# Use the following settings for GNU compilers (gcc).
#
CC       = gcc
CFLAGS   = -c -o
LD       = gcc
LDFLAGS  = -o 
LDLIBS   =
RM       = rm -f
O        = .o
X        =


###############################################################################
#
# Do not change anything below this line
#
###############################################################################

chat1002$(X): chatbot$(O) knowledge$(O) main$(O)
	$(LD) $(LDFLAGS)chat1002$(X) chatbot$(O) knowledge$(O) main$(O) $(LDLIBS)

chatbot$(O): chatbot.c chat1002.h
	$(CC) $(CFLAGS) chatbot$(O) chatbot.c

knowledge$(O): knowledge.c chat1002.h
	$(CC) $(CFLAGS) knowledge$(O) knowledge.c
	
main$(O): main.c chat1002.h
	$(CC) $(CFLAGS) main$(O) main.c
	
clean:
	$(RM) *$(O)
