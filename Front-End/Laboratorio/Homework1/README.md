# Homework 1

Lo scopo principale del homework è quello di implementare <b>Subset Construction</b> Algoritm.<br>
Il progetto è diviso in 2 parti.
 - Part1: Subset Construction.
 - Part2: Creazione di un automa non deterministico a partire da un albero. 

<br>

è possibile trovare un esempio di Subset Construction nel file `SubsetConstruction_explanation+example.pdf`. <br>
(Example 1 è un automa inventato) <br>
(Example 2 riguarda l'input di `tree1.txt`). <br>
  
<br>

## How to run the programm

#### Option 1

```bash
g++ postorder.cpp` 
./a.out tree1.txt > input.txt`    # ( Di default l'output è fatto su IOSTREAM )
g++ substet_construction.cpp` 
./a.out input.txt`
```


#### Option2

```bash
g++ -o post.exe postorder.cpp`
g++ -o subset.exe subset_construction.cpp`
./post.exe tree1.txt | ./subset.exe`
```

<br><br>

## Part1 (Subset Construction)

Source file name : `subset_construction.cpp` <br>
Input : Automa finito non deterministico. <br>
Output: Automa finito deterministico <br>
S → Simboli alfabeto  ( messi in un SET di caratteri ) <br> 
K → Numero stati ( va dedotto dal numero di righe ) <br>
□ se in una generica riga c’è scritto → p q r  ( questi sono gli stati che può andare dallo stato i,j ) <br>

---

### Input-example1

Input - Graphic 📈

<img src="img/risultato_finale.png" alt="input"><br>

Input - Text 📄 (output of `postorder.cpp` executed with `tree1.txt`)
 
```c++
a b c   //Simboli dell’alfabeto (ε,a,b,c) 
14      //Stati finali
        // Δ (0,"ε")      
        // Δ (0,"a")
1       // Δ (0,"b")
        // Δ (0,"c")
12      // Δ (1,"ε")
        // Δ (1,"a")
        // ...
        // ...
        // ...
3       
<2 righe vuote>
4
<5 righe vuote>
5
<riga vuota>
13
<4 righe vuote>
7
<2 righe vuote>
9 6
<3 righe vuote>
6 9
<3 righe vuote>
10
<6 righe vuote>
11
13
<3 righe vuote>
2 8
<7 righe vuote>
```
<br><br>
<br>

### Output-example1

Output - Graphic 📈

<table style="width : 80%;">
     <tr>
        <td><h4>Letter</h4></td>
        <td><h4>Number</h4></td>
        <td><h4>State set</h4></td> 
    </tr>
    <tr>
        <td><img src="img/letter_deterministic_solution.png" alt="input" width=100%><br></td>
        <td><img src="img/number_deterministic_solution.png.png" alt="input" width=100%><br></td>
        <td>
        A = {0} <br>
        B = {1,2,6,8,9,10,12} <br>
        C = {3,4,6,7,9,10} <br>
        D = {11,13} <br>
        E = {6,7,9,10} <br>
        F = {5,13} <br>
        </td>
    </tr>
</table>



  
<br>

Output - Text 📄

```c++
// State set
0                      // A = {0}
1 2 6 8 9 10 12        // B = {1,2,6,8,9,10,12}
3 4 6 7 9 10           // C = {3,4,6,7,9,10}
11 13                  // D = {11,13}
6 7 9 10               // E = {6,7,9,10}
5 13                   // F = {5,13}
0 1 2 3 4 5            // Stati finali = {0,1,2,3,4,5} -> {A,B,C,D,E,F} 
// Transiction functions 
        //ẟ(0,a) 
1       //ẟ(0,b) = 1 
        //ẟ(0,c) 
2       //ẟ(1,a) = 2
        //ẟ(1,b) 
3       //ẟ(1,c) = 3
4       //ẟ(2,a) = 4
5       //ẟ(2,b) = 5
3       //ẟ(2,c) = 3
        //ẟ(3,a) 
        //ẟ(3,b) 
        //ẟ(3,c) 
4       //ẟ(4,a) = 4
        //ẟ(4,b) 
3       //ẟ(4,c) = 3
        //ẟ(5,a) 
        //ẟ(5,b) 
        //ẟ(5,c) 
```

<br><br>

### Input-example2

Input - Graphic 📈  (<span style="color:yellow">⚠️  this input isn't compatible with programm data structures</span>)

<img src="img/non_deterministic_auto.png" alt="input"><br>

Input - Text 📄    (<span style="color:yellow">⚠️  this input isn't compatible with programm data structures</span>)

```c++
a b                             //Simboli dell’alfabeto (ε,a,b) 
8 #                             //Stati finali
1 8                             // Δ (0,"ε")        
<riga vuota>                    // Δ (0,”a”)  
<riga vuota>                    // Δ (0,”b”) 
<riga vuota>                    // Δ (1,ε)
2 3                             // Δ(1,”a”) → cioè dallo stato 1 con input = “a”
<riga vuota>                    // Δ(1,”b") → cioè dallo stato 1 con input = “b”
4                               // Δ(2,”ε")...
<4 righe vuote>                 // ...
5 
8 
2 
<riga vuota>
6 7 
<3 righe vuote>
8 
<3 righe vuote>
5 8 
<3 righe vuote>
<eof>
```
<br>

### Output-example2

Output - Graphic 📈

<table>
    <tr>
        <td><img src="img/deterministic_auto.png" alt="input"><br></td>
        <td><img src="img/state_set_output.png" alt="input"><br></td>
    </tr>

</table>

Output - Text 📄

```c++
// State set
0 1 8                 // A = {0,1,8}
2 3 4 8               // B = {2,3,4,8}
2 4 8                 // C = {2,4,8}
5 6 7                 // D = {5,6,7}
8                     // E = {8}
5 6 7 8               // F = {5,6,7,8}
0 1 2 3 4 5           // Stati finali = {0,1,2,3,4,5} -> {A,B,C,D,E,F} 
// Transiction functions
1                     //ẟ(0,a) = 1(B)
<riga vuota>          // (0,”b”)
2                     // ẟ(1,a) = 2(C)
3                     // ẟ(1,b) = 3(D)
2                     // ẟ(2,a) = 2(C)
<riga vuota>          // (2,”b”)
4                     // ẟ(3,a) = 4(E)
5                     // ẟ(3,b) = 5(F)
4                     // ẟ(4,a) = 4(E)
5                     // ẟ(4,b) = 5(F)
```

<br><br>

### Explanation

Per implementare l'algoritmo si è deciso di utilizzare la seguente struttura dati:

Code:

```c++
char* simboloInput;   // IC
int* state1,*state2;   // STATE1,STATE2
```

Graphic📈:

<img src="img/data_structure_part1.png" alt="input">

<br>

- IC : rappresenta il carattere in input.
- State1 : rappresenta lo stato di arrivo.
- State2 : rappresenta lo stato di arrivo. (Utilizzato solo nel caso di ε).


<br><br>

## Part2 (automaton construction)

Source file name: `postorder.cpp` <br>
Input: File di testo contente la rappresentazione lineare di un albero <br>
Output: Automa a stati finiti non deterministico. <br>
Example: On explanation you can find the solution of input example `tree1.txt`

### Input-example1

Input - Text 📄 (`tree1.txt`)

```text
a b c
  ( .(b)(| (.(a) (b))(. (*(a))(c)) ))
```
<br>

### Output-example1

Output - Graphic 📈

<img src="img/risultato_finale.png" alt="risultato" width=30%>

Output - Text 📄

```c++
a b c   //Simboli dell’alfabeto (ε,a,b,c) 
14      //Stati finali
        // Δ (0,"ε")      
        // Δ (0,"a")
1       // Δ (0,"b")
        // Δ (0,"c")
12      // Δ (1,"ε")
        // Δ (1,"a")
        // ...
        // ...
        // ...
3       
<2 righe vuote>
4
<5 righe vuote>
5
<riga vuota>
13
<4 righe vuote>
7
<2 righe vuote>
9 6
<3 righe vuote>
6 9
<3 righe vuote>
10
<6 righe vuote>
11
13
<3 righe vuote>
2 8
<7 righe vuote>
```
<br><br>

### Explanation

A seguito l'algoritmo per costruire l'automa partendo dal seguente AST(Abstract Syntax Tree).<br>
La costruzione dell'automa viene fatta durante la visita dell'albero.<br>
La struttura dati utilizzata è visionabile nella _Parte1_.

#### AST:

`tree1.txt`

<img src="img/AST_example.png" alt="input">

#### ALGORITMO: 

---

##### Caso Base:  

<img src="img/caso_base.png" alt="caso base" width=30%>

###### Concatenazione(·):

<img src="img/concatenazione.png" alt="concatenazione" width=40%>

###### Chiusura(*):  

<img src="img/chiusura_riflessiva.png" alt="chiusura riflessiva" width=40%>

###### Unione(|):  

<img src="img/unione.png" alt="unione" width=40%>

---

<br><br>

#### Risulato finale:

`tree1.txt` trasformed into a non deterministic automaton.

<img src="img/risultato_finale.png" alt="risultato" width=40%>

<br>

Filled data structure _(Part1)_

<img src="img/tree1_debug_print.png" alt="risultato" width=30%>





