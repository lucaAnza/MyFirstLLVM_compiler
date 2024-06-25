# Appunti su slide-11



## Istruzioni Loop-Invariant

1. Gli operandi sono definiti fuori dal loop
2. Gli operandi sono istruzioni che sono loop-invariant.

### How to identify it?

1. Calcolare le reaching definitions.
2. Per ogni istruzione del tipo A = B + C è loop-invariant se:
    1. Le reaching definitions di B e C sono fuori dal Loop.
    2. C'è esattamente una reaching definition per B o C e si tratta di un'istruzione.


<br><br>

## Code motion

Non tutte le istruzioni loop-invariant possono essere spostate nel preheader.

### Condizioni

- Correttezza: lo spostamento del codice non altera la semantica.
- Performance: l'esecuzione del codice non è rallentata.
- ...


## Algoritmo

1. ...
2. ...
3. ...






