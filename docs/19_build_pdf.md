# 构建程序与一键生成PDF

只想看书：直接打开dist里的手机版PDF。想写代码：先构建，再运行一个练习。Make与xmake任选一个，不必同时使用。

## 用xmake编译

需要较新的GCC/Clang、Python 3和xmake 2.9或更高版本。本仓库实际验证使用xmake 3.1.2。

```bash
xmake f -m release
xmake
xmake run c_03_grade
xmake run cpp_03_grade
xmake check
```

`xmake`构建全部90个独立程序。C目标名以`c_`开头，C++目标名以`cpp_`开头。例如`c_44_reservations`是订餐链表版。生成文件在`build/xmake/c/`与`build/xmake/cpp/`。

运行成绩程序后若终端暂时空白，输入一个0–100的整数并回车，例如100。

`xmake check`会先编译，再运行基础、算法、实验测试和仓库完整性检查。使用的仍是C99与C++11，不会自动升级语言标准。

```bash
# 直接运行二进制并重定向输入
./build/xmake/c/44_reservations < labs/data/bookings.txt

# 只编译一个目标
xmake build c_08_prime

# 调试构建
xmake f -m debug
xmake build c_17_pointers
```

Windows建议使用MinGW-w64或WSL来学习严格C99。MSVC对C标准的支持与GCC不同；仅有xmake并不会改变编译器能力。

## 用Make编译

```bash
make -j4
make test
make sanitize
```

Make输出在`build/c/`与`build/cpp/`，与xmake输出分开，避免互相覆盖。

## 第一次生成PDF：安装依赖

生成PDF需要四项：Python 3、Pandoc 3、XeLaTeX、Noto CJK中文字体；合并原PDF还需要PyMuPDF。代码编译不依赖这些排版工具。

Ubuntu/Debian可以使用：

```bash
sudo apt install pandoc texlive-xetex texlive-latex-extra fonts-noto-cjk
python3 -m pip install -r tools/requirements-pdf.txt
```

若系统不允许直接pip安装，先创建Python虚拟环境再安装。Windows可安装Pandoc、TeX Live与Noto Sans CJK字体，并保证pandoc和xelatex在PATH中。使用本仓库已生成的PDF不需要安装任何这些工具。

## 一键生成

在仓库根目录运行以下任意一条：

```bash
xmake pdf
# 或
make pdf
# 或
python3 tools/build_pdf.py
```

默认生成两份文件：

|文件|收录内容|适合用途|
|---|---|---|
|大一C语言全面指南_C99_CPP11_手机版.pdf|全部Markdown文档、45组C/C++完整源码、构建和辅助脚本|手机离线学习、看代码、做题复盘|
|大一C语言全面指南_C99_CPP11_含全部原始资料.pdf|手机版全部内容，再加raw里的6份原始PDF，共258页原件|查原题、对原答案、核对出处|

两个文件都在dist目录。`dist/pdf_manifest.json`列出每个收录文件及其SHA-256，方便检查有没有漏文档或代码。临时排版文件和日志位于`build/pdf/`。

手机版使用约108×192毫米的单栏窄页、12号正文字体，中文字体嵌入PDF。宽表改成逐条排列，代码长行自动折行，保留全部字符和注释。目录、PDF书签与文档内代码链接方便跳转。代码折行只是排版变化，仓库中的源文件没有因此改写。

附原件版直接追加原PDF页面，保留原卷版面。原PDF内容和页数不变，外部资料中的错误仍保留在原件中，修正说明在指南勘误章。

如果失败，先打开`build/pdf/pandoc.log`。缺字体就安装Noto CJK；缺命令就检查PATH。可先运行`python3 tools/build_pdf.py --smoke`只生成少量内容，验证排版环境。

## 更新资料后的顺序

```bash
xmake stats
xmake check
xmake pdf
python3 tools/check_pdf.py
```

修改已有文档或代码后，重新生成PDF即可。新增Markdown文档、C/C++源文件或工具脚本，会自动进入PDF收录清单。教学源码仍应保持编号成对，并更新data/examples.json，保证练习目录与测试完整。
