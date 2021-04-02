#include "llvm/IR/Module.h"
#include "llvm/IR/Value.h"
#include "llvm/ADT/DenseMap.h"

#include "MultiValueMap.h"
#include "InitializerPass.h"

#ifndef __CONVERSION_H__
#define __CONVERSION_H_

namespace taffo{

    struct Conversion {
    public:
        bool performConversion(llvm::Module &m, MultiValueMap<llvm::Value *, ValueInfo> &annotatedInstructions);

    private:
        llvm::DenseMap<llvm::Value *,llvm::Value *> convertedValuePool;

        void createFixedPointFromAnnotation(MultiValueMap<llvm::Value *, ValueInfo> &annotatedInstructions, MultiValueMap<llvm::Value *, mdutils::FPType> &translatedFP);

    };
}

#endif