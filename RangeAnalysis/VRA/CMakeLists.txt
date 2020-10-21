add_llvm_library(VRA MODULE
    ValueRangeAnalysis.h
    ValueRangeAnalysis.cpp
    
    PLUGIN_TOOL
    opt
)

set_property(TARGET VRA PROPERTY CXX_STANDARD 11)
set_property(TARGET VRA PROPERTY CXX_STANDARD_REQUIRED ON)

target_link_libraries(VRA TaffoUtils)