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

1. 画出关键变量/数组状态，手算样例。
2. 从空文件独立实现C99版本。
3. 至少增加三个边界测试，并写出预期结果。
4. 解释时间/空间复杂度，再改写C++11版本。

提示：分离查找、验证、修改和释放；修改失败不破坏已有记录；维护唯一编号。

复杂度参考：每条增删查改O(n)，空间O(n)。

挑战：增设姓名修改、按时间排序、文件保存；先写数据格式再扩展菜单。

完成后对照：[C99](../../src/c/44_reservations.c) / [C++11](../../src/cpp/44_reservations.cpp)。

```bash
./build/c/44_reservations < tests/cases/44_reservations.in
./build/cpp/44_reservations < tests/cases/44_reservations.in
```
