# Assignment 3

## Consegna

• A partire dal codice della esercitazione 4, implementare un passo di Loop-Invariant Code Motion (LICM).

## Algoritmo per la Code Motion 

• Dato un insieme di nodi in un loop: 

1. Calcolare le <b>reaching definitions</b>.

2. Trovare le istruzioni <b>loop-invariant</b>.
   
3. Calcolare i <b>dominatori</b> (dominance tree)

4. Trovare le <b>uscite del loop</b> (i successori fuori dal loop)
   
5. Trovare le <b>istruzioni candidate alla code motion</b>:              (le condizioni devono essere tutte vere)
   1. Sono loop invariant
   2. Si trovano in blocchi che dominano tutte le uscite del loop <b>OPPURE</b> la variabile definita dall’istruzione è dead all’uscita del loop.
   3. Assegnano un valore a variabili non assegnate altrove nel loop
   4. Si trovano in blocchi che dominano tutti i blocchi nel loop che usano la variabile a cui si sta assegnando un valore

6. Eseguire una ricerca <b>depth-first</b> dei blocchi

7. Spostare l’istruzione candidata nel <b>preheader</b> se tutte le istruzioni
invarianti da cui questa dipende sono state spostate.


## Rappresentazione grafica del problema

### Control Flow Graph of .ll code (No mem2reg opt)  --- [C style]

<img src="img/LICM_no_mem2reg.png" alt="DU" width=70%></img>  

<br><br>

---

### Control Flow Graph of .ll code (with mem2reg opt)  --- [C style]

<br>

<img src="img/LICM_mem2reg.png" alt="DU" width=70%></img>

<br><br>

### Control Flow Graph of .ll code (with mem2reg opt) --- [IR style]

<br>

<img src="img/LICM_mem2reg_IR.png" alt="DU" width=70%></img>   
<br><br><br>



## Steps

1. Seguire lo step di inizializzazione del passo in <b>Esercitazione4</b>

2. Generare il file .ll nel seguente modo:

    ```bash
    echo "Avvio scripting per creazione MEM2REG file"
    INSTALL/bin/clang -S -emit-llvm -O0 TEST/source_c_files/LICM.c -o LICM_no_opt.ll -Xclang -disable-O0-optnone
    INSTALL/bin/opt -p=mem2reg LICM_no_opt.ll -o LICM_no_opt.bc 
    INSTALL/bin/llvm-dis LICM_no_opt.bc -o LICM.ll
    echo "Script terminato, risultato salvato in LICM.ll"
    echo "Eliminazione file intermedi"
    rm LICM_no_opt.bc
    rm LICM_no_opt.ll
    ```

3. Commentare le righe che incominciano con `attributes #...`

