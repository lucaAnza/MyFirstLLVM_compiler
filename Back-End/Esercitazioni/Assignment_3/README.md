# Assignment 3

## Consegna

• A partire dal codice della esercitazione 4, implementare un passo di Loop-Invariant Code Motion (LICM).

## Algoritmo per la Code Motion 

• Dato un insieme di nodi in un loop: 

1. Calcolare le <b>reaching definitions</b>.

2. Trovare le istruzioni <b>loop-invariant</b>.
   
3. Calcolare i <b>dominatori</b> (dominance tree)

4. Trovare le <b>uscite del loop</b> (i successori fuori dal loop)
   
5. Trovare le <b>istruzioni candidate alla code motion</b>:              (le condizioni devono essere tutte vere)
   1. Sono loop invariant
   2. Si trovano in blocchi che dominano tutte le uscite del loop <b>OPPURE</b> la variabile definita dall’istruzione è dead all’uscita del loop.
   3. Assegnano un valore a variabili non assegnate altrove nel loop
   4. Si trovano in blocchi che dominano tutti i blocchi nel loop che usano la variabile a cui si sta assegnando un valore

6. Eseguire una ricerca <b>depth-first</b> dei blocchi

7. Spostare l’istruzione candidata nel <b>preheader</b> se tutte le istruzioni
invarianti da cui questa dipende sono state spostate.


## Rappresentazione grafica del problema

### Control Flow Graph of .ll code (No mem2reg opt)  --- [C style]

<img src="img/LICM_no_mem2reg.png" alt="DU" width=70%></img>  

<br><br>

---

### Control Flow Graph of .ll code (with mem2reg opt)  --- [C style]

<br>

<img src="img/LICM_mem2reg.png" alt="DU" width=70%></img>

<br><br>

### Control Flow Graph of .ll code (with mem2reg opt) --- [IR style]

<br>

<img src="img/LICM_mem2reg_IR.png" alt="DU" width=70%></img>   
<br><br><br>



## Steps

1. Seguire lo step di inizializzazione del passo in <b>Esercitazione4</b>

2. Generare il file .ll nel seguente modo:

    ```bash
    echo "Avvio scripting per creazione MEM2REG file"
    INSTALL/bin/clang -S -emit-llvm -O0 TEST/source_c_files/LICM.c -o LICM_no_opt.ll -Xclang -disable-O0-optnone
    INSTALL/bin/opt -p=mem2reg LICM_no_opt.ll -o LICM_no_opt.bc 
    INSTALL/bin/llvm-dis LICM_no_opt.bc -o LICM.ll
    echo "Script terminato, risultato salvato in LICM.ll"
    echo "Eliminazione file intermedi"
    rm LICM_no_opt.bc
    rm LICM_no_opt.ll
    ```

3. Commentare le righe che incominciano con `attributes #...`

4. Cambiare il codice di <b> LoopPasses.cpp </b>

    ```c++
    //TODO -> Copiare dal progetto finale
    ```
<br>

5. Cambiare il codice di <b> LoopPasses.h </b>

    ```c++
    #ifndef LLVM_TRANSFORMS_LOOPPASSES_H
    #define LLVM_TRANSFORMS_LOOPPASSES_H

    #include "llvm/IR/PassManager.h"
    #include "llvm/Transforms/Scalar/LoopPassManager.h"


    namespace llvm {
        class LoopPasses : public PassInfoMixin<LoopPasses> {
            public:
            PreservedAnalyses run(Loop &L, LoopAnalysisManager &LAM , LoopStandardAnalysisResults &LAR, LPMUpdater &LU);
        };
    } // namespace llvm


    #endif // LLVM_TRANSFORMS_TESTPASS _H

    ```

<br>

6. Lanciare i seguenti comandi

    ```bash
    INSTALL/bin/opt -p loop_pass TEST/LICM.ll -o temp.bc
    INSTALL/bin/llvm-dis temp.bc -o LICM_opt.ll
    rm temp.bc
    ```





