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
