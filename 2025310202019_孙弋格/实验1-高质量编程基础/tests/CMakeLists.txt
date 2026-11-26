add_executable(stage1_tests
    ExecutorTest.cpp
)
target_include_directories(stage1_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src")
target_link_libraries(stage1_tests PRIVATE stage1_executor gtest_main)
if(MSVC)
    target_compile_options(stage1_tests PRIVATE /W4 /WX /utf-8)
else()
    target_compile_options(stage1_tests PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()
add_test(NAME stage1_tests COMMAND stage1_tests)
