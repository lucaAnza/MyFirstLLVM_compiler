# STEP ESERCITAZIONE




## ESERCIZIO 2


1. vai nella directory `/LLVM/SRC/llvm-project-llvmorg-17.0.6/llvm/include/llvm/Transforms/Utils$ `
2. Aggiungi il file **TestPass.h**


```
#ifndef LLVM_TRANSFORMS_TESTPASS_H
#define LLVM_TRANSFORMS_TESTPASS_H

#include "llvm/IR/PassManager.h"
namespace llvm {
    class TestPass : public PassInfoMixin<TestPass> {
        public:
        PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
    };
} // namespace llvm


#endif // LLVM_TRANSFORMS_TESTPASS _H
```

3. vai nella directory `/LLVM/SRC/llvm-project-llvmorg-17.0.6/llvm/lib/llvm/Transforms/Utils$ `

4. Aggiungi il file **TestPass.cpp**

```
#include "llvm/Transforms/Utils/TestPass.h"
using namespace llvm;
PreservedAnalyses TestPass::run(Function &F,
FunctionAnalysisManager &AM) {
errs() << Questa funzione si chiama << F.getName() << "\n";
return PreservedAnalyses::all();
}
```


5. vai nella directory  `/LLVM/SRC/llvm-project-llvmorg-17.0.6/llvm/lib/llvm/Transforms/Utils$ `

6. Modifichi il file CMakeList.txt e aggiungi il nome "TestPass.cpp" mettilo in ordine alfabetico

7. vai nella directory  `/LLVM/SRC/llvm-project-llvmorg-17.0.6/llvm/lib/Passes/PassRegistry.def`

8. Aggiungi questa riga "FUNCTION_PASS("testpass", TestPass())" al file **PassRegistry.def**
9. Aggiungi questa riga "#include "llvm/Transforms/Utils/TestPass.h"" al file **PassBuilder.cpp**

10. Vai in `/LLVM/BUILD/` e manda il comando `make opt` e successivamente `make install`

11. Andare in `/LLVM` e mandare il comando source `setup.sh`

12. Andare nella directory `LLVM/` e poi mandare il comando 
`opt -passes=testpass TEST/Loop.bc \ -disable-output`

`INSTALL/bin/opt -passes=testpass TEST/Loop.ll -disable-output`



### ATTENZIONE
1. modifica il file `/LLVM/setup.sh`    -> Controlla come fare
2. scrivere `source setup.sh`
3. manda `opt -passes=testpass TEST/Loop.ll -disable-output`






## ESERCIZIO 3

1. Al posto di funzione mettere "module"



