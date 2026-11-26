add_library(stage2_executor STATIC
    Command.cpp
    Executor.cpp
)
target_include_directories(stage2_executor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_include_directories(stage2_executor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
if(MSVC)
    target_compile_options(stage2_executor PRIVATE /W4 /WX /utf-8)
else()
    target_compile_options(stage2_executor PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()
