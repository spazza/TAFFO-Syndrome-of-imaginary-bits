#include "llvm/Pass.h"
#include "llvm/IR/Constants.h"

#include "InputInfo.h"
#include "MultiValueMap.h"

#ifndef __TAFFO_INITIALIZER_PASS_H__
#define __TAFFO_INITIALIZER_PASS_H__

#define DEBUG_TYPE "taffo-Syndrome-of-imaginary-bits-prototype"
#define DEBUG_ANNOTATIONS "annotations"

/* 
    PARTS OF TAFFO'S CODE HAVE BEEN COPIED FROM ORIGINAL PROJECT TO DEVELOP THE PROTOTYPE
    NOW I'M TAKING INTO ACCOUNT THE MOST SIMPLE CASE, VARIABLES INSIDE A LOCAL FUNCTION 
    WITH VERY HIGH/LOW VALUES   
*/


namespace taffo{
    struct ValueInfo{
        std::shared_ptr<mdutils::MDInfo> metadata;
    };

    struct Initialization : public llvm::ModulePass{
        static char ID;

        llvm::SmallPtrSet<llvm::Function *, 32> enabledFunctions;

        Initialization(): ModulePass(ID){}
        bool runOnModule(llvm::Module &m) override;

        void readAllLocalAnnotations(llvm::Module &m, MultiValueMap<llvm::Value *, ValueInfo>& res);
        void readLocalAnnotations(llvm::Function &f, MultiValueMap<llvm::Value *, ValueInfo>& res);
       
        void parseAnnotation(MultiValueMap<llvm::Value *, ValueInfo>& res, llvm::ConstantExpr *annotationPtrInst, llvm::Value *instr);

        bool parseAnnotationString(llvm::StringRef annString);

        void propagateAnnotationsData(const MultiValueMap<llvm::Value *, ValueInfo>& val, MultiValueMap<llvm::Value *, ValueInfo>& queue);
        void updateUserMetadata(std::shared_ptr<mdutils::MDInfo> &userMetadata, const std::shared_ptr<mdutils::MDInfo> &parentMetadata);
        void setMetadataOfValue(llvm::Value *v, ValueInfo& vi);
        void removeAnnotationCalls(MultiValueMap<llvm::Value *, ValueInfo>& q);     

        void conversion(llvm::Module &m, MultiValueMap<llvm::Value *, ValueInfo> &annotatedInstructions);
    };
}

#endif 
