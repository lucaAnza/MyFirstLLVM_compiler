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
void loopAdjacentANDControlFlowFilter(Loop *l , std::set<Loop*> LoopFusionCandidates , LoopInfo &LI , DominatorTree &DT){

    //TODO - check if it is Guarded  //L->isGuarded();

    if (BasicBlock *ExitBlock = l->getExitBlock()) {
        //outs() << "Exit Block : " << *ExitBlock << "\n";
        BasicBlock *nextBB = ExitBlock->getTerminator()->getSuccessor(0);
        Loop *preheaderL1 = LI.getLoopFor(nextBB);
        //Check if the next BB is a Loop in the set
        if (LoopFusionCandidates.find(preheaderL1) == LoopFusionCandidates.end()) {
            LoopFusionCandidates.erase(l);
        //Check if L0 dominates L1
        }else if(!DT.dominates(ExitBlock ,nextBB )){
            LoopFusionCandidates.erase(l);
        }
    } else {
        outs() << "TopLevelLoop has multiple exit blocks.\n";
    }

}

PreservedAnalyses LoopFusionPass::run(Function &F, FunctionAnalysisManager &AM) {
    
    
    
    outs() << "Start loop fusion opt...\n";
    std::set<Loop*> LoopFusionCandidates;


    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
    LoopFusionCandidates = getAllTopLevelLoops(LI);
    DominatorTree DT;
    DT.recalculate(F); 

        
    for (Loop *TopLevelLoop : LI){
        
        outs()<<"TopLevelLoop : "<<*TopLevelLoop<<"\n";
        loopAdjacentANDControlFlowFilter(TopLevelLoop , LoopFusionCandidates , LI , DT);

         
    }

    outs()<<"Candidates for the loop fusion : \n";
    for(auto it = LoopFusionCandidates.begin() , end = LoopFusionCandidates.end() ; it != end ; it++ ){
        Loop *l = *it;
        outs()<<*l<<"\n";
    }
    

    return PreservedAnalyses::all();
}











/* Iterazione sui cicli annidati
        for (Loop *L : depth_first(TopLevelLoop)){
            // We only handle inner-most loops.
            if (L->isInnermost())
                LoopFusionCandidates.insert(L);
        }
        */