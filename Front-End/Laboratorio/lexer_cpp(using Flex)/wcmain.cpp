#include <iostream>
#include <FlexLexer.h>
using namespace std;

extern unsigned long charCount, wordCount, lineCount;

int main()
{
  FlexLexer* lexer = new yyFlexLexer;
  lexer->yylex();
  cout << lineCount << " " << wordCount << " " 
       << charCount << endl;
  return 0;
}

