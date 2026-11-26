add_library(stage3_executor STATIC
    Command.cpp
    Executor.cpp
    PoseHandler.cpp
)
target_include_directories(stage3_executor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_include_directories(stage3_executor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
if(MSVC)
    target_compile_options(stage3_executor PRIVATE /W4 /WX /utf-8)
else()
    target_compile_options(stage3_executor PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()
