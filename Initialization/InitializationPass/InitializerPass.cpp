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

using namespace llvm;
using namespace taffo;

char Initialization::ID = 0;

static RegisterPass<Initialization> X("Initialization", "Initialization pass", false, true);

bool Initialization::runOnModule(llvm::Module &m) {
    LLVM_DEBUG(dbgs() << " ----- INITIALIZATION PASS ----- \n");
    
    MultiValueMap<llvm::Value *, ValueInfo> localAnnotations;
    
    readAllLocalAnnotations(m, localAnnotations);

    MultiValueMap<llvm::Value *, ValueInfo> vals;
    buildConversionQueueForRootValues(localAnnotations, vals);

    for(auto V: vals)
      setMetadataOfValue(V -> first, V -> second); 
    
    removeAnnotationCalls(vals);

    for(Function &f: m.functions())
      for(inst_iterator iIt = inst_begin(&f), iItEnd = inst_end(&f); iIt != iItEnd; iIt++) 
        if(f.getName() == "main")
          errs() << *iIt << "\n";
    /*
    for(auto v: vals){
      std::shared_ptr<mdutils::MDInfo> md = v -> second.metadata;
      if(Instruction *inst = dyn_cast<Instruction>(v -> first))
        if(mdutils::MDInfo *ii = dyn_cast<mdutils::InputInfo>(md.get()))
          LLVM_DEBUG(dbgs() << "Data: " << v -> first -> getName() << " , " << ii -> toString() << "\n");
    }
    */
    LLVM_DEBUG(dbgs() << " ----- END OF INIT PASS ----- \n\n");

    return true;
}

void Initialization::setMetadataOfValue(llvm::Value *v, ValueInfo& vi){
    std::shared_ptr<mdutils::MDInfo> md = vi.metadata;
    if(Instruction *inst = dyn_cast<Instruction>(v)){
      if(mdutils::InputInfo *ii = dyn_cast<mdutils::InputInfo>(md.get()))
        mdutils::MetadataManager::setInputInfoMetadata(*inst, *ii);
    }
}

void Initialization::buildConversionQueueForRootValues(const MultiValueMap<llvm::Value *, ValueInfo>& val, MultiValueMap<llvm::Value *, ValueInfo>& queue) {

  queue.insert(queue.begin(), val.begin(), val.end());

  SmallPtrSet<llvm::Value *, 8U> visited;
  size_t prevQueueSize = 0;
  while (prevQueueSize < queue.size()) {

    prevQueueSize = queue.size();

    auto next = queue.begin();
    while (next != queue.end()) {
      Value *v = next->first;
      visited.insert(v);

      for (auto *u: v->users()) {

        auto UI = queue.find(u);
        ValueInfo UVInfo;
        if (UI != queue.end()) {
          UVInfo = UI->second;
          queue.erase(UI);
        }
        UI = queue.push_back(u, std::move(UVInfo)).first;

        UI -> second.metadata.reset(next -> second.metadata -> clone());

      }
      ++next;
    }
  }
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

