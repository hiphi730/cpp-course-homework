# C++ 课程实验作业

孙弋格 · 2025310202019

[浏览五个实验的源码和测试](./2025310202019_孙弋格/) · [下载提交压缩包](./2025310202019_孙弋格.zip)

五个实验按阶段分别保存。每个实验的 `include/`、`src/` 和 `tests/` 分别包含公开接口、实现和单元测试。完整目录共用课程提供的 GoogleTest 1.12.1。

## 运行测试

完整解压提交包，或克隆仓库。进入含有五个实验的 `2025310202019_孙弋格` 文件夹。

Windows 下使用课程 MinGW-w64，请确保支持 C++17 的 `g++` 和 `mingw32-make` 在 PATH 中。在命令提示符中运行：

```bat
script\build_and_run.bat
```

脚本自动把编译所需文件复制到临时英文目录，在临时盘符下编译并运行五组测试，完成后清理，最后显示 `All five stages passed.`。此方式无需安装 Ninja 或 CMake。[Windows 自动测试记录](https://github.com/hiphi730/cpp-course-homework/actions/workflows/windows.yml)

macOS 或 Linux 使用 CMake 3.16 及以上和 C++17 编译器，运行：

```sh
sh script/build_and_run.sh
```

五个阶段分别包含 18、35、36、65、267 个 GoogleTest 用例，共 421 个。
