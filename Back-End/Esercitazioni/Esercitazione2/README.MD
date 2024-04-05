# ESERCITAZIONE 2

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

``` c++
; int foo(int e, int a) {
;   int b = a + 1;
;   int c = b * 2;
;   b = e << 1;
;   int d = b / 4;
;   return c * d;
; }
```

↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓ IR Code ↓↓↓↓↓↓↓↓↓↓↓↓↓↓↓

``` text
define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) #0 {
  %3 = add nsw i32 %1, 1
  %4 = mul nsw i32 %3, 2
  %5 = shl i32 %0, 1
  %6 = sdiv i32 %5, 4
  %7 = mul nsw i32 %4, %6
  ret i32 %7
}
```

### Value

Ha dei metodi fondamentali come `getType() , hasName() , getName(), ...`.  
Inoltre ogni nodo _User_ ha una lista di _Value_ che lo compongono. Dato un _Instruction_ per ottenere tutti i suoi operandi fare:

```c++
User &Inst = ...;
for (auto Iter = Inst.op_begin(); Iter != Inst.op_end(); ++Iter)
    { Value *Operand = *Iter; }
```

### User

Da _User_,oltre agli operandi (Value), è possibile ottenere chi utilizza quella determinata instruzione.

```c++
User &Inst = ...;
for (auto Iter = Inst.user_begin(); Iter != Inst.user_end(); ++Iter)
    { User *InstUser = *Iter; }
```


## ESERCIZIO 1  (Analisi di LocalOpts.cpp)

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









## ESERCIZIO 2  (Modifica di LocalOpts.cpp)

```text
Per esercitarci a manipolare la IR *modifichiamo adesso il
passo LocalOpts.cpp* perché sostituisca tutte le operazioni di
moltiplicazione che hanno tra gli operandi una costante che
è una potenza di 2 con una shift (strength reduction)
Utilizzare solo funzioni di LLVM, non usare moduli matematici ( ex: #cmath )
Documentation on : < https://llvm.org/doxygen/classes.html >
```

![consegna](/Back-End/Esercitazioni/Esercitazione2/screen_1.png)


ADVICE :  Ricordati che per compilare devi andare in `/LLVM/BUILD/`:

1. `make opt`
2. `install opt`
3. `cd ..`  
4. `INSTALL/bin/opt -p localopts TEST/Foo.ll -o Foo-optimized.bc`  
(esegui i passi di ottimizazione sul file *Foo.ll* e mette crea un file binario *Foo-optimized.bc* )
5. (Optional) `INSTALL/bin/llvm-dis Foo-optimized.bc -o Foo.optimized.ll`
(trasforma il file binario -> file IR. In questo modo è più facile vedere il risultato )

1.Modificare il file **LocalOpts.cpp**

```c++
#include "llvm/Transforms/Utils/LocalOpts.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstrTypes.h"
// L'include seguente va in LocalOpts.h
#include <llvm/IR/Constants.h>

using namespace llvm;

bool runOnBasicBlock(BasicBlock &B) {
    
    unsigned cont = 0;
    
    //Itera tutte le istruzioni
    for (auto iter_i = B.begin() ; iter_i != B.end() ; ++iter_i){
        cont++;
        Instruction &I = *iter_i;
        
        if (I.isBinaryOp() && I.getOpcode() == Instruction::Mul) {

            BinaryOperator *mul = dyn_cast<BinaryOperator>(&I);
            outs()<<"("<<*mul<<")" <<" è una moltiplicazione\n";
            
            Value *op_0 = mul->getOperand(0);
            Value *op_1 = mul->getOperand(1);

            outs()<<"Operando[0] : "<<*op_0<<"\n";
            outs()<<"Operando[1] : "<<*op_1<<"\n";

            ConstantInt *C;
            Value *moltiplicando;
            if (C = dyn_cast<ConstantInt>(op_1)) {
                outs()<<"Operando[1] è una costante intera ("<<C->getValue()<<")\n";
                moltiplicando = op_0;
            }else if(C = dyn_cast<ConstantInt>(op_0)){
                outs()<<"Operando[0] è una costante intera ("<<C->getValue()<<")\n";
                moltiplicando = op_1;
            }
            
            //Controllo se ho trovato una costante e se la costante è una potenza di 2
            if (C && C->getValue().isPowerOf2()){
                const llvm::APInt costanteIntera = C->getValue();
                outs()<<"La seguente moltiplizazione ha al suo interno una potenza di 2!\n\n";
                // Conversione da mul -> shi
                Constant *shiftConst = ConstantInt::get(C->getType() , C->getValue().exactLogBase2());
                outs()<<"Provo a creare una nuova istruzione con v1 = "<<*moltiplicando<<" e v2 = "<<C->getValue()<<"\n";
                Instruction *new_shift = BinaryOperator::Create(BinaryOperator::Shl , moltiplicando , shiftConst); 
                //Inserimento istruzione dopo moltiplicazione
                new_shift ->insertAfter(mul);
                mul->replaceAllUsesWith(new_shift);
            }else{
                outs()<<"La seguente moltiplizazione NON ha al suo interno una potenza di 2!\n\n";
            }

        }
    }
    outs() << "\nIstruzioni analizzate : "<<cont<<"\n";
    return true;

}

bool runOnFunction(Function &F) {
    bool Transformed = false;

    for (auto Iter = F.begin(); Iter != F.end(); ++Iter) {
        if (runOnBasicBlock(*Iter)) {
            Transformed = true;
        }
    }

    return Transformed;
}


PreservedAnalyses LocalOpts::run(Module &M,
                                      ModuleAnalysisManager &AM) {
    for (auto Fiter = M.begin(); Fiter != M.end(); ++Fiter)
        if (runOnFunction(*Fiter))
            return PreservedAnalyses::none();
    return PreservedAnalyses::all();
}
```

· Risultato finale:

``` text

; ModuleID = 'Foo-optimized.bc'
source_filename = "TEST/Foo.ll"

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) {
  %3 = add nsw i32 %1, 1
  %4 = mul nsw i32 %3, 2
  %5 = shl i32 %3, 1           <--------------- Aggiunta della nuova istruzione creata ( left shitf <<1 == n * 2 )
  %6 = shl i32 %0, 1
  %7 = sdiv i32 %6, 4
  %8 = mul nsw i32 %5, %7      <--------------- Sostituzione di %4 -> %5
  ret i32 %8
}

```


## Primo assignment

```text
1. Algebraic Identity -> ...
2. Strength Reduction -> la cosa avanzata è che magari se la potenza è uguale a 15. Si può fare shift + add
3. Multi-Instruction Optimization -> ...
```


