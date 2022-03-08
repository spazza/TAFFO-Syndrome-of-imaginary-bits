#include <limits.h>

#include "AnnotationParser.h"

using namespace llvm;
using namespace taffo;

/**
 * Parse the data inserted in the passed string if it is valid. The string representation changes passing from llvm::StringRef to std::isstringstream.
 * @param annStr string containing the annotation
 * @return true if the parsing procedure is successful, false otherwise
 **/
bool AnnotationParser::parseAnnotationString(StringRef annStr){
    metadata.reset();
    sstream = std::istringstream(annStr.substr(0, annStr.size()));

    return annStr.find('(') == StringRef::npos ? parseStrangeAnnotation() : false;
}

/**
 * Check which strange annotation is contained in the read string
 * @return true if the reading process is successful, false otherwise
 **/
bool AnnotationParser::parseStrangeAnnotation(){
    std::string head;
    sstream >> head;

    if(head == "strange-float")
        return parseStrangeFloat();
    if(head == "strange-fixed-point")
        return parseStrangeFixedPoint();

    return false;
}

/**
 * Parse all the information inserted in the strange float annotation, therefore the number of skipped bits and the range. Also instruction metadata
 * are updated. In addition some checks on the skipped bits and the range are introduced.
 * @return true if the parsing procedure is successful, false otherwise
 **/
bool AnnotationParser::parseStrangeFloat(){  
    mdutils::InputInfo *info = new mdutils::InputInfo(nullptr, nullptr, nullptr, true);  
    metadata.reset(info);

    int skippedBits;
    double min, max;
    sstream >> skippedBits >> min >> max;

    if(!sstream.fail() || !sstream.bad()){  
        info -> skippedBits = setSkippedBits(skippedBits);
        info -> IRange.reset(new mdutils::Range(setRangeBound(min, std::numeric_limits<double>::min()), 
                                                setRangeBound(max, std::numeric_limits<double>::max())));
        LLVM_DEBUG(dbgs() << "Strange float found: [ Skipped bits: " << info -> skippedBits 
                        << " Range: " << info -> IRange -> Min << ", " << info -> IRange -> Max << "]\n");     
    }else{
        info -> IRange.reset(new mdutils::Range(0, 0));
        LLVM_DEBUG(dbgs() << "WARNING: Generic error while reading annotation, empty range created [Skipped bits: " 
            << 0 << " Range: " << 0 << ", " << 0 << "]\n");
        return false;
    }   
    return true;
}

bool AnnotationParser::parseStrangeFixedPoint(){
    /* 
        TO BE IMPLEMENTED
    */
    return true;
}

/**
 * Check if an overflow occurs in a double variable, it seems that when a too high/low value is read from an annotation its value is aprroximated to 0.0
 * @param value variable to be analyzed
 * @return true if overflow occurs, otherwise false
 **/
bool AnnotationParser::checkOverflow(double value) {
    return value == 0.0 ? true : false;
}

/**
 * Set the a bound of the range, in case an overflow occurs show a warning message and set the bound to the bound limit
 * @param value variable to be set
 * @param boundLimit value to be assigned in case an overflow occurs
 * @return previous value of the range bound, otherwise the bound limit in case of overflow
 **/
double AnnotationParser::setRangeBound(double value, double boundLimit){
    if(checkOverflow(value)){
        LLVM_DEBUG(dbgs() << "WARNING: overflow in a strange-float occurred range bound set to the limit, problem may be solved adding more skipped bits \n");
        return boundLimit;
    }
    return value;
}

/**
 * Analyze the skipped bits checking if the variable representing them is a natural number
 * @param skippedBits variable representing the skipped bits
 * @return the new value of the skipped bits, in case no problem occurs the previous value is returned
 **/
int AnnotationParser::setSkippedBits(int skippedBits){
    if(skippedBits < 0){
        LLVM_DEBUG(dbgs() << "WARNING: wrong skipped bits format in strange-float, value set to 0");
        return 0;
    }
    return skippedBits;
}