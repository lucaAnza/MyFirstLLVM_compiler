#include "llvm/Transforms/Utils/LoopInterchangePasses.h"
#include "llvm/Analysis/DominanceFrontier.h"
#include "llvm/Analysis/LoopInfo.h"
#include "llvm/Analysis/PostDominators.h"
#include "llvm/IR/Dominators.h"
#include "llvm/IR/InstrTypes.h"
#include "llvm/IR/Instructions.h"
#include <llvm/IR/Constants.h>

using namespace llvm;

/**
 * @brief Sposta le istruzioni invarianti del loop nel preheader
 *
 */

void move_to_preheader2(Loop *L, std::set<Instruction*> &loop_invariant_instructions) {
  BasicBlock *preheader = L->getLoopPreheader();
  Instruction *terminator = preheader->getTerminator();

  for (Instruction *inst : loop_invariant_instructions) {
    inst->moveBefore(terminator);
  }

  outs() << "Moved Loop Invariant Instructions to preheader!\n";
}

/**
 * @brief Controlla se un operando è definito fuori dal loop
 *
 */
bool isDefinedOutside2(Value *Operand, Loop &L) {
  Instruction *I_temp = dyn_cast<Instruction>(Operand);
  if (I_temp != NULL) {
    return !(L.contains(I_temp->getParent()));
  } else {
    return false;
  }
}

/**
 * @brief Controlla se l'operando è una costante
 *
 */
bool isConstant2(Value *Operand) {
  if (ConstantInt *C = dyn_cast<ConstantInt>(Operand)) {
    return true;
  } else {
    return false;
  }
}

/**
 * @brief Aggiunge le istruzioni loop invariant a un set
 * @return std::set<Instruction *> -> il set di istruzioni loop invariant
 */
bool isLoopInvariantCandidate2( Value *Operand, Loop &L, std::set<Instruction *> loop_invariant_instructions) {
  Instruction *I_link = dyn_cast<Instruction>(Operand);
  return (isConstant2(Operand) || isDefinedOutside2(Operand, L) ||
          (I_link != NULL && (loop_invariant_instructions.count(I_link) > 0)) ||
          (isa<Argument>(Operand)));
}

/**
 * @brief Trova tutti i blocchi di uscita dal CFG del loop
 */
std::set<BasicBlock *> find_exit_blocks2(Loop &L) {
  std::set<BasicBlock *> exit_blocks;
  for (BasicBlock *BB : L.blocks()) {
    for (Instruction &I : *BB) {
      if (BranchInst *BI = dyn_cast<BranchInst>(&I)) {
        for (unsigned i = 0; i < BI->getNumSuccessors(); ++i) {
          BasicBlock *succ = BI->getSuccessor(i);
          if (!L.contains(succ)) {
            exit_blocks.insert(succ);
          }
        }
      }
    }
  }
  return exit_blocks;
}

/**
 * @brief Trova e aggiunge a un set tutti i blocchi che dominano tutte le uscite
 * del loop
 *
 * @return std::set<BasicBlock *> -> set di blocchi che dominano tutte le uscite
 */
std::set<BasicBlock *> find_exit_dominators2(DominatorTree &DT, Loop &L) {
  std::set<BasicBlock *> exit_blocks = find_exit_blocks2(L);
  std::set<BasicBlock *> exit_dominators;

  for (BasicBlock *BB : L.blocks()) {
    bool dominates_all_exits = true;

    for (BasicBlock *exitBlock : exit_blocks) {
      if (!DT.dominates(BB, exitBlock)) {
        dominates_all_exits = false;
        break;
      }
    }
    if (dominates_all_exits) {
      exit_dominators.insert(BB);
    }
  }
  return exit_dominators;
}

/**
 * @brief Controlla se un'istruzione domina tutti i suoi usi nel loop con
 * gestione esplcita per i nodi PHI
 *
 */
