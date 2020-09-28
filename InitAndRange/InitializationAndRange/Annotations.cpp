#include "llvm/Pass.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Constants.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "InitAndRange.h"
#include "AnnotationParser.h"

using namespace llvm;
using namespace taffo;

/**
 *  Read the annotations inside the module and add them to the map res, finally delete all the attributes 
 **/
void InitAndRange::readAllLocalAnnotations(llvm::Module &m, MultiValueMap<llvm::Value *, ValueInfo>& res){
    for(Function &f: m.functions()){
        MultiValueMap<Value *, ValueInfo> t;
        readLocalAnnotations(f,t);
        res.insert(res.end(), t.begin(), t.end());
        f.removeFnAttr(Attribute::OptimizeNone);
    }
    
}

void InitAndRange::readLocalAnnotations(llvm::Function &f, MultiValueMap<llvm::Value *, ValueInfo>& res){

    for(inst_iterator iIt = inst_begin(&f), iItEnd = inst_end(&f); iIt != iItEnd; iIt++) //inst_iterator serve per scandire le istruzioni di una funzione
        if(CallInst *call = dyn_cast<CallInst>(&(*iIt))){
            if(!call -> getCalledFunction())
                continue;
            if(call -> getCalledFunction() -> getName() == "llvm.var.annotation")
                parseAnnotation(res, cast<ConstantExpr>(iIt -> getOperand(1)), iIt -> getOperand(0));
            
        }    
}

void InitAndRange::parseAnnotation(MultiValueMap<llvm::Value *, ValueInfo>& res, ConstantExpr *annotationPtrInst, Value *instr){
    ValueInfo vi;

    if(!(annotationPtrInst -> getOpcode() == Instruction::GetElementPtr)) 
        return;
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
        errs() << "  " << parser.lastError() << "\n";
        return;
    }

    vi.metadata = parser.metadata;

    if(Instruction *toconv = dyn_cast<Instruction>(instr))
        res.push_back(toconv -> getOperand(0), vi);
    else if(Function *fun = dyn_cast<Function>(instr)){
            enabledFunctions.insert(fun);
            for(auto user: fun -> users()){
                if(!(isa<CallInst>(user) || isa<InvokeInst>(user)))
                    continue;
                res.push_back(user, vi);
            }
        }else
            res.push_back(instr, vi);
}

