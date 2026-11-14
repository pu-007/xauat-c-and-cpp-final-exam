# 44_reservations 订餐信息管理：插入查询修改删除显示

层级：综合。来源：S6实验6 p47–51；链表C版与vector C++11版。

## 任务

菜单1 id name people HH:MM插入；2 id查询；3 id people HH:MM修改；4 id删除；5显示；6退出。编号正且唯一，姓名无空格<=31字节，人数1..1000

## 样例

输入（空白表示无输入）：

```text
5
1 7 Li 3 18:30
1 7 Wu 2 19:00
2 7
3 7 4 20:00
5
4 7
2 7
6
```

输出：

```text
EMPTY
OK
DUPLICATE
7 Li 3 18:30
OK
7 Li 4 20:00
OK
NOT_FOUND
```

## 实践步骤

1. 每行解析一条命令，检查参数个数、正编号、姓名字节数、人数和 00:00 至 23:59 的时间；多余参数或非法值输出 `INVALID`。
2. 插入前查重；查询和删除找不到输出 `NOT_FOUND`；插入、修改、删除成功输出 `OK`，重复编号输出 `DUPLICATE`。显示按插入顺序，空表输出 `EMPTY`；6 或输入结束退出。
3. 样例先显示空表，插入 7 后重复插入被拒绝；修改人数和时间后显示新记录，删除后查询不到。无效修改不能改变原记录。

每行最多 254 字节；该菜单和输出为资料项目的改编。单次操作 O(n)，存储 O(n)。C 链表使用二级指针连接或删除结点并释放内存；C++ `vector` 自动管理内存，插入或删除后迭代器可能失效。

完成后对照：[C99](../../src/44_reservations.c) / [C++11](../../src/44_reservations.cpp)。

```bash
./build/c/44_reservations < tests/cases/44_reservations.in
./build/cpp/44_reservations < tests/cases/44_reservations.in
```
