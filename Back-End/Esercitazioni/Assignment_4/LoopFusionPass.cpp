#include "llvm/Transforms/Utils/LoopFusionPass.h"
#include "llvm/Analysis/DominanceFrontier.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include <llvm/IR/Constants.h>

using namespace llvm;


/// @brief  Find all top level loops
/// @param LI Info struct of the Loop
/// @return  Set of Loops 
std::set<Loop*> getAllTopLevelLoops(LoopInfo &LI){
    std::set<Loop*> temp;
    for (Loop *TopLevelLoop : LI){
        temp.insert(TopLevelLoop);
    }
    return temp;
}

/// @brief remove from the set the Loops are not adjent
/// @param l  loop pointer
/// @param TopLevelLoops  set of loop candidate to the fusion
/// @param LI  Loop Info struct
void loopAdjentFilter(Loop *l , std::set<Loop*> LoopFusionCandidates , LoopInfo &LI){

    if (BasicBlock *ExitBlock = l->getExitBlock()) {
        //outs() << "Exit Block : " << *ExitBlock << "\n";
        BasicBlock *nextBB = ExitBlock->getTerminator()->getSuccessor(0);
        Loop *nextLoop = LI.getLoopFor(nextBB);
        if (LoopFusionCandidates.find(nextLoop) != LoopFusionCandidates.end()) {
            LoopFusionCandidates.erase(nextLoop);
            LoopFusionCandidates.erase(l);
        }
    } else {
        outs() << "TopLevelLoop has multiple exit blocks.\n";
    }

}

PreservedAnalyses LoopFusionPass::run(Function &F, FunctionAnalysisManager &AM) {
    
    //L->isGuarded();
    
    outs() << "Start loop fusion opt...\n";
    std::set<Loop*> LoopFusionCandidates;


    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
    LoopFusionCandidates = getAllTopLevelLoops(LI);

        
    for (Loop *TopLevelLoop : LI){
        outs()<<"TopLevelLoop : "<<*TopLevelLoop<<"\n";

        loopAdjentFilter(TopLevelLoop , LoopFusionCandidates , LI);

        /* Iterazione sui cicli annidati
        for (Loop *L : depth_first(TopLevelLoop)){
            // We only handle inner-most loops.
            if (L->isInnermost())
                LoopFusionCandidates.insert(L);
        }
        */ 
    }

    return PreservedAnalyses::all();
}