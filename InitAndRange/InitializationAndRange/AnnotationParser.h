#include <string>
#include <sstream>
#include "InitAndRange.h"

#ifndef __ANNOTATION_PARSER_H__
#define __ANNOTATION_PARSER_H__

namespace taffo{
    class AnnotationParser {
        std::istringstream sstream;
        std::string error;

        void reset();
        bool parse();

    
    public:
        llvm::Optional<std::string> target;
        bool startingPoint;
        bool backtracking;
        unsigned int backtrackingdepth;
        std::shared_ptr<mdutils::MDInfo> metadata;

        bool parseAnnotationString(llvm::StringRef annStr);
        llvm::StringRef lastError();
    };
}

#endif 