add_library(Extended_fixed_point_lib
    fixed_point.hpp
    fixed_point_utils.hpp
    fixed_point_external_operators.hpp
    ufixed_point.hpp
    ufixed_point_external_operators.hpp

    extended_fixed_point.hpp
)

target_include_directories(Extended_fixed_point_lib PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")

set_target_properties(Extended_fixed_point_lib PROPERTIES LINKER_LANGUAGE CXX)