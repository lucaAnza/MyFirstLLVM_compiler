# How to start the compiler


## Setup
⚠ Remember to install dependencies package!


## The pgm

1. `./kcomp <filename>` -> Stampa in stderr il codice IR generato.
    - Example : `./kcomp input.txt 2> output.ll`



## How to try if the generated IR code does what you expected

### .ll version
1. Save in a file with .ll extension the IR code    
2. `lli <file_name>.ll`               

### .s version
1. Save in a file with .s extension the IR code    
2. `clang -o file_exe input.s`



## REMEMBER !!!

On *parser2.yy* you can find a relative implemention of the first grammar version.