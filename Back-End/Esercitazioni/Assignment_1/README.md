# Primo assignment

Documentation on : [LLVM Documentation](https://llvm.org/doxygen/classes.html)


## Esercizio1 - Algebraic identity

//TO DO

## Esercizio2 - Strength Reduction (più avanzato)

//TO DO

## Esercizio3 - Multi-Instruction Optimization

Example -> `a = b + 1, c = a − 1 ⇒a = b + 1, c = b`

Code:

``` c++

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
        
        if (I.isBinaryOp() && I.getOpcode() == Instruction::Add) {

            BinaryOperator *add = dyn_cast<BinaryOperator>(&I);
            outs()<<"("<<*add<<")" <<" è una addizione\n";
            
            Value *op_0 = add->getOperand(0);
            Value *op_1 = add->getOperand(1);

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
            
            
            const llvm::APInt costanteIntera
            Instruction candidates[10];  // TO-DO become a SET
            //Controllo se ho trovato una costante
            if (C){
                costanteIntera = C->getValue();
                /*
                // Conversione da mul -> shi
                Constant *shiftConst = ConstantInt::get(C->getType() , C->getValue().exactLogBase2());
                outs()<<"Provo a creare una nuova istruzione con v1 = "<<*moltiplicando<<" e v2 = "<<C->getValue()<<"\n";
                Instruction *new_shift = BinaryOperator::Create(BinaryOperator::Shl , moltiplicando , shiftConst); 
                //Inserimento istruzione dopo moltiplicazione
                new_shift ->insertAfter(mul);
                mul->replaceAllUsesWith(new_shift);
                */
            }else{
                outs()<<"La seguente moltiplizazione NON ha una costante intera\n\n";
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

