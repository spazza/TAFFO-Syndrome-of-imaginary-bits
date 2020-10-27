#include <string>
#include <sstream>
#include "InitializerPass.h"

#ifndef __ANNOTATION_PARSER_H__
#define __ANNOTATION_PARSER_H__

namespace taffo{
    /**
     * Class used to extract information from a string representing an annotation. In this prototype there are two types of annotations available:
     * - strange-float that represents a double with some bit set to 0 after the '.' in order to represent values that are out of bounds of the double numbers,
     *   also a range for these numbers must be provided. (__attribute((annotate("strange-float [skippedBits] [minRange] [maxRange]")));)
     * - strange-fixed-point TO BE IMPLEMENTED
     **/
    class AnnotationParser {
    private:
        /**
         * String stream used to manipulate the information inside the annotation
         **/
        std::istringstream sstream;

        /**
         * Check which strange annotation is contained in the read string
         * @return true if the reading process is successful, false otherwise
         **/
        bool parseStrangeAnnotation();

        /**
         * Parse all the information inserted in the strange float annotation, therefore the number of skipped bits and the range. Also instruction metadata
         * are updated. In addition some checks on the skipped bits and the range are introduced.
         * @return true if the parsing procedure is successful, false otherwise
         **/
        bool parseStrangeFloat();


        bool parseStrangeFixedPoint();

        /**
         * Check if an overflow occurs in a double variable, it seems that when a too high/low value is read from an annotation its value is aprroximated to 0.0
         * @param value variable to be analyzed
         * @return true if overflow occurs, otherwise false
         **/
        bool checkOverflow(double value);

        /**
         * Set the a bound of the range, in case an overflow occurs show a warning message and set the bound to the bound limit
         * @param value variable to be set
         * @param boundLimit value to be assigned in case an overflow occurs
         * @return previous value of the range bound, otherwise the bound limit in case of overflow
         **/
        double setRangeBound(double value, double boundLimit);

        /**
         * Analyze the skipped bits checking if the variable representing them is a natural number
         * @param skippedBits variable representing the skipped bits
         * @return the new value of the skipped bits, in case no problem occurs the previous value is returned
         **/
        int setSkippedBits(int skippedBits);
   
    public:
        /**
         * Variable containing the metadata extracted from the annotation
         **/
        std::shared_ptr<mdutils::MDInfo> metadata;

        /**
         * Parse the data inserted in the passed string if it is valid. The string representation changes passing from llvm::StringRef to std::isstringstream.
         * @param annStr string containing the annotation
         * @return true if the parsing procedure is successful, false otherwise
         **/
        bool parseAnnotationString(llvm::StringRef annStr);
    };
}

#endif 
