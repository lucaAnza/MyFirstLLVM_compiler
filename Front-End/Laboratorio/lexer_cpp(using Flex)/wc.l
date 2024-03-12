%{
#include <iostream>
using namespace std;

unsigned long charCount = 0, wordCount = 0, lineCount = 0;

%}

word [^ \t\n]+
eol \n

%option noyywrap

%%
{word} 	   {wordCount++; charCount += yyleng;}
{eol}	   {charCount++; lineCount++;}
.	   charCount++;

%%
int main( int argc, char** argv) {
    FlexLexer* lexer = new yyFlexLexer;
    lexer->yylex();
    cout << lineCount << " " << wordCount << " " << charCount << endl;
}
