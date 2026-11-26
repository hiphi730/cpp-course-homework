add_executable(stage5_tests
    ActionGroupTest.cpp
    ExecutorFastTest.cpp
    ExecutorReverseTest.cpp
    ExecutorTest.cpp
    ExecutorTurnRoundTest.cpp
    VehicleTypeTest.cpp
)
target_include_directories(stage5_tests PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/../src")
target_link_libraries(stage5_tests PRIVATE stage5_executor gtest_main)
if(MSVC)
    target_compile_options(stage5_tests PRIVATE /W4 /WX /utf-8)
else()
    target_compile_options(stage5_tests PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()
add_test(NAME stage5_tests COMMAND stage5_tests)
