#include "llvm/Support/Debug.h"

#include "TypeUtils.h"
#include "Conversion.h"

using namespace taffo;
using namespace llvm;

bool Conversion::performConversion(llvm::Module &m, MultiValueMap<llvm::Value *, ValueInfo> &annotatedInstructions){
    LLVM_DEBUG(dbgs() << " ----- CONVERSION PHASE ----- \n");

    MultiValueMap<llvm::Value *, mdutils::FPType> annotatedFPInstructions;
    createFixedPointFromAnnotation(annotatedInstructions, annotatedFPInstructions);


    LLVM_DEBUG(dbgs() << " ----- END OF CONVERSION PHASE ----- \n\n");
    return true;
}

void Conversion::createFixedPointFromAnnotation(MultiValueMap<llvm::Value *, ValueInfo> &annotatedInstructions, 
                                                MultiValueMap<llvm::Value *, mdutils::FPType> &translatedFP){

    for(auto mapElement = annotatedInstructions.begin(); mapElement != annotatedInstructions.end(); ++mapElement){
        mdutils::InputInfo *ii = cast<mdutils::InputInfo>(mapElement -> second.metadata.get());
        mdutils::FPType fp = taffo::fixedPointTypeFromRange(*(ii -> IRange));

        errs() << "Value: " << fp.toString() << "\n";    

    }
}
