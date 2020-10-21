#include <limits.h>

#include "AnnotationParser.h"

using namespace llvm;
using namespace taffo;

void AnnotationParser::reset(){
    target = None;
    metadata.reset();
}

bool AnnotationParser::parseAnnotationString(StringRef annStr){

    reset();
    sstream = std::istringstream(annStr.substr(0, annStr.size()));
    bool res = false;

    if(annStr.find('(') == StringRef::npos)
        res = parseStrangeFloat();

    return res;
}

bool AnnotationParser::parseStrangeFloat(){
    std::string head;
    sstream >> head;

    checkStrangeFloatRange(0,0);
    if(head == "strange-float"){
        mdutils::InputInfo *info = new mdutils::InputInfo(nullptr, nullptr, nullptr, true);
        metadata.reset(info);    
    
        int skippedBits;
        double min, max;
        sstream >> skippedBits >> min >> max;
        if(!sstream.fail()){
            info -> skippedBits = skippedBits;
            info -> IRange.reset(new mdutils::Range(min, max));
            LLVM_DEBUG(dbgs() << "Strange float found: [ Skipped bits: " << skippedBits << " Range: " << min << ", " << max << "]\n");
        }
    }
    return true;
}

StringRef AnnotationParser::lastError(){
    return error.empty() ? error : "parsing error";
}

bool AnnotationParser::checkStrangeFloatRange(double min, double max) {
    if(std::isinf(min))
        LLVM_DEBUG(dbgs() << "Overflow\n");
    LLVM_DEBUG(dbgs() << "Limit:" << std::numeric_limits<double>::min() << "\n");
    return true;
}
