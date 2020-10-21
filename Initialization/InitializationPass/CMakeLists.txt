add_llvm_library(InitializationPass MODULE
    InitializerPass.h
    InitializerPass.cpp
    AnnotationParser.h
    AnnotationParser.cpp
    Annotations.cpp

    PLUGIN_TOOL
    opt
)

set_property(TARGET InitializationPass PROPERTY CXX_STANDARD 11)
set_property(TARGET InitializationPass PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(InitializationPass TaffoUtils)