# My first Front-End compiler.


## How to start the compiler
⚠ Remember to install dependencies package!

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
        <td> <img src="img/Grammar_liv1_1.png" alt="liv1_1" width=90%></img> </td>
    </tr>
</table>

Feature:

1. Binding.
2. Assignment.
3. Init of local variable.
4. Init of global variable.
    
<br>

#### Assignment

This is the first feature that we will implement.
For this reason we add a rule in the grammar to have the possibility
to create a programm made with only a Binding.
So we can easily test the feature.
<br>
Summary of each steps:

1. Add rules on grammar

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

2. Continue...