4. Cambiare il codice di <b> LoopPasses.cpp </b>

    ```c++
    #include "llvm/Transforms/Utils/LoopPasses.h"
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
    void move_to_preheader(Loop *L,
                        std::set<Instruction *> &loop_invariant_instructions)
    {
    BasicBlock *preheader = L->getLoopPreheader();
    Instruction *terminator = preheader->getTerminator();

    for (Instruction *inst : loop_invariant_instructions)
    {
        inst->moveBefore(terminator);
    }

    outs() << "Moved Loop Invariant Instructions to preheader!\n";
    }

    /**
    * @brief Controlla se un operando è definito fuori dal loop
    *
    */
    bool isDefinedOutside(Value *Operand, Loop &L)
    {
    Instruction *I_temp = dyn_cast<Instruction>(Operand);
    if (I_temp != NULL)
    {
        return !(L.contains(I_temp->getParent()));
    }
    else
    {
        return false;
    }
    }

    /**
    * @brief Controlla se l'operando è una costante
    *
    */
    bool isCostant(Value *Operand)
    {
    if (ConstantInt *C = dyn_cast<ConstantInt>(Operand))
    {
        return true;
    }
    else
    {
        return false;
    }
    }

    /**
    * @brief Aggiunge le istruzioni loop invariant a un set
    * @return std::set<Instruction *> -> il set di istruzioni loop invariant
    */
    bool isLoopInvariantCandidate(
        Value *Operand, Loop &L,
        std::set<Instruction *> loop_invariant_instructions)
    {
    Instruction *I_link = dyn_cast<Instruction>(Operand);
    return (isCostant(Operand) || isDefinedOutside(Operand, L) ||
            (I_link != NULL && (loop_invariant_instructions.count(I_link) > 0)) ||
            (isa<Argument>(Operand)));
    }

    /**
    * @brief Trova tutti i blocchi di uscita dal CFG del loop
    */
    std::set<BasicBlock *> find_exit_blocks(Loop &L)
    {
    std::set<BasicBlock *> exit_blocks;
    for (BasicBlock *BB : L.blocks())
    {
        for (Instruction &I : *BB)
        {
        if (BranchInst *BI = dyn_cast<BranchInst>(&I))
        {
            for (unsigned i = 0; i < BI->getNumSuccessors(); ++i)
            {
            BasicBlock *succ = BI->getSuccessor(i);
            if (!L.contains(succ))
            {
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
    std::set<BasicBlock *> find_exit_dominators(DominatorTree &DT, Loop &L)
    {
    std::set<BasicBlock *> exit_blocks = find_exit_blocks(L);
    std::set<BasicBlock *> exit_dominators;

    for (BasicBlock *BB : L.blocks())
    {
        bool dominates_all_exits = true;

        for (BasicBlock *exitBlock : exit_blocks)
        {
        if (!DT.dominates(BB, exitBlock))
        {
            dominates_all_exits = false;
            break;
        }
        }
        if (dominates_all_exits)
        {
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
    bool instruction_dominates_all_uses(Instruction *I, DominatorTree &DT,
                                        Loop &L)
    {
    for (User *U : I->users())
    {
        if (Instruction *userInst = dyn_cast<Instruction>(U))
        {

        // Handling speciale per nodi PHI:
        if (PHINode *phiNode = dyn_cast<PHINode>(userInst))
        {
            for (unsigned i = 0; i < phiNode->getNumIncomingValues(); ++i)
            {
            // Valutiamo solo casi che contribuiscono al nodo PHI che sono uguali
            // all'istruzione soggetta al controllo della dominanza:
            if (phiNode->getIncomingValue(i) == I)
            {
                BasicBlock *incomingBlock = phiNode->getIncomingBlock(i);
                if (!DT.dominates(I->getParent(), incomingBlock))
                {
                return false;
                }
            }
            }
        }
        else
        {

            // Istruzione Normale
            if (L.contains(userInst->getParent()) && !DT.dominates(I, userInst))
            {
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
    // bool is_dead(Instruction *I, Loop &L) {
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
    bool is_dead(Instruction *I, Loop &L)
    {
    for (User *U : I->users())
    {
        Instruction *userInst = dyn_cast<Instruction>(U);
        if (userInst && !L.contains(userInst->getParent()))
        {
        return false;
        }
    }
    return true;
    }

    PreservedAnalyses LoopPasses::run(Loop &L, LoopAnalysisManager &LAM,
                                    LoopStandardAnalysisResults &LAR,
                                    LPMUpdater &LU)
    {

    outs() << "Starting loop programm: \n\n";

    std::set<Instruction *> loop_invariant_instructions;
    std::set<Instruction *> code_motion_instructions;

    if (!L.isLoopSimplifyForm())
    {
        outs() << "\n il Loop non è in forma normale \n";
        return PreservedAnalyses::all();
    }
    BasicBlock *preheader = L.getLoopPreheader();
    if (!preheader)
    {
        errs() << "Il loop NON ha un Preheader!\n";
        return PreservedAnalyses::all();
    }
    outs() << "\nIl loop è in forma Normale e ha un Preheader!Continuo analisi\n";
    outs() << "------- Starting LICM -------\n";

    // Itera su tutte le istruzioni del loop e verifica se sono invarianti
    for (auto BI = L.block_begin(); BI != L.block_end(); ++BI)
    {
        BasicBlock &BB = **BI;
        for (auto &I : BB)
        {
        bool isLoopInvariant = true;
        PHINode *phi_node = dyn_cast<PHINode>(&I);

        // Se l'istruzione è un nodo PHI, non è loop invariant
        if (phi_node)
        {
            isLoopInvariant = false;
        }
        else
        {
            for (auto *Iter = I.op_begin(); Iter != I.op_end(); ++Iter)
            {
            Value *Operand = *Iter;
            if (!isLoopInvariantCandidate(Operand, L,
                                            loop_invariant_instructions))
                isLoopInvariant = false;
            }
        }

        if (isLoopInvariant == true)
        {
            loop_invariant_instructions.insert(&I);
        }
        }
    }

    // Stampa le istruzioni loop invariant:
    // outs() << "\nLoop invariant instructions : \n";
    // for (const auto &element : loop_invariant_instructions) {
    //   outs() << *element << "\n";
    // }

    DominatorTree &DT = LAR.DT;
    std::set<BasicBlock *> exit_dominators = find_exit_dominators(DT, L);

    /**
    * @brief Inserimento delle istruzioni candidate alla code motion nella
    * rispettiva struttura dati
    */
    for (Instruction *inst : loop_invariant_instructions)
    {
        BasicBlock *inst_bb = inst->getParent();
        if (exit_dominators.count(inst_bb))
        {
        if (instruction_dominates_all_uses(inst, DT, L))
        {
            code_motion_instructions.insert(inst);
        }
        }
        else if (is_dead(inst, L))
        {
        code_motion_instructions.insert(inst);
        }
    }

    outs() << "\nAttempting to move instructions...\n";
    move_to_preheader(&L, code_motion_instructions);
    outs() << "------- Finished LICM -------\n\n";

    //Stampa le istruzioni candidate alla code motion:
        outs() << "\nCode Motion Instructions: \n";
        for (const auto &element : code_motion_instructions) {
        outs() << *element << "\n";
    }

    return PreservedAnalyses::all();
    }
    ```
<br>

5. Cambiare il codice di <b> LoopPasses.h </b>

    ```c++
    #ifndef LLVM_TRANSFORMS_LOOPPASSES_H
    #define LLVM_TRANSFORMS_LOOPPASSES_H

    #include "llvm/IR/PassManager.h"
    #include "llvm/Transforms/Scalar/LoopPassManager.h"


    namespace llvm {
        class LoopPasses : public PassInfoMixin<LoopPasses> {
            public:
            PreservedAnalyses run(Loop &L, LoopAnalysisManager &LAM , LoopStandardAnalysisResults &LAR, LPMUpdater &LU);
        };
    } // namespace llvm


    #endif // LLVM_TRANSFORMS_TESTPASS _H

    ```

<br>

6. Lanciare i seguenti comandi

    ```bash
    INSTALL/bin/opt -p loop_pass TEST/LICM.ll -o temp.bc
    INSTALL/bin/llvm-dis temp.bc -o LICM_opt.ll
    rm temp.bc
    ```





