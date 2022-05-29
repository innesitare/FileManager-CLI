add_library(operations FileSystemOperations.cpp)
set_target_properties(operations PROPERTIES CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(operations PRIVATE "-Wall")
    target_compile_options(operations PRIVATE "-Wextra")
    target_compile_options(operations PRIVATE "-pedantic")
    target_compile_options(operations PRIVATE "-Werror")
    target_compile_options(operations PRIVATE "-Wno-sign-compare")
endif()

target_include_directories(operations PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
