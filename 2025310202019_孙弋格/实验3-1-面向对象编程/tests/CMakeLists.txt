add_executable(stage3_tests
    ExecutorFastTest.cpp
    ExecutorRefactorTest.cpp
    ExecutorTest.cpp
)
target_include_directories(stage3_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src")
target_link_libraries(stage3_tests PRIVATE stage3_executor gtest_main)
if(MSVC)
    target_compile_options(stage3_tests PRIVATE /W4 /WX /utf-8)
else()
    target_compile_options(stage3_tests PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()
add_test(NAME stage3_tests COMMAND stage3_tests)
