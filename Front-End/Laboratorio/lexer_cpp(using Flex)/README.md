# ATTENTION : Make file has got some bugs

## What's there in this directory ? 

In this directory you can find 2 simple cpp programm that simulate a Lexer. 
They are done by using Lex ( generator of lessic analizator)

## How can i try it ? 

### PGM1 ( simple tok )
1. Write on terminal:
`flex -+ -o src.cpp simpletok.l`
`g++ -o file_exe src.cpp`

### PGM2 (wc - separate version)

1. Write on terminal:
`g++ -c wcsep.cpp`
`g++ -c wcmain.cpp`
`g++ -o wc wcsep.o wcmain.o`
`./wc`
### PGM3 (wc - one file version)

1. Write on terminal:
`flex -+ -o src.cpp wc.l`
`g++ -o wc_exe src.cpp`

### PGM4 ( simple tok - with more tokens )
1. Write on terminal:
`flex -+ -o src.cpp moretokens.l`
`g++ -o file_exe src.cpp`


### Informazioni aggiuntive : 

Il programma Lex (file di norma con estensione .l) viene compilato
con il seguente comando:

`flex -+ -o <source>.cpp <filename>.l`

dove `filename` e `source` indicano i nomi rispettivamente del file
Lex e del programma C++ generato.

L'opzione -+ indica proprio che il target è il linguaggio C++
Se si omette l'opzione -o, il file viene creato con il nome default
lex.yy.cc

