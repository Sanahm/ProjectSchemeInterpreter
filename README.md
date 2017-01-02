# Welcome to the ProjectSchemeInterpreter wiki!
This project was about building in the programming language C **an interpreter for Scheme programming language**.
#What is Scheme?
Scheme is a functional programming language derived from the programming language Lisp.
For more informations see the following link [[https://en.wikipedia.org/wiki/Scheme_(programming_language)]] and [[http://www.schemers.org/Documents/Standards/R5RS/HTML/]] that deeply describes the Scheme programming language.

> Note that there is no programming norms for this language but just a standard and because of that you will find many Scheme interpreters with some differences between them.

# How to get the code?
The program runs well on linux system and on window with Mingw( minimalist unix package for window)

**1) Cloning the repository**

To get the code clone the repo by typing

     git clone "https://github.com/Sanahm/ProjectSchemeInterpreter"

**2) Structure of the repository**

The directory **ProjectSchemeInterpreter** contains 2 others directoires called **scheme** and **testing**. You can also find a file called readme.txt that also gives some explanations about the code structure.

The directory **scheme** is organized as follows:
- **Makefile:** to compile either in debug mode (show traces of the program) or in release mode (final product)
- **src:** contains the C code of your interpreter. You will have to modify the file read.c and to read the file repl.c
- **include:** which contains all the definitions of types and prototypes of your program. Read the headers carefully before you start coding and editing them.
- **tests_step0 to 4:** code tests
$ Make debug to compile the code in debug mode (it creates the executable 'scheme')

> If you want to continue the code please read the readme.txt file.

**3) How to compile?**

Make sure you are still in directory

    $ Make debug #to compile the code in debug mode (it creates the executable 'scheme')

    $ ./scheme #to launch it in interactive mode

    $ ./scheme myFile.scm #to launch it in script mode

    $ ./scheme tests_step?/02_readint.scm #to run it on file 02_readint.scm

    $ ../testing/simpleUnitTest.sh -b -e ./scheme tests_step?/*/*.Scm #to run the program on all test_step? files in batch mode (non-interactive)

    $ Make tarball #to create the archive to send to the teacher (this creates a tgz with your name and date)

#Ressources:
* [[http://people.csail.mit.edu/jaffer/SCM]]

* [[https://repl.it/languages/scheme]]
