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
2. Aggiungi `MODULE_PASS("local_opt", LocalOpts())` a **PassRegistry.def**

6.Vai in `/LLVM/BUILD/` Ricompila e installa opt:

1. `make opt`
2. `install opt`

7.Vai in `/LLVM` e mandare il comando source `setup.sh`

8.`opt -p localopts Foo.ll -o Foo-optimized.bc`

9.`llvm-dis Foo.optimezed.bc -o Foo.optimized.ll`
















```c++
#ifndef LLVM_TRANSFORMS_TESTPASS_H
#define LLVM_TRANSFORMS_TESTPASS_H

#include "llvm/IR/PassManager.h"
namespace llvm {
    class TestPass : public PassInfoMixin<TestPass> {
        public:
        PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
    };
} // namespace llvm


