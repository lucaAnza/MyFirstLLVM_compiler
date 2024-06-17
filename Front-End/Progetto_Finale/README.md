# My first Front-End compiler.

⚠ Remember to install dependencies package!

## How to start the compiler

1. `make`
2. `./kcomp <filename>` -> Stampa in stderr il codice IR generato.
    - Example : `./kcomp input.txt 2> output.ll`

## How to try if the generated IR code does what you expected

### .ll version
1. Save in a file with .ll extension the IR code    
2. `lli <file_name>.ll`               

### .s version
1. Save in a file with .s extension the IR code    
2. `clang -o file_exe input.s`


## Theoretical Prerequisites

Abstract Syntax Tree scheme:

<img src="img/tree_scheme.png" alt="liv1_1" width=50%></img>




## Steps

### Grammar Level 1.0

New features from the starting grammar are <span style="color:#57DDFF">highlighted</span>.

<table>
    <tr>
        <td> <img src="img/Grammar_liv1_1.png" alt="liv1_1" width=90%></img> </td>
        <td> <img src="img/Grammar_liv1_2.png" alt="liv1_1" width=90%></img> </td>
    </tr>
</table>

Feature:

1. Block.
2. Statements.
3. Vardefs.
4. Assignments
5. Init of local variable.
6. Init of global variable.
    
<br>

#### Block and Statements (step1_1)

These are the first feature we are going to implement.
Because we need a base for Bindings,Assignments,If.
<br><br>
Summary of each steps:

1. Add <b>class</b>, <b>type</b>, <b>token</b> and <b>rules</b> on grammar(</b>parser.yy<b>)

    ```c++

    ///////////////////////////////////CLASS//////////////////////////////////////////
    %code requires {
    ...
    class BlockAST;    //New
    }

    ///////////////////////////////////TOKEN//////////////////////////////////////////

    %define api.token.prefix {TOK_}
    %token
    LPAREN_G   "{"  //New
    RPAREN_G   "}"  //New
    ;

    ///////////////////////////////////TYPE//////////////////////////////////////////

    %type <BlockAST*> block;
    %type <std::vector<ExprAST*>> stmts;
    %type <ExprAST*> stmt;

    ///////////////////////////////////RULES//////////////////////////////////////////

    definition:
    "def" proto block   { $$ = new FunctionAST($2,$3); $2->noemit(); };  // <----- change exp with block

    stmts:
    stmt                 { std::vector<ExprAST*> statemets; statemets.insert(statemets.begin(),$1); $$ = statemets;}
    | stmt ";" stmts       { $3.insert($3.begin(),$1); $$ = $3; };

    stmt:
    block                    { $$ = $1;}
    | exp                    { $$ = $1;};

    block:
    "{" stmts "}"                     { $$ = new BlockAST($2); };

    ```

2. Add class header(<b>driver.hpp</b>)

    ```c++
    /// BlockAST
    class BlockAST : public ExprAST {
    private:
        std::vector<BindingAST*> bindings;
        std::vector<ExprAST*> stmts;
    public:
    BlockAST(std::vector<BindingAST*> bindings,std::vector<ExprAST*> stmts);
    BlockAST(std::vector<ExprAST*> stmts);
    Value *codegen(driver& drv) override;
    };
    ```

3. Add class implementation(<b>driver.cpp</b>)

    ```c++

    /*************************Block******************************/
    BlockAST::BlockAST(std::vector<BindingAST*> bindings,std::vector<ExprAST*> stmts):
    bindings(std::move(bindings)), stmts(std::move(stmts)) {};

    BlockAST::BlockAST(std::vector<ExprAST*> stmts):
    stmts(std::move(stmts)) {};

    Value* BlockAST::codegen(driver& drv){

    Value* blockValue;
    
    // Statements allocator
    for(int i=0; i<stmts.size(); i++){
        blockValue = stmts[i]->codegen(drv);
        if(!blockValue) return nullptr;
    }
    
    return blockValue;   
    };
        
    ```

4. Add token on <b>scanner.ll</b>

    ```c++
    "{"      return yy::parser::make_LPAREN_G  (loc);
    "}"      return yy::parser::make_RPAREN_G  (loc);
    ```







/////////////////TO DO///////////////////////////
#### Binding

This is the first feature that we will implement.
For this reason we add a rule in the grammar to have the possibility
to create a programm made with only a Binding.
So we can easily test it.
<br>
Summary of each steps:

1. Add rules on grammar(</b>parser.yy<b>)

    ```c++
    program:
    %empty                { $$ = new SeqAST(nullptr,nullptr); }
    |  top ";" program      { $$ = new SeqAST($1,$3); }
    |  binding ";" program  { $$ = new SeqAST($1,$3); }

    binding:
    "var" "id" initexp   { $$ = new Binding($2); };

    initexp:
    %empty               { $$ = nullptr; }
    | "=" exp              { $$ = $2; };
    ```

2. Add class header(<b>driver.hpp</b>)

    ```c++
    // Binding - Classe che rappresenta un binding (Ex: var x = 7)
    class Binding : public RootAST{
        private:
            std::string type;
        public:
            Binding(std::string type);
            std::string getType();
    };
    ```

3. Add class implementation(<b>driver.cpp</b>)

    ```c++
    // Implementazione della classe
    Binding::Binding(std::string type): type(type) {std::cout<<"hi i am luca\n";};
    std::string Binding::getType(){
            std::cout<<"tipo =  "<<type<<"\n";
            return type;
    }
    ```

4. Add type on parser,the eventually new token and the class use(</b>parser.yy<b>)

    ```c++
    //class
    %code requires {
    #include <string>
    #include <exception>
    ...
    class BindingAST;
    ...
    }

    //type
    %type <Binding*> binding
    %type <ExprAST*> initexp

    //token
    %define api.token.prefix {TOK_}
    %token
    ...
    EQUAL      "="
    ...
    ;
    ```

5. Add token on <b>scanner.ll</b>

    `"="      return yy::parser::make_EQUAL     (loc);`


#### Block