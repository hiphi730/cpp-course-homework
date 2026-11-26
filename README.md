# C++ 课程实验作业

孙弋格 · 2025310202019

[浏览五个实验的源码和测试](./2025310202019_孙弋格/) · [下载提交压缩包](./2025310202019_孙弋格.zip)

五个实验按阶段分别保存。每个实验的 `include/`、`src/` 和 `tests/` 分别包含公开接口、实现和单元测试。完整目录共用课程提供的 GoogleTest 1.12.1。

## 运行测试

需要 CMake 3.16 或更高版本，以及支持 C++17 的编译器。解压作业包或克隆仓库后，先进入含有五个实验的 `2025310202019_孙弋格` 文件夹。

在 Windows 课程用 MinGW 环境中运行：

```bat
cmake -S . -B build-mingw -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Debug
cmake --build build-mingw --parallel
cd build-mingw
ctest -C Debug --output-on-failure
```

在 macOS 或 Linux 上运行：

```sh
sh script/build_and_run.sh
```

CTest 分别运行五个阶段的测试程序。一共包含 421 个 GoogleTest 用例。五个程序均通过时，CTest 会显示 `100% tests passed, 0 tests failed out of 5`。
