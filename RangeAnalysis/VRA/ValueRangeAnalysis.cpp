#include "llvm/ADT/DenseMap.h"

#include "ValueRangeAnalysis.h"

using namespace taffo;
using namespace llvm;

char ValueRangeAnalysis::ID = 0;

static RegisterPass<ValueRangeAnalysis> X("VRA", "Value Range Analysis Pass", false, false);

bool ValueRangeAnalysis::runOnModule(Module &m){
  LLVM_DEBUG(dbgs() << " ----- VRA PASS ----- \n");

	harvestMetadata(m);

  processModule(m);

  LLVM_DEBUG(dbgs() << " ----- END OF VRA PASS ----- \n");

	return true;
}

void ValueRangeAnalysis::harvestMetadata(llvm::Module &m){
  mdutils::MetadataManager &MDManager = mdutils::MetadataManager::getMetadataManager();

  for(llvm::Function &f : m.functions())
    for(auto &&bb : f.getBasicBlockList())
      for(auto &i : bb.getInstList()){
        mdutils::MDInfo *MDI = MDManager.retrieveMDInfo(&i);
        if(!MDI)
          continue;
        if(mdutils::InputInfo *II = dyn_cast<mdutils::InputInfo>(MDI)){
          if(isValidRange(II -> IRange.get())){
            const llvm::Value* i_ptr = &i;
            user_input[i_ptr] = make_range(II -> IRange -> Min, II -> IRange -> Max, II -> isFinal());
          }
        }     
      }
}

void ValueRangeAnalysis::processModule(llvm::Module &m){
  for(llvm::Function &f : m.functions())
    for(auto &&bb : f.getBasicBlockList())
      processBasicBlock(bb);

}



bool ValueRangeAnalysis::isValidRange(mdutils::Range *rng) {
  return rng != nullptr && !std::isnan(rng->Min) && !std::isnan(rng->Max);
} 

