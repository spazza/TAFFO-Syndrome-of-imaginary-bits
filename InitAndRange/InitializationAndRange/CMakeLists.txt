add_llvm_library(InitializationAndRange MODULE
    InitAndRange.h
    InitAndRange.cpp
    AnnotationParser.h
    AnnotationParser.cpp
    Annotations.cpp

    PLUGIN_TOOL
    opt
)

set_property(TARGET InitializationAndRange PROPERTY CXX_STANDARD 11)
set_property(TARGET InitializationAndRange PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(InitializationAndRange TaffoUtils)