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

#include "InitializerPass.h"
#include "Metadata.h"
#include "InputInfo.h"
#include "TypeUtils.h"
#include "Conversion.h"
#include <iostream>

using namespace llvm;
using namespace taffo;

char Initialization::ID = 0;

static RegisterPass<Initialization> X("StrangeBitsPrototype", "Strange bits prototype pass", false, true);

bool Initialization::runOnModule(llvm::Module &m) {
    LLVM_DEBUG(dbgs() << " ----- INITIALIZATION PHASE ----- \n");

    MultiValueMap<llvm::Value *, ValueInfo> localAnnotations;
    
    readAllLocalAnnotations(m, localAnnotations);

    MultiValueMap<llvm::Value *, ValueInfo> instructionsAnnotated;
    propagateAnnotationsData(localAnnotations, instructionsAnnotated);

    for(auto i: instructionsAnnotated)
        setMetadataOfValue(i -> first, i -> second);
    
    removeAnnotationCalls(instructionsAnnotated);

    for(auto i = instructionsAnnotated.begin(); i != instructionsAnnotated.end(); ++i)
        errs() << "Value: " << *(i -> first) << " , Metadata: " << i -> second.metadata->toString() << "\n";

    LLVM_DEBUG(dbgs() << " ----- END OF INITIALIZATION PHASE ----- \n\n");

    conversion(m, instructionsAnnotated);

    return true;
}

//Is it necessary?
void Initialization::setMetadataOfValue(llvm::Value *v, ValueInfo& vi){
    std::shared_ptr<mdutils::MDInfo> md = vi.metadata;
    if(Instruction *inst = dyn_cast<Instruction>(v)){
        if(mdutils::InputInfo *ii = dyn_cast<mdutils::InputInfo>(md.get()))
            mdutils::MetadataManager::setInputInfoMetadata(*inst, *ii);
    }
}

//some instructions has not a name, but are users of the value (don't have "return value") 
//range of result overwritten, by the metadata of used instructions
void Initialization::propagateAnnotationsData(const MultiValueMap<llvm::Value *, ValueInfo>& annotations, MultiValueMap<llvm::Value *, ValueInfo>& affectedInstrQueue){
    affectedInstrQueue.insert(affectedInstrQueue.begin(), annotations.begin(), annotations.end());

    for(auto queueElement = affectedInstrQueue.begin(); queueElement != affectedInstrQueue.end(); ++queueElement){
        llvm::Value *v = queueElement -> first;

        for(auto *u : v -> users()){        
            auto userElement = affectedInstrQueue.find(u);

            if(userElement != affectedInstrQueue.end()){
                updateUserMetadata(userElement -> second.metadata, queueElement -> second.metadata);
            }else{
                ValueInfo newValueInfo;
                newValueInfo.metadata.reset(queueElement -> second.metadata -> clone());
                affectedInstrQueue.push_back(u, newValueInfo);
            }          
        }
    }
}

void Initialization::updateUserMetadata(std::shared_ptr<mdutils::MDInfo> &userMetadata, const std::shared_ptr<mdutils::MDInfo> &parentMetadata){
    mdutils::InputInfo *parentInfo = cast<mdutils::InputInfo>(parentMetadata.get());
    mdutils::InputInfo *userInfo = cast<mdutils::InputInfo>(userMetadata.get());

    if(parentInfo -> skippedBits < userInfo -> skippedBits)
        userInfo -> skippedBits = parentInfo -> skippedBits;

    if(parentInfo -> IRange -> Min < userInfo -> IRange -> Min)
        userInfo -> IRange -> Min = parentInfo -> IRange -> Min;

    if(parentInfo -> IRange -> Max > userInfo -> IRange -> Max)
        userInfo -> IRange -> Max = parentInfo -> IRange -> Max;
}

void Initialization::removeAnnotationCalls(MultiValueMap<llvm::Value *, ValueInfo>& q){
  for (auto i = q.begin(); i != q.end();) {
    Value *v = i->first;
    
    if (CallInst *anno = dyn_cast<CallInst>(v)) {
      if (anno->getCalledFunction()) {
        if (anno->getCalledFunction()->getName() == "llvm.var.annotation") {
          i = q.erase(i);
          anno->eraseFromParent();
          continue;
        }
      }
    }    
    i++;
  }
}

void Initialization::conversion(llvm::Module &m, MultiValueMap<llvm::Value *, ValueInfo> &annotatedInstructions){
    Conversion c;
    c.performConversion(m, annotatedInstructions);
}