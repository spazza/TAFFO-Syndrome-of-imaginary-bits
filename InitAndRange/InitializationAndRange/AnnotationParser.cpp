#include "AnnotationParser.h"

using namespace llvm;
using namespace taffo;

void AnnotationParser::reset(){
    target = None;
    startingPoint = false;
    backtracking = false;
    metadata.reset();
}


bool AnnotationParser::parseAnnotationString(StringRef annStr){

    reset();
    sstream = std::istringstream(annStr.substr(0, annStr.size()));
    bool res = false;

    if(annStr.find('(') == StringRef::npos)
        res = parse();

    return res;
}

bool AnnotationParser::parse(){
    bool readNumBits = true;
    std::string head;
    sstream >> head;

    if(head.find("target:") == 0){
        target = head.substr(7);
        startingPoint = true;
        sstream >> head;
    }

    if(head == "range")
        readNumBits = false;
    else
        return false;
    mdutils::InputInfo *info = new mdutils::InputInfo(nullptr, nullptr, nullptr, true);
    metadata.reset(info);    

    //skipped code
    
    double min, max;
    sstream >> min >> max;
    if(!sstream.fail()){
        info -> IRange.reset(new mdutils::Range(min, max));
        LLVM_DEBUG(dbgs() << "Range found: [" << min << ", " << max << "]\n");

        //skipped code
    }

    return true;
}

StringRef AnnotationParser::lastError(){
    return error.empty() ? error : "generic error";
}

