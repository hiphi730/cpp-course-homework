add_executable(stage2_tests
    ExecutorFastTest.cpp
    ExecutorTest.cpp
)
target_include_directories(stage2_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src")
target_link_libraries(stage2_tests PRIVATE stage2_executor gtest_main)
if(MSVC)
    target_compile_options(stage2_tests PRIVATE /W4 /WX /utf-8)
else()
    target_compile_options(stage2_tests PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()
add_test(NAME stage2_tests COMMAND stage2_tests)
