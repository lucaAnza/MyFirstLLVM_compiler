# Primo assignment

Documentation on : [LLVM Documentation](https://llvm.org/doxygen/classes.html)


## Esercizio1 - Algebraic identity

//TO DO

## Esercizio2 - Strength Reduction (più avanzato)

//TO DO

## Esercizio3 - Multi-Instruction Optimization

Example -> `a = b + 1, c = a − 1 ⇒a = b + 1, c = b`

1.Creazione del codice IR di prova

```text

; C++ - programm
; b = 1+1
; a = b + 1
; c = a-1 
; d = c * 4
; e = c + 3
; return e
; ...

define dso_local i32 @foo(i32 noundef %0, i32 noundef %1) {
  %b = add nsw i32 1  , 1
  %a = add nsw i32 %b , 1
  %c = sub nsw i32 %a , 1
  %3 = mul nsw i32 %c , 4
  %4 = add nsw i32 %c , 3
  ret i32 %4
}


```

2.Modifica del file LocalOpts.cpp


Code:

``` c++

#include "llvm/Transforms/Utils/LocalOpts.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstrTypes.h"
// L'include seguente va in LocalOpts.h
#include <llvm/IR/Constants.h>
#include <vector>

using namespace llvm;


// Funzione che ritorna il value che dovrei mettere al posto della sottrazione
Value* findOperator(BasicBlock::iterator sottrazione , BasicBlock::iterator primaIstruzione , Value* var , const llvm::APInt costanteSub ){  

    // Itera le istruzioni partendo dalla sottrazione e arriva fino all'inizio (primaIstruzione)               // TO-DO : migliorare ciclo
    BasicBlock::iterator it = sottrazione;
    ConstantInt* C0,*C1;
    do{
        if(it == primaIstruzione)
            break;
        it--;
        
        Instruction *sub = dyn_cast<Instruction>(var);
        Instruction *instruction = &(*it);

        //Controllo se il value dell'operazione che sto analizzando è uguale al value del sottrazione          //TO-DO : trovare un altro metodo per confrontare
        if( sub->getOperand(0) == instruction->getOperand(0) && sub->getOperand(1) == instruction->getOperand(1)) {
            outs()<<"Ho trovato un istruzione con il Value che è un buon candidato ( istr : "<<*instruction<<" )\n";
            C0 = dyn_cast<ConstantInt>(instruction->getOperand(0));
            C1 = dyn_cast<ConstantInt>(instruction->getOperand(1));
            if ( C0 != NULL ){
                const llvm::APInt costanteAdd = C0->getValue();
                outs()<<"Costante trovata! : "<<costanteAdd<<"\n";
                if(costanteAdd.eq(costanteSub)){
                    outs()<<"Costante uguale a quella della sottrazione!\n";
                    return instruction->getOperand(1);
                }
            }else if(C1 != NULL){
                const llvm::APInt costanteAdd = C1->getValue();
                outs()<<"Costante trovata! : "<<costanteAdd<<"\n";
                if(costanteAdd.eq(costanteSub)){
                    outs()<<"Costante uguale a quella della sottrazione! : \n";
                    return instruction->getOperand(0);
                }
            }else{
                outs()<<"Nessuna costante trovata!\n";
            }
        }
    }while(true);


    return NULL;

}


bool runOnBasicBlock(BasicBlock &B) {
    
    unsigned cont = 0;
    std::vector<Instruction*> toDelete;  
    
    //Itera tutte le istruzioni
    for(auto iter_i = B.begin() ; iter_i != B.end() ; ++iter_i){
        cont++;
        Instruction &I = *iter_i;
        
        //Controllo se l'istruzione è una sottrazione
        if(I.isBinaryOp() && I.getOpcode() == Instruction::Sub) {

            BinaryOperator *sub = dyn_cast<BinaryOperator>(&I);
            outs()<<"("<<*sub<<")" <<" è una sottrazione\n";
            
            Value *op_0 = sub->getOperand(0);
            Value *op_1 = sub->getOperand(1);

            ConstantInt *C;
            Value *variabile;
            if( (C = dyn_cast<ConstantInt>(op_1)) ) {
                variabile = op_0;
            }else if( (C = dyn_cast<ConstantInt>(op_0)) ){
                variabile = op_1;
            }
            
            //Controllo se ho trovato una costante
            if(C){
                const llvm::APInt costanteIntera = C->getValue();
                Value* new_value = findOperator(iter_i , B.begin() , variabile , costanteIntera);
                if(new_value){  // Controllo se ho trovato un addizione con le caratteristiche desiderate
                    outs() << "Nuovo valore che devo mettere  c = ... <----- = {"<<*new_value<<"} \n";
                    I.replaceAllUsesWith(new_value);
                    toDelete.push_back(&I);
                }else{
                    outs()<< "Non ho trovato nessuna <Add> con le caratteristiche adatte!\n";
                }
                
            }else{
                outs()<<"La seguente sottrazione NON ha una costante intera\n\n";
            }
        }
        outs()<<"\n\n";
        
    }


    //Cancellazione di tutte le istruzioni inutili
    for (auto& element : toDelete) {
        outs()<<"Cancello la seguente istruzione : "<<*element<<"\n";
        element->eraseFromParent();
    }


    //Debug
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

