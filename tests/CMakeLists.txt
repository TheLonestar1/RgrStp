set(target_name test)

add_executable(${target_name})

include(CompileOptions)
set_compile_options(${target_name})

target_sources(
  ${target_name}
  PRIVATE
    test.sum.cpp
)

target_include_directories(
    ${target_name}
    PRIVATE
    ${PROJECT_SOURCE_DIR}/external/googletest)



target_link_libraries(
  ${target_name}
  PRIVATE
    math
    gtest
    gtest_main
)
add_test(NAME ${target_name} COMMAND ${target_name})