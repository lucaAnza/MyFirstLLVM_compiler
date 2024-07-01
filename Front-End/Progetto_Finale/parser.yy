%skeleton "lalr1.cc" /* -*- C++ -*- */
%require "3.2"
%defines

%define api.token.constructor
%define api.location.file none
%define api.value.type variant
%define parse.assert

%code requires {
  # include <string>
  #include <exception>
  class driver;
  class RootAST;
  class ExprAST;
  class NumberExprAST;
  class VariableExprAST;
  class CallExprAST;
  class FunctionAST;
  class SeqAST;
  class PrototypeAST;
  class BindingAST;
  class BlockAST;
  class AssignmentAST;
  class GlobalVariableAST;
  class IFstmsAST;
}

// The parsing context.
%param { driver& drv }

%locations

%define parse.trace
%define parse.error verbose

%code {
# include "driver.hpp"
}

%define api.token.prefix {TOK_}
%token
  END  0  "end of file"
  SEMICOLON  ";"
  COMMA      ","
  MINUS      "-"
  PLUS       "+"
  STAR       "*"
  SLASH      "/"
  LPAREN     "("
  RPAREN     ")"
  EQUAL      "="
  LPAREN_G   "{"
  RPAREN_G   "}"
  EQUAL_if   "=="
  LESS_if    "<"
  CONDITION  "?"
  CONDITION_SEPARATOR ":"
  EXTERN     "extern"
  DEF        "def"
  VAR        "var"
  GLOBAL     "global"
;

%token <std::string> IDENTIFIER "id"
%token <double> NUMBER "number"
%type <ExprAST*> exp
%type <ExprAST*> idexp
%type <std::vector<ExprAST*>> optexp
%type <std::vector<ExprAST*>> explist
%type <RootAST*> program
%type <RootAST*> top
%type <FunctionAST*> definition
%type <PrototypeAST*> external
%type <PrototypeAST*> proto
%type <std::vector<std::string>> idseq
%type <BlockAST*> block;
%type <std::vector<ExprAST*>> stmts;
%type <ExprAST*> stmt;
%type <ExprAST*> initexp
%type <AssignmentAST*> assignment;
%type <std::vector<BindingAST*>> vardefs;
%type <BindingAST*> binding;
%type <GlobalVariableAST*> globalvar;
%type <IFstmsAST*> expif;
%type <ExprAST*> condexp;

%%
%start startsymb;

startsymb:
program                 { drv.root = $1; }

program:
  %empty                { $$ = new SeqAST(nullptr,nullptr); }
|  top ";" program      { $$ = new SeqAST($1,$3); }

initexp:
  %empty               { $$ = nullptr; }
| "=" exp              { $$ = $2; };

top:
%empty                  { $$ = nullptr; }
| definition            { $$ = $1; }
| external              { $$ = $1; }
| globalvar             { $$ = $1; };

definition:
  "def" proto block       { $$ = new FunctionAST($2,$3); $2->noemit(); };

external:
  "extern" proto        { $$ = $2; };

proto:
  "id" "(" idseq ")"    { $$ = new PrototypeAST($1,$3);  };

globalvar:
  "global" "id"         { $$ = new GlobalVariableAST($2); };

idseq:
  %empty                { std::vector<std::string> args; $$ = args; }
| "id" idseq            { $2.insert($2.begin(),$1); $$ = $2; };

%left "<" "=";
%left "+" "-";
%left "*" "/";

////////////////////////////////////// GRAMMAR 1.0 //////////////////////////////////////////////////////////
stmts:
  stmt                 { std::vector<ExprAST*> statemets; statemets.insert(statemets.begin(),$1); $$ = statemets;}
| stmt ";" stmts       { $3.insert($3.begin(),$1); $$ = $3; };

stmt:
assignment                 { $$ = $1;}
| block                    { $$ = $1;}
| exp                      { $$ = $1;};

assignment:
  "id" "=" exp           { $$ = new AssignmentAST($1,$3);};

block:
  "{" stmts "}"                  { $$ = new BlockAST($2); };
| "{" vardefs ";" stmts "}"      { $$ = new BlockAST($2,$4); };

vardefs:
  binding                { std::vector<BindingAST*> bindings; bindings.insert(bindings.begin(),$1); $$ = bindings;}
| vardefs ";" binding    { $1.insert($1.begin(),$3); $$ = $1; };

binding:
  "var" "id" initexp   { $$ = new BindingAST($2,$3); };

////////////////////////////////////// GRAMMAR 1.0 //////////////////////////////////////////////////////////


exp:
  exp "+" exp           { $$ = new BinaryExprAST('+',$1,$3); }
| exp "-" exp           { $$ = new BinaryExprAST('-',$1,$3); }
| exp "*" exp           { $$ = new BinaryExprAST('*',$1,$3); }
| exp "/" exp           { $$ = new BinaryExprAST('/',$1,$3); }
| idexp                 { $$ = $1; }
| "(" exp ")"           { $$ = $2; }
| "number"              { $$ = new NumberExprAST($1); }
| expif                 { $$ = $1; };


////////////////////////////////////// GRAMMAR 1.0 //////////////////////////////////////////////////////////

expif:
  condexp "?" exp ":" exp   { $$ = new IFstmsAST($3,$5,$1);};

condexp:
  exp "<" exp               { $$ = new BinaryExprAST('<',$1,$3); }
| exp "==" exp              { $$ = new BinaryExprAST('=',$1,$3); }

////////////////////////////////////// GRAMMAR 1.0 //////////////////////////////////////////////////////////


idexp:
  "id"                  { $$ = new VariableExprAST($1); }
| "id" "(" optexp ")"   { $$ = new CallExprAST($1,$3); };

optexp:
  %empty                { std::vector<ExprAST*> args;
			 $$ = args; }
| explist               { $$ = $1; };

explist:
  exp                   { std::vector<ExprAST*> args;
                         args.push_back($1);
			 $$ = args;
                        }
| exp "," explist       { $3.insert($3.begin(), $1); $$ = $3; };
 
%%

void
yy::parser::error (const location_type& l, const std::string& m)
{
  std::cerr << l << ": " << m << '\n';
}