bool instruction_dominates_all_uses2(Instruction *I, DominatorTree &DT, Loop &L) {
  for (User *U : I->users()) {
    if (Instruction *userInst = dyn_cast<Instruction>(U)) {

      // Handling speciale per nodi PHI:
      if (PHINode *phiNode = dyn_cast<PHINode>(userInst)) {
        for (unsigned i = 0; i < phiNode->getNumIncomingValues(); ++i) {
          // Valutiamo solo casi che contribuiscono al nodo PHI che sono uguali
          // all'istruzione soggetta al controllo della dominanza:
          if (phiNode->getIncomingValue(i) == I) {
            BasicBlock *incomingBlock = phiNode->getIncomingBlock(i);
            if (!DT.dominates(I->getParent(), incomingBlock)) {
              return false;
            }
          }
        }
      } else {

        // Istruzione Normale
        if (L.contains(userInst->getParent()) && !DT.dominates(I, userInst)) {
          return false;
        }
      }
    }
  }
  return true;
}

/**
 * @brief Verifica se un'istruzione è dead code con gestione esplicita per i
 * nodi PHI
 */
// bool is_dead2(Instruction *I, Loop &L) {
//   for (User *U : I->users()) {
//     Instruction *userInst = dyn_cast<Instruction>(U);
//     if (PHINode *phi = dyn_cast<PHINode>(userInst)) {
//       outs() << "\n\n";
//       outs() << "Found PHI user of " << *I << "\n";
//       for (unsigned i = 0; i < phi->getNumIncomingValues(); ++i) {
//         if (phi->getIncomingValue(i) == I) {
//           outs() << "Instruction from PHI prospective: "
//                  << *(phi->getIncomingValue(i)) << "   --\n";
//           BasicBlock *incomingBlock = phi->getIncomingBlock(i);
//           if (!L.contains(incomingBlock)) {
//             // Se il valore arriva da un blocco fuori dal loop, non è dead
//             code return false;
//           }
//         }
//       }
//     } else if (userInst) {
//       if (!L.contains(userInst->getParent())) {
//         // Se l'istruzione è utilizzata fuori dal loop, non è dead code
//         return false;
//       }
//     }
//   }
//   return true;
// }

/**
 * @brief Verifica se un'istruzione è dead code
 *
 */
bool is_dead2(Instruction *I, Loop &L) {
  for (User *U : I->users()) {
    Instruction *userInst = dyn_cast<Instruction>(U);
    if (userInst && !L.contains(userInst->getParent())) {
      return false;
    }
  }
  return true;
}

PreservedAnalyses LoopInterchangePasses::run(Function &F, FunctionAnalysisManager &AM) {
    
    outs() << "\nStart loop fusion opt...\n";

    LoopInfo &LI = AM.getResult<LoopAnalysis>(F);
    //Possibile miglioramento vettore di <L_top , L_inner> , ...
    
    Loop *LTop = nullptr;
    Loop *LInner = nullptr;
    int cont=0; 

    //Ottenimento del LTop,LInner  (TODO-transform in function)
    for (auto lit = LI.rbegin(); lit != LI.rend(); ++lit) {
        LTop = *lit;
        outs() << "Top level loop : " << *LTop << "\n";
        auto subLoops = LTop->getSubLoops();
        for (auto subLoop : subLoops) {
            cont++;
            outs() << "Inner loop : " << *subLoop << "\n";
            LInner = subLoop;
        }
        //Check loop format
        if(cont != 1){
            outs()<<"Errore il top loop ha più di un ciclo inestato\n";
            return PreservedAnalyses::none();
        }
        cont=0;
    }

    
    PHINode *indVar1 = LTop->getCanonicalInductionVariable();
    PHINode *indVar2 = LInner->getCanonicalInductionVariable();
    // Controlla se entrambe le variabili di induzione esistono
    if (!indVar1 || !indVar2) {
        outs() << "Warning: Uno dei loop non ha variabile di induzione.\n";
        return PreservedAnalyses::none();
    }
    outs()<<"top : "<<*indVar1<<"\n";
    outs()<<"inner : "<<*indVar2<<"\n";


    for (auto *user : indVar1->users() ) {
        outs()<<"use : "<<*user<<"\n";
    }
  
    return PreservedAnalyses::all();
}


//NEXT-STEP
//for (auto *User : users) {
    //    User->replaceUsesOfWith(indVar2, indVar1);
    //}