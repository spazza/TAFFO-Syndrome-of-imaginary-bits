add_llvm_library(StrangeBitsPrototypePass MODULE
    InitializerPass.h
    InitializerPass.cpp
    AnnotationParser.h
    AnnotationParser.cpp
    Annotations.cpp
    Conversion.h
    Conversion.cpp

    PLUGIN_TOOL
    opt
)

set_property(TARGET StrangeBitsPrototypePass PROPERTY CXX_STANDARD 11)
set_property(TARGET StrangeBitsPrototypePass PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(StrangeBitsPrototypePass TaffoUtils)