# ESERCITAZIONE 2

## ESERCIZIO 1

### Parte1


1.Scarica i file **LocalOpts.cpp** e **Foo.ll** e inseriscili in `/TEST`

2.Copia il file **LocalOpts.cpp** in `LLVM/SRC/llvm-project-llvmorg-17.0.6/llvm/lib/Transforms/Utils`

3.Inserisci nel file **CMakeLists.txt** questo : `LocalOpts.cpp`

4.Crea il file **LocalOpts.h** in `LLVM/SRC/llvm-project-llvmorg-17.0.6/llvm/include/llvm/Transforms/Utils` e inserisci

```c++
#ifndef LLVM_TRANSFORMS_LOCALOPTS_H
#define LLVM_TRANSFORMS_LOCALOPTS_H

#include "llvm/IR/PassManager.h"


namespace llvm {
    class LocalOpts : public PassInfoMixin<LocalOpts> {
        public:
        PreservedAnalyses run(Module &M, ModuleAnalysisManager &AM);
    };
} // namespace llvm


#endif // LLVM_TRANSFORMS_TESTPASS _H
```



5.Edita il **PassRegistry.def** e **PassBuilder.cpp** presenti in `LLVM/SRC/llvm-project-llvmorg-17.0.6/llvm/lib/Passes`

1. Aggiungi `#include "llvm/Transforms/Utils/LocalOpts.h"` a **PassBuilder.cpp**
2. Aggiungi `MODULE_PASS("localopts", LocalOpts())` a **PassRegistry.def**

6.Vai in `/LLVM/BUILD/` Ricompila e installa opt:

1. `make opt`
2. `install opt`

7.Vai in `/LLVM` 

8.Mandare il comando source `setup.sh` ( Eseguire questo step se si è settato il file setup.sh correttamente )

9.Mandare il comando : `INSTALL/bin/opt -p localopts TEST/Foo.ll -o Foo-optimized.bc`

10.Mandare il comando : `INSTALL/bin/llvm-dis Foo-optimized.bc -o Foo.optimized.ll`


#### Conclusione

Ora è possibile analizzare il file **LocalOpts.cpp** per capire cosa fa. Inoltre si può visionare il file
**Foo.optimized.ll** per vedere il codice IR che è stato generato dopo la compilazione.









## ESERCIZIO 2

```text
Per esercitarci a manipolare la IR modifichiamo adesso il
passo LocalOpts.cpp perché sostituisca tutte le operazioni di
moltiplicazione che hanno tra gli operandi una costante che
è una potenza di 2 con una shift (strength reduction)
Utilizzare solo funzioni di LLVM, non usare moduli matematici ( ex: #cmath )
Documentation on : < https://llvm.org/doxygen/classes.html >


<inserisci immagine>
```

ADVICE :  Ricordati che per compilare devi andare in `/LLVM/BUILD/`:

1. `make opt`
2. `install opt`
3. `cd ..`  
4. `INSTALL/bin/opt -p localopts TEST/Foo.ll -o Foo-optimized.bc`  
(esegui i passi di ottimizazione [nei passi fa parte LocalOpts.cpp] )

1.Modificare il file **LocalOpts.cpp**

2. Soluzione consigli : 

-> Per il logaritmo `exactLogBase2()`
-> Costruttore 


## Primo assignment

```text
1. Algebraic Identity -> ...
2. Strength Reduction -> la cosa avanzata è che magari se la potenza è uguale a 15. Si può fare shift + add
3. Multi-Instruction Optimization -> ...
```
