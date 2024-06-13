# ATTENTION : Make file has got some bugs

## Install

1. `sudo apt install flex`

## What's there in this directory ? 

In this directory you can find 2 simple cpp programm that simulate a Lexer. 
They are done by using Lex ( generator of lessic analizator)

## How can i try it ? 

### PGM1 ( simple tok )
Write on terminal:

1. `flex -+ -o src.cpp simpletok.l`
2. `g++ -o file_exe src.cpp`

### PGM2 (wc - separate version)

Write on terminal:
1. `g++ -c wcsep.cpp`
2. `g++ -c wcmain.cpp`
3. `g++ -o wc wcsep.o wcmain.o`
4. `./wc`
   
### PGM3 (wc - one file version)

Write on terminal:
1. `flex -+ -o src.cpp wc.l`
2. `g++ -o wc_exe src.cpp`

### PGM4 ( simple tok - with more tokens )

Write on terminal:
1. `flex -+ -o src.cpp moretokens.l`
2. `g++ -o file_exe src.cpp`


### Informazioni aggiuntive : 

Il programma Lex (file di norma con estensione .l) viene compilato
con il seguente comando:

`flex -+ -o <source>.cpp <filename>.l`

dove `filename` e `source` indicano i nomi rispettivamente del file
Lex e del programma C++ generato.

L'opzione -+ indica proprio che il target è il linguaggio C++
Se si omette l'opzione -o, il file viene creato con il nome default
lex.yy.cc

