# 使用随课程起始工程提供的 GoogleTest 1.12.1，不联网下载。
if(NOT TARGET gtest_main)
    set(BUILD_GMOCK OFF CACHE BOOL "" FORCE)
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    set(CMAKE_POLICY_VERSION_MINIMUM 3.5)
    add_subdirectory("${CMAKE_CURRENT_LIST_DIR}/../third_party/googletest"
                     "${CMAKE_BINARY_DIR}/course-googletest" EXCLUDE_FROM_ALL)
endif()
