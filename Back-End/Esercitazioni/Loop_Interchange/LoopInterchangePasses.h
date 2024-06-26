#ifndef LLVM_TRANSFORMS_LOOPINTERCHANGEPASSES_H
#define LLVM_TRANSFORMS_LOOPINTERCHANGEPASSES_H

#include "llvm/IR/PassManager.h"
#include "llvm/Transforms/Scalar/LoopPassManager.h"


namespace llvm {
    class LoopInterchangePasses : public PassInfoMixin<LoopInterchangePasses> {
        public:
        PreservedAnalyses run(Function &F, FunctionAnalysisManager &AM);
    };
} // namespace llvm


#endif // LLVM_TRANSFORMS_TESTPASS _H
