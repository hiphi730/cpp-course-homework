add_executable(stage4_tests
    ExecutorFastTest.cpp
    ExecutorReverseTest.cpp
    ExecutorTest.cpp
)
target_include_directories(stage4_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src")
target_link_libraries(stage4_tests PRIVATE stage4_executor gtest_main)
if(MSVC)
    target_compile_options(stage4_tests PRIVATE /W4 /WX /utf-8)
else()
    target_compile_options(stage4_tests PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()
add_test(NAME stage4_tests COMMAND stage4_tests)
