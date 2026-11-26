add_library(stage1_executor STATIC
    Executor.cpp
)
target_include_directories(stage1_executor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_include_directories(stage1_executor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
if(MSVC)
    target_compile_options(stage1_executor PRIVATE /W4 /WX /utf-8)
else()
    target_compile_options(stage1_executor PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()
