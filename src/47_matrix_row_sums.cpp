/* S1 PDF 第109页模拟一编程2：输出5行6列矩阵及各行和。
 * 算法：读取并保存矩阵，累加到一维行和数组，再逐行输出矩阵及行和。
 * 时间复杂度 O(5*6)，空间复杂度 O(5*6)；对应 C99：47_matrix_row_sums.c。
 * 输入：5行各6个整数，每个在-10000至10000；读取失败或越界返回1。
 * 输出：5行，每行6个原数以单空格分隔，后接“ | ”和行和，再换行。
 * C99 对照使用 scanf/printf、同样的数组和 (int) 强制转换；本版使用输入输出流。
 */
#include <iostream> // 提供标准输入输出流。

int main() { // 程序入口，不接收参数。
    int matrix[5][6]; // 保存输入矩阵，供之后回显。
    int sums[5] = {}; // 一维数组的五个行和均初始化为零。
    for (int row = 0; row < 5; ++row) { // 行下标从0递增到4。
        for (int col = 0; col < 6; ++col) { // 列下标从0递增到5。
            long long value; // 用较宽类型读取并检查范围。
            if (!(std::cin >> value) || value < -10000 || value > 10000) { // 输入流读取失败或数值越界时拒绝。
                return 1; // 输入无效时结束。
            }
            matrix[row][col] = static_cast<int>(value); // 范围检查后保存元素。
            sums[row] += matrix[row][col]; // 累加当前行的和。
        }
    }
    for (int row = 0; row < 5; ++row) { // 按原顺序输出各行。
        for (int col = 0; col < 6; ++col) { // 输出当前行的六个元素。
            if (col != 0) { // 元素之间用一个空格分隔。
                std::cout << ' '; // 输出分隔符。
            }
            std::cout << matrix[row][col]; // 回显当前元素。
        }
        std::cout << " | " << sums[row] << '\n'; // 输出分隔符、行和和换行。
    }
    return 0; // 表示正常结束。
}
