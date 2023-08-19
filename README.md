# C PROGRAMMING LANGUAGE
---
### This project is used with open source tools
No Windows based IDE environments are used or implied! Cygwin, Linux, MacOS and BSD environments are suitable.
### Project structure
    C-programming-language/
        |- 1-Variable/
            |- 1-1-example/             Example folder
                |- inc/
                    |- *            Header files
                |- obj/
                    |- *            Object files
                |- src/
                    |- main.c       C files
                    |- task1.c
                    |- task2.c
                    |- task3.c
                |- main             Executable program
                |- Makefile         Sub Makefile
        |- Makefile                     Used to clean up files built
        |- Makefile.incl                Main Makefile
### How to use
1. Change the BINARY variable (in Sub Makefile) to match your target name.
2. Put your C files in the `src/` folder.
3. Put your Header files in the `inc/` folder.
4. Object files in `obj/` folder, execultive program in root project directory.
5. If necessary, change the compiler and the flags (not recommended).
