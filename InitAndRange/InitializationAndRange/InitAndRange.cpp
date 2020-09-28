#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/LegacyPassManager.h"
#include "llvm/Transforms/IPO/PassManagerBuilder.h"
#include "llvm/Support/Debug.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Constants.h"

#include "InitAndRange.h"

using namespace llvm;
using namespace taffo;

char InitAndRange::ID = 0;

static RegisterPass<InitAndRange> X("InitAndRange", "Initialization and Range pass", false, true);

bool InitAndRange::runOnModule(llvm::Module &m) {
    LLVM_DEBUG(dbgs() << "[Initialization and Range pass]\n");

    MultiValueMap<llvm::Value *, ValueInfo> localAnnotations;
    
    readAllLocalAnnotations(m, localAnnotations);

    LLVM_DEBUG(dbgs() << " ----- END OF INIT PASS ----- \n\n");

    MultiValueMap<llvm::Value *, ValueInfo>::iterator itMap;

    for(itMap = localAnnotations.begin(); itMap != localAnnotations.end(); ++itMap){
        LLVM_DEBUG(dbgs() << "Value: " << itMap -> first << " -- " << itMap -> second.metadata.get()  << " \n");
    }  
    //definire tipo apposta per float con range oltre i limiti       

    return true;
}

/*static RegisterStandardPasses Y(
    PassManagerBuilder::EP_EarlyAsPossible,[](const PassManagerBuilder &Builder, legacy::PassManagerBase &PM){ PM.add(new InitAndRange()); }
);*/



