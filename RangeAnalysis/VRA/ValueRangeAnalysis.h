#include "llvm/Pass.h"

#include "Range.h"
#include "Metadata.h"

#define DEBUG_VRA "ValueRangeAnalysis"
#define DEBUG_TYPE "VRA"

#ifndef TAFFO_VALUE_RANGE_ANALYSIS_HPP
#define TAFFO_VALUE_RANGE_ANALYSIS_HPP


namespace taffo {

    struct ValueRangeAnalysis : public llvm::ModulePass {
	    static char ID;

    public:
	    ValueRangeAnalysis(): ModulePass(ID) { }

	    bool runOnModule(llvm::Module &M) override;

    private:
	    void harvestMetadata(llvm::Module &M);
        void processModule(llvm::Module &M);
        void processBasicBlock(llvm::BasicBlock &bb);
        const generic_range_ptr_t fetchInfo(const llvm::Value* v, bool derived_or_final = false);
        bool isValidRange(mdutils::Range *rng);

        llvm::DenseMap<const llvm::Value *, generic_range_ptr_t> user_input;
    };
}

#endif 