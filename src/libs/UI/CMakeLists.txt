add_library(UI FileSystemUI.cpp)
set_target_properties(UI PROPERTIES CXX_STANDARD 20)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    target_compile_options(UI PRIVATE "-Wall")
    target_compile_options(UI PRIVATE "-Wextra")
    target_compile_options(UI PRIVATE "-pedantic")
    target_compile_options(UI PRIVATE "-Werror")
    target_compile_options(UI PRIVATE "-Wno-sign-compare")
endif()

target_include_directories(UI PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/..)
target_link_libraries(UI
    PRIVATE ftxui::screen
    PRIVATE ftxui::dom
    PRIVATE ftxui::component
    PRIVATE operations
)
