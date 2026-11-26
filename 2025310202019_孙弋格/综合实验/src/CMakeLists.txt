add_library(stage5_executor STATIC
    Executor.cpp
    action/ActionGroup.cpp
    command/Command.cpp
    command/CommandFactory.cpp
    pose/PoseHandler.cpp
)
target_include_directories(stage5_executor PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/../include")
target_include_directories(stage5_executor PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")
if(MSVC)
    target_compile_options(stage5_executor PRIVATE /W4 /WX /utf-8)
else()
    target_compile_options(stage5_executor PRIVATE -Wall -Wextra -Werror -Wpedantic)
endif()
