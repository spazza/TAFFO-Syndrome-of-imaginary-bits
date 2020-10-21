#include <string>
#include <sstream>
#include "InitializerPass.h"

#ifndef __ANNOTATION_PARSER_H__
#define __ANNOTATION_PARSER_H__

namespace taffo{
    class AnnotationParser {
        std::istringstream sstream;
        std::string error;

        void reset();
        bool parseStrangeFloat();

        bool checkStrangeFloatRange(double min, double max);
   
    public:
        llvm::Optional<std::string> target;
        std::shared_ptr<mdutils::MDInfo> metadata;

        bool parseAnnotationString(llvm::StringRef annStr);
        llvm::StringRef lastError();
    };
}

#endif 
