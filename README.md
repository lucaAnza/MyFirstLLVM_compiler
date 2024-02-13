# How to start the compiler


## Setup
1. First things to do is to install llvm-16 ( `sudo apt install llvm-16` )
2. To check if it correctly installed write `llvm-config --version`
3. Otherwise you can check if you can find this file `/usr/lib/llvm-16`


## The pgm

1. `./kcomp <filename>` -> Stampa in stderr il codice IR generato.



## How to try if the generated IR code does what you expected

### .ll version
1. Save in a file with .ll extension the IR code    
2. `lli <file_name>.ll`               

### .s version
1. Save in a file with .s extension the IR code    
2. `clang -o file_exe input.s`            