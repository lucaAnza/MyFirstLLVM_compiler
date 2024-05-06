# ESERCITAZIONE 4

-> Slide-08 Esercitazione - Loops e UD-DU Chains

## Prerequisiti

· Ricorda il seguente schema di classi:

```mermaid
flowchart TD
    
    Value --> User

    User --> Instruction

    Instruction
```

· Ricordati che:

- *Foo-optimized.bc* è il file binario generato
- *Foo.ll* è il file(IR) che stiamo ottimizando

· Ricordati che per compilare:

- `make opt (/BUILD)`
- `make -j16 install (/BUILD)`
- `INSTALL/bin/opt -p localopts TEST/Foo.ll -o Foo-optimized.bc`




## Consegna

### 1.Verificare che il loop sia in forma normale

`isLoopSimplifyForm()`

### 2.Recuperare blocchi significativi del loop

```c++
getLoopPreheader () const`
getHeader() const
getBlocks() const
```

### 3.Scorrere i basic blocks che compongono un loop

```c++

for (Loop::block_iterator BI = L->block_begin(); BI != L->block_end(); ++BI);

```


## Steps

0.Attenzione: <b>LoopPass</b> esiste già come nome.

1.vai nella directory `/LLVM/SRC/llvm-project-llvmorg-17.0.6/llvm/include/llvm/Transforms/Utils/`

2.Aggiungi il file **LoopPasses.h**

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

3.vai nella directory `/LLVM/SRC/llvm-project-llvmorg-17.0.6/llvm/lib/llvm/Transforms/Utils/`

4.Aggiungi il file **LoopPasses.cpp**

```c++
#include "llvm/Transforms/Utils/LoopPasses.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstrTypes.h"
#include <llvm/IR/Constants.h>


using namespace llvm;


#include <stdio.h>
#include <stdlib.h>


PreservedAnalyses LoopPasses::run(Loop &L, LoopAnalysisManager &LAM , LoopStandardAnalysisResults &LAR, LPMUpdater &LU){

    outs() << "Starting loop programm: \n\n";

    for (Loop::block_iterator BI = L.block_begin(); BI != L.block_end(); ++BI){
        outs()<<"Loop : "<<*BI<<"\n";
    }
  
    return PreservedAnalyses::all();
}

```

5.vai nella directory  ` /LLVM/SRC/llvm-project-llvmorg-17.0.6/llvm/lib/Transforms/Utils/ `

6.Modifichi il file CMakeList.txt e aggiungi il nome "LoopPasses.cpp" mettilo in ordine alfabetico.

7.vai nella directory  `/LLVM/SRC/llvm-project-llvmorg-17.0.6/llvm/lib/Passes/PassRegistry.def`

8.Aggiungi questa riga `LOOP_PASS("loop_pass", LoopPasses())` al file **PassRegistry.def**

9.Aggiungi questa riga `#include "llvm/Transforms/Utils/LoopPasses.h"` al file **PassBuilder.cpp**

10.Vai in `/LLVM/BUILD/` e manda il comando `make opt` e successivamente `make install`

⚠ Attenzione ⚠

Per generare il file Loop1.ll si sono eseguiti i seguenti step:

1. Creato un file .c che contenesse un loop
2. Lanciare il seguente comando `INSTALL/bin/clang -S -emit-llvm -O0 TEST/source_c_files/Loop1.c -o Loop1.ll`
3. Commentare (add `;`) nel file Loop1.ll la seguente riga : `attributes #0 = { noinline nounwind optnone uwtable "frame-pointer"="all" "m...`


11.Andare nella directory `LLVM/` e poi mandare il comando:

`INSTALL/bin/opt -p loop_pass TEST/Loop1.ll -o Loop1-optimazed.bc`  
`INSTALL/bin/llvm-dis Loop1-optimazed.bc -o Assignment_optimazed.ll`












