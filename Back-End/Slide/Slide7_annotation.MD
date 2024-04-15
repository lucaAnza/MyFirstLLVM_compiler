# Appunti su slide-07

## Difference about local/global/interprocedural analisys

- Local -> part of a CFG.
- Global -> the *entire* CFG.
- Interprocedural -> more than 1 module.

## Data Flow analisys

- Definition
- Start from CFG (Control Flow Graph)
- For each point of the programm(prima e dopo ogni statements) you make an analisys.

BasickBlock effects:

1. *Uses* -> b,c                      \[USE\]
2. *Kills* a definition -> a          \[KILL\]
3. *Defines* a variable -> a          \[DEF\]

Locally exposed use -> non è preceduto nel BB da una definizione della stessa variabile.  
Locally available definition -> ? 

*Locally exposed use, Example:*

```c++

t1 = r1+r2   // Usi localmente esposti -> r1,r2
r2 = t1      // Definizioni uccise -> r2
t2 = r2+r1    
r1 = t2
t3 = r1*r1
r2 = t3
if r2>100 goto L1

```

## Reaching Definitions

- Per ogni punto del programma se esiste un percorso da p a d tale per cui d non è uccisa.
- Creo un bit vettor: bool v[n_definitions]
- Watch examples: pag 20,21,22,23,24.


### Example slide_48

<img src="img/screen_bit_vector.png" alt="img" width=45%></img>

1. Crea tabella gen e kill

|    | Gen   | Kill |
|----|-------|------|
| B1 | 1,2,3 | 4,5,6,7|
| B2 | 4,5   | 1,2,7  |
| B3 | 6     | 3      |
| B4 | 7     | 1,4    |



2. 

```text

*Iteration-1

--------------------B1------------------                                                  It-0                 
OLDOUT[B1] = ∅ 
OUT[B1] = Gen[B1] U (In[B1] - Kill[B1]) = 1,2,3 U ∅ = 1,2,3   => OUT[B1] = 1,2,3    [CHANGED from old]
--------------------B1------------------

--------------------B2------------------
In[B2] = OUT[B1] U OUT[B4] = 1,2,3 U  ∅ = 1,2,3  => IN[B2] = 1,2,3
OLDOUT[B2] = ∅
OUT[B2] = 4,5 U (1,2,3-1,2,7) = 3,4,5 => OUT[B2] = 3,4,5                            [CHANGED from old]
--------------------B2------------------

--------------------B3------------------
In[B3]=OUT[B2] = 3,4,5
OLDOUT[B3] = ∅
OUT[B3] = 6 U (3,4,5-3) = 4,5,6 => OUT[B3] = 4,5,6                                  [CHANGED from old]
--------------------B3------------------

--------------------B4------------------
In[B4] = OUT[B2] U OUT[B3] = 3,4,5,6Ù
OLDOUT[B4] = ∅
OUT[B4] = 7 U (3,4,5,6-1,4) = 3,5,6,7 =>  OUT[B4] = 3,5,6,7                         [CHANGED from old]
--------------------B4------------------

*Iteration-2
...
*Iteration-3
...

(Continua fino a quando per ogni BB (OLDOUT == OUT) )

```

## Liveness Analysis

- Determinare per ogni linea di del basic block, se una variabile è viva.  
- Il bit vector sarà un bit per ogni variabile bool v[n_variable]
