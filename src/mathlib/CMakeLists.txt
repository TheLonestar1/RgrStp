set(target_name math)


add_library(${target_name} STATIC
    Matrixlib.cpp
    ${PROJECT_SOURCE_DIR}/include/Matrixlib/Matrixlib.hpp)

    include(CompileOptions)
    set_compile_options(${target_name})

    target_include_directories(
  ${target_name}
  PUBLIC
    ${CMAKE_CURRENT_LIST_DIR}
    ${PROJECT_SOURCE_DIR}/include/
    )
