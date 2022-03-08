#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "InitializerPass.h"
#include "AnnotationParser.h"

using namespace llvm;
using namespace taffo;

/**
 * For each function in the module read all the local annotations contained inside and insert them in the map containing all the annotations.
 * Finally remove the annotations from each function.
 * @param m main llvm module
 * @param annotations map containing all the annotations of all the functions 
 **/
void Initialization::readAllLocalAnnotations(llvm::Module &m, MultiValueMap<llvm::Value *, ValueInfo>& annotations){
    for(Function &f: m.functions()){
        MultiValueMap<Value *, ValueInfo> tmp;
        readLocalAnnotations(f,tmp);
        annotations.insert(annotations.end(), tmp.begin(), tmp.end());
        f.removeFnAttr(Attribute::OptimizeNone);
    }   
}

/**
 * Read all the annotations contained in a function, first scan all the calling instructions and then find the llvm annotations. Finally add the annotation 
 * inside the annotations' map.
 * @param f function to be scan
 * @param annotations map containing all the annotations of all the functions
 **/
void Initialization::readLocalAnnotations(llvm::Function &f, MultiValueMap<llvm::Value *, ValueInfo>& annotations){   
    for(inst_iterator iIt = inst_begin(&f), iItEnd = inst_end(&f); iIt != iItEnd; iIt++) 
        if(CallInst *call = dyn_cast<CallInst>(&(*iIt))){
            if(!call -> getCalledFunction())
                continue;
            if(call -> getCalledFunction() -> getName() == "llvm.var.annotation")
                parseAnnotation(annotations, cast<ConstantExpr>(iIt -> getOperand(1)), iIt -> getOperand(0));       
        }    
}

void Initialization::parseAnnotation(MultiValueMap<llvm::Value *, ValueInfo>& annotation, ConstantExpr *annotationPtrInst, llvm::Value *instr){
    GlobalVariable *annotationContent = dyn_cast<GlobalVariable>(annotationPtrInst -> getOperand(0));
    if(!annotationContent)
        return;
    ConstantDataSequential *annotationStr = dyn_cast<ConstantDataSequential>(annotationContent -> getInitializer());
    if(!annotationStr) 
        return;
    if(!(annotationStr -> isString()))
        return;

    StringRef annStr = annotationStr -> getAsString();
    AnnotationParser parser;
    if(!parser.parseAnnotationString(annStr)){
        errs() << "TAFFO annotation parser syntax error: \n";
        errs() << " In annotation: \"" << annStr << "\"\n";
        return;
    }

    ValueInfo vi;
    vi.metadata = parser.metadata;

    if(Instruction *toconv = dyn_cast<Instruction>(instr))
        annotation.push_back(toconv -> getOperand(0), vi);
}
