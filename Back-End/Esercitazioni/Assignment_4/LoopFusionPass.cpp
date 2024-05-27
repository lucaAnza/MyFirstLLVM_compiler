#include "llvm/Transforms/Utils/LoopFusionPass.h"
#include "llvm/Analysis/DominanceFrontier.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include <llvm/IR/Constants.h>

using namespace llvm;

PreservedAnalyses LoopFusionPass::run(Function &F, FunctionAnalysisManager &AM) {
    outs() << "Start loop fusion opt...\n";
    SmallVector<Loop*, 8> Worklist;

    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);

        
    for (Loop *TopLevelLoop : LI){
        outs()<<"TopLevelLoop : "<<*TopLevelLoop<<"\n";

        if (BasicBlock *ExitBlock = TopLevelLoop->getExitBlock()) {
            outs() << "Next BasicBlock after TopLevelLoop: " << *ExitBlock << "\n";
        } else {
            outs() << "TopLevelLoop has multiple exit blocks.\n";
        }

        for (Loop *L : depth_first(TopLevelLoop)){
            // We only handle inner-most loops.
            if (L->isInnermost())
                Worklist.push_back(L);
        }
    }

    return PreservedAnalyses::all();
}