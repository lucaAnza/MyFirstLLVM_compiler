%{
#include <iostream>
#include <fstream>
#include <list>
using namespace std;

list<string> files;
%}

DIGIT   [0-9]
DIGIT1  [1-9]

%%
"+"               { cout << "        operatore <" << yytext[0] << ">" << endl; }
"-"               { cout << "        operatore <" << yytext[0] << ">" << endl; }
"="               { cout << "        operatore <" << yytext[0] << ">" << endl; }
{DIGIT1}{DIGIT}*  { cout << "           numero <" << yytext    << ">" << endl; }
.                 { cout << "Token sconosciuto <" << yytext[0] << ">" << endl; }
%%

int yyFlexLexer::yywrap(){
    cout << "Hallo\n";
    if (files.size()) {
    	ifstream f(files.front());
    	files.pop_front();
    	cout << "Start scanning new file\n";
    	/* yyFlexLexer::yyrestart(&f);
    	Alternativamente a quest'ultima 
    	yyFlexLexer::switch_streams(&f); 
    	*/
    	yyFlexLexer::yylex(&f);
    	return 0;
    }
    return 1;
}

int main(int argc, char** argv) {
    FlexLexer* lexer = new yyFlexLexer();
    if (argc>1) {
    	for (int i=2;i<argc;i++) {
    	    files.push_back(argv[i]);
    	}
    	ifstream f(argv[1]);
    	lexer->yylex(&f);
    } else {
    	lexer->yylex();
    }
    return 0;
}
	
