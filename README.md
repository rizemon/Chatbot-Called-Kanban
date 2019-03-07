# Chatbot-Called-Kanban
C Assignment Team Project 2 for ICT1002 Programming Fundamentals

### Prerequisites
1. Modify Makefile.  
For **Windows**, uncomment the settings for Microsoft compilers and comment the settings for GNU compilers.   
For **Linux**, comment the settings for Microsoft compilers and uncomment the settings for GNU compilers. 
#### For Windows
```
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
```
#### For Linux
```
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
```
2. Run Makefile
``` shell
make
```

### How to run

1. Execute chat1002.exe / chat1002
```shell
./chat1002
```


## Built With

* Tears and sweat.
* Grief and regret
* Proscastinations

## Authors

* **Shikiko** 
* **rizemon**


## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* Jesus

## How to test out linkedlist.h, hashtable.h, knowledgebase.h

1. Write your code in playground.c
2. Run Makefile
```shell
make
```
3. Run playground
```shell
./playground
```

