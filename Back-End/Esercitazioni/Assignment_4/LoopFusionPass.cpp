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
std::vector<Loop*> getAllTopLevelLoops(LoopInfo &LI){
    std::vector<Loop*> temp;
    for (Loop *TopLevelLoop : LI){
        temp.push_back(TopLevelLoop);
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


bool are_loops_adjacent(const Loop* L0, const Loop* L1) {
    // Controllo se i due loop sono nulli
    if (!L0 || !L1) {
        return false;
    }

    //nel preheader del loop L0 c'è un branch che va al preheader del loop L1
    if (L0->isGuarded()) {
        outs()<<"L0 è guarded\n";
        BasicBlock* L0preheader = L0->getLoopPreheader();
        //prendo l'ultimo istruzione del preheader del loop L0
        Instruction* L0preheaderTerminator = L0preheader->getTerminator();
        //controllo se l'istruzione è un branch
        if (BranchInst* L0preheaderBranch = dyn_cast<BranchInst>(L0preheaderTerminator)) {
            //controllo se il branch ha due operandi
            if (L0preheaderBranch->getNumSuccessors() == 2) {
                //prendo il secondo operando del branch
                BasicBlock* L0preheaderBranchSuccessor1 = L0preheaderBranch->getSuccessor(0);
                BasicBlock* L0preheaderBranchSuccessor2 = L0preheaderBranch->getSuccessor(1);

            if (L0preheaderBranchSuccessor1 == L1->getHeader() || L0preheaderBranchSuccessor2 == L1->getHeader()) {
                return true;
            }
            }

        }
        return false;
    }

//non Guarded
    if(!L0->isGuarded()){
    outs()<<"L0 non è guarded\n";
    SmallVector<BasicBlock *> L0exitBlocks;
    //prendo tutti gli exit block del loop e li metto in un vettore
    L0->getExitBlocks(L0exitBlocks);
    //controllo se il preheader del loop L1 è diverso all'exit block del loop L0, nel caso in cui sia diverso ritorno false
    //vado a controllare che tutte le uscite convergono verso un unico punto s
    for (BasicBlock* exitingblock : L0exitBlocks) {
            if(exitingblock != L1->getLoopPreheader()){
                return false;
            }
        }
        return true;
    }
}


//Funzionante (da come presupposto che sia già stato fatto il controllo di adiacenza)
bool areControlFlowEquivalent(Loop *L0, Loop *L1, DominatorTree &DT, PostDominatorTree &PDT){
    
    SmallVector<BasicBlock *> L0exitBlocks;
    L0->getExitBlocks(L0exitBlocks);

    for (BasicBlock* exitBlock : L0exitBlocks ) {
        BasicBlock *nextBB = exitBlock->getTerminator()->getSuccessor(0);
        int n_succ = exitBlock->getTerminator()->getNumSuccessors();
        if(n_succ > 0 && !DT.dominates(exitBlock ,nextBB ) && !PDT.dominates(nextBB, exitBlock)){
            return false;
        }   
    }

    return true;
}


// Non funzionante, logicamente corretto.
bool haveSameTripCount(Loop *L0, Loop *L1, ScalarEvolution &SE){
    const SCEV *S1 = SE.getBackedgeTakenCount(L0);
    const SCEV *S2 = SE.getBackedgeTakenCount(L1);

    if (S1 == S2) {
        outs()<<"I 2 loop hanno lo stesso numero di iterazioni!\n";
        return true;
    } else {
        return false;
    }
}




PreservedAnalyses LoopFusionPass::run(Function &F, FunctionAnalysisManager &AM) {
    
    
    
    outs() << "Start loop fusion opt...\n";
    std::vector<Loop*> LoopFusionCandidates;
    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
    LoopFusionCandidates = getAllTopLevelLoops(LI);


    // Point 3 - Dominance
    DominatorTree &DT = AM.getResult<DominatorTreeAnalysis>(F);
    PostDominatorTree &PDT = AM.getResult<PostDominatorTreeAnalysis>(F);

    // Point 2 - Same number of iteration
    ScalarEvolution &SE = AM.getResult<ScalarEvolutionAnalysis>(F);
        
    for (Loop *TopLevelLoop : LI){
        outs()<<"TopLevelLoop : "<<*TopLevelLoop<<"\n"; 
    }

    areControlFlowEquivalent(LoopFusionCandidates[1] , LoopFusionCandidates[0] , DT , PDT );
    

    return PreservedAnalyses::all();
}











/* Iterazione sui cicli annidati
        for (Loop *L : depth_first(TopLevelLoop)){
            // We only handle inner-most loops.
            if (L->isInnermost())
                LoopFusionCandidates.insert(L);
        }
        */



//TENTATIVO ITERAZIONI UGUALI

/*
const SCEV *S = SE.getBackedgeTakenCount(TopLevelLoop);
        llvm::raw_ostream &OS = llvm::outs();
        S->print(OS);
        if (isa<SCEVCouldNotCompute>(S)) {
            outs()<<"Il numero di iterazione non può essere calcolato!\n";
            continue;
        }else{
            outs()<<"Il loop itera "<<*S<<" volte\n";
        }*/