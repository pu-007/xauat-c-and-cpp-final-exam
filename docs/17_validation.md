# 验证记录与可复现命令

验证环境：Linux，GCC/G++ 14.2.0，Python 3.12.14。标准固定为 **C99 / C++11**。

## 已完成

|检查|结果|
|---|---|
|45个C程序|`gcc -std=c99 -O2 -Wall -Wextra -Wpedantic -Werror`全部通过|
|xmake构建与check|xmake 3.1.2已构建90个目标，并通过相同功能测试与仓库检查|
|45个C++程序|`g++ -std=c++11 -O2 -Wall -Wextra -Wpedantic -Werror`全部通过|
|基础/算法回归|1264次进程断言通过；另10组魔方阵性质检查通过|
|实验回归|108次进程断言通过；另2组持久文件流水线逐字节验证通过|
|ASan/UBSan|重新构建90个程序，复用全部上述测试，通过|
|LeakSanitizer|在不受ptrace限制的本地执行环境，启用detect_leaks=1后全部上述测试通过|
|统计与资料|6个原PDF的SHA-256校验、258页文本、695次题号出现核对|
|仓库完整性|C/C++成对、样例文件与元数据一致、任务卡完整、本地Markdown链接检查|

```text
PASS: 1264 process assertions + 10 magic-square property checks; C99/C++11; seed=20261103
PASS labs: 108 process assertions + 2 persistent-file pipelines with byte-level validation; seed=20261104
```

`tests/run.py`用Python排序、gcd/lcm、pow、factorial、find、背包子集枚举等独立参考核对算法；不是仅比较C/C++是否一致。`tests/labs.py`以有序字典模拟220条订餐操作，检查错误输入不修改旧记录，并读二进制文件验证姓名与每科分数。

## 重现

```bash
make clean
make -j4
make test
make sanitize
make stats
python3 tools/check_repo.py
xmake check
xmake pdf
python3 tools/check_pdf.py
```

make sanitize在Linux/GCC上使用地址与未定义行为检测、保留帧指针及禁用PIE以减少受限环境中的地址映射干扰。最初在被ptrace跟踪的沙箱中LeakSanitizer报告环境致命错误；随后以相同已构建检测程序在允许正常运行的本地环境通过，没有关闭泄漏检测来宣称成功。

如果你的容器也限制ptrace相关能力，泄漏检测可能无法启动；按自己的环境配置运行，不能把启动失败当代码错误或测试通过。

## 验证边界

- 每个程序有写明的输入范围，不承诺解析任意超长/超范围恶意数值。直接scanf读取整数的程序假设该记号可由目标整数类型表示。
- 测试覆盖正常、空/单元素、重复、全负、越界范围、无解、部分错误输入，以及选定随机数据；不是形式化证明。
- 37二次方程使用教材直接公式，极端尺度可能相消或溢出；主要验证常见教学系数。32/38展示数值迭代而非工业数值库。
- 二进制文件使用本机int表示，只验证相同实现的C/C++往返；UTF-8名字按字节限制。
- 原PDF含未定义行为/旧标准/排版问题；这些片段不直接加入“必须编译通过”的教学源代码目录。


## PDF资料包的检查

`tools/check_pdf.py`按实际文件清单逐个核对，避免只检查“PDF能打开”。检查内容包括：

- 全部Markdown、90份教学源码、工具及配置源码都在收录清单中，哈希与当前文件一致。
- 所有教学源码和工具源码的文件名可在PDF中检索到。
- 目录和内部链接能跳到有效页面，字体已嵌入，文本不超出页面边界。
- 附原件版比手机版正好多258页；每一页的文本和页面尺寸与raw原件相同。
- 人工查看了封面、知识卡片、考题依据与长代码页面，确认中文显示及自动折行正常。

PDF页数随文档更新而变化，以dist/pdf_manifest.json为准。原始资料始终为6份、258页。
