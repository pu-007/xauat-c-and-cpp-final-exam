# 西建大大一 C 语言全面指南 · C99 / C++11

从零基础到期末综合题，再到算法思想与 C++ 实践。依据你上传的 **6 份 PDF、258 页**整理；以 **ISO C99** 为主线，所有配套 C++ 程序使用 **ISO C++11**。代码是重新编写的教学实现，参考原题意，不照搬资料中的错误。

目标是具备冲击满分的能力；考试范围与评分仍以任课教师要求为准。这里不把题库重复次数包装成历年命题概率。

## 构建与手机阅读

支持 `xmake` 或 Make。运行 `xmake check` 编译并测试；运行 `xmake pdf` 一键生成手机版及附全部原件的PDF。依赖和命令见[构建与PDF说明](docs/19_build_pdf.md)。原始6份PDF统一放在[raw](raw/README.md)，内容保持不变。

## 第一次打开：先完成这三步

1. 阅读 [学习路线](docs/00_roadmap.md)，选“3天急救”“7天冲刺”或“完整学期”。
2. 在仓库根目录执行 `make -j4 && make test`，确认环境可以编译和运行。
3. 从[期末题型与分阶段练习](practice/exam_workbook.md)开始，先读题、手算，再打开同目录的 C 和 C++ 对照代码；完整目录见[53 组练习](docs/04_examples.md)。

```bash
# 需要 GCC/G++、Make、Python 3；不依赖第三方C/C++库
make -j4
printf '100\n' | ./build/c/03_grade
printf '100\n' | ./build/cpp/03_grade

# 单独编译：C一定用gcc，C++一定用g++
gcc -std=c99 -Wall -Wextra -Wpedantic src/03_grade.c -o grade
g++ -std=c++11 -Wall -Wextra -Wpedantic src/03_grade.cpp -o grade_cpp

make test       # 固定样例、边界、随机参考计算、算法性质检查
make sanitize   # Linux/GCC：地址/未定义行为检查及内存泄漏检查
make stats      # 从资料文本与核对表重新生成统计
```

## 怎么学习一道题：成绩等级示例

以[03 成绩等级](src/03_grade.md)为例：题目要求输入 0～100 的整数成绩，输出 A、B、C、D 或 E。先在题目页面看完整要求、样例、边界和解题步骤；输入 `100` 应输出 `A`。

1. 先自己判断 `score/10` 的结果，思考 `100` 和 `90` 为什么都归为 A，以及每个 `case` 为什么需要 `break`。
2. 打开同一目录下的 [C 代码](src/03_grade.c) 与 [C++ 代码](src/03_grade.cpp)。按注释逐句看：C 的 `scanf` 通过地址读取、`printf` 输出；C++ 版本用输入输出流。两份程序的题目和算法相同，每份都是独立可运行的程序。
3. 在仓库根目录执行 `make -j4` 后，分别运行 `printf '100\n' | ./build/c/03_grade` 和 `printf '100\n' | ./build/cpp/03_grade`，两者都应输出 `A`。再试 `59`、`60`、`89`、`90`，检查边界。
4. 合上参考代码，从空文件重写；遇到不会的题型，回到[分阶段题册](practice/exam_workbook.md)，按基础、读程序、填空改错、完整编程的顺序练习。

所有题目都通过[题目目录](docs/04_examples.md)进入：同一行提供题目、C 代码和 C++ 代码。`src/` 的同编号 `.c` 与 `.cpp` 放在一起，代码开头说明题意、算法和语言差异；可按自己的进度逐题阅读。[考频与题型](docs/02_frequency.md)保留原资料页码、统计口径和相应练习，方便返回 `raw/` 对照原题。

Windows 建议 WSL 或较新的 MinGW-w64；VC6.0 不完整支持 C99/C++11，不能用它决定这两个标准是否合法。VS 的 C 编译支持情况需按具体版本确认。

## 导航

|用途|入口|
|---|---|
|学习顺序、验收标准、时间安排|[00 学习路线](docs/00_roadmap.md)|
|6份资料出处、页码、答案覆盖边界|[01 来源说明](docs/01_sources.md)|
|题量、题型分值、复习优先级|[02 考频与题型](docs/02_frequency.md) · [期中期末依据](docs/20_exam_evidence.md) · [分阶段题型训练](practice/exam_workbook.md)|
|不要背错的原资料问题|[03 勘误](docs/03_errata.md)|
|所有配对代码与运行样例|[04 代码目录](docs/04_examples.md)|
|C基础、类型、表达式、输入输出|[05 基础](docs/05_basics.md)|
|分支循环、读程序、数值题|[06 控制结构](docs/06_control.md)|
|数组、排序、二维矩阵|[07 数组](docs/07_arrays.md)|
|字符、字符串、常用库函数|[08 字符串](docs/08_strings.md)|
|函数、存储期、递归、多文件|[09 函数](docs/09_functions.md)|
|指针、动态内存、声明辨析|[10 指针](docs/10_pointers.md)|
|结构体、共用体、枚举、链表|[11 复合类型](docs/11_records.md)|
|文件、二进制、调试、工程习惯|[12 文件与调试](docs/12_files_debug.md)|
|算法思想及复杂度阶梯|[13 算法](docs/13_algorithms.md) · [逐步推演](docs/18_algorithm_workshop.md) · [数据结构、算法与外部资源](docs/21_data_structures_algorithms.md)|
|C99与C++11差异、STL与RAII|[14 C++桥梁](docs/14_cpp11.md)|
|六次上机实验与综合项目|[15 实验手册](docs/15_labs.md)|
|全知识点查漏与附加题类型|[16 知识地图](docs/16_coverage.md)|
|原卷解析、模拟题、练习空白稿|[practice](practice/README.md)|
|测试范围和结果|[验证记录](docs/17_validation.md)|

## 仓库结构和使用约定

- `src/`：53 组按题号相邻的 C99 `.c` 与 C++11 `.cpp` 独立程序，例如 `08_prime.c` 和 `08_prime.cpp`；每个文件都包含题意、解法、对照和注释。
- `tests/cases/`：输入与期望输出。练习程序不打印冗余输入提示，便于重定向和自动核对。
- `data/sources/`：PDF逐页抽取文本；S5另有双栏阅读辅助。排版与公式以原PDF为准。
- `data/section_counts.csv`：人工核对的题量；`page_keyword_hits.csv`仅为关键词检索。
- `tools/`：统计、搜索、验证工具。构建不需要PDF工具，重新抽取PDF才需要PyMuPDF。

输入范围写在每个程序头部；超出明确范围或读取失败通常返回状态码1。数值输入假定词法合法且可表示为对应读取类型；这不是面向恶意输入的通用解析器。中文文本使用UTF-8，字符串长度按字节；字符分类练习以单字节英语文本为对象。

**考试代码与拓展代码的界线：** 题目要求冒泡、指针、特定函数签名时，必须按要求手写；`std::sort`只用于对应的 C++ 实践版。拓展算法不计入原资料考频。

资料来自用户上传，原作者权利不变。仓库用于个人学习；未将原PDF自动上传或发布。没有为整个仓库附加会覆盖原资料的开源许可证。
