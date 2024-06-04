#include "llvm/Transforms/Utils/TestPass.h"

using namespace llvm;

PreservedAnalyses TestPass::run(Function &F,FunctionAnalysisManager &AM) {
    errs() << "Questa funzione si chiama << F.getName()" << "\n";
    return PreservedAnalyses::all();
}