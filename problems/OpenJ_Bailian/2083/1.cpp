#include <iostream>
#include <vector>
#include <cmath>
#include <cstring>

using namespace std;

// 全局字符数组，最大边长为 3^6 = 729
char canvas[731][731];

// 预计算 3 的幂次方，提高效率
int pow3[8];

/**
 * 递归绘制盒分形
 * @param n 当前分形的度数
 * @param r 起始行坐标
 * @param c 起始列坐标
 */
void draw(int n, int r, int c) {
    if (n == 1) {
        canvas[r][c] = 'X';
        return;
    }

    // 计算子分形（n-1度）的边长
    int subSize = pow3[n - 2];

    // 递归填充五个位置
    draw(n - 1, r, c);                         // 左上
    draw(n - 1, r, c + 2 * subSize);           // 右上
    draw(n - 1, r + subSize, c + subSize);     // 中间
    draw(n - 1, r + 2 * subSize, c);           // 左下
    draw(n - 1, r + 2 * subSize, c + 2 * subSize); // 右下
}

int main() {
    // 预处理 3 的幂
    pow3[0] = 1;
    for (int i = 1; i <= 7; ++i) pow3[i] = pow3[i - 1] * 3;

    int n;
    while (cin >> n && n != -1) {
        int size = pow3[n - 1];

        // 初始化画布为空格
        for (int i = 0; i < size; ++i) {
            for (int j = 0; j < size; ++j) {
                canvas[i][j] = ' ';
            }
            canvas[i][size] = '\0'; // 方便按行打印
        }

        // 开始递归绘制
        draw(n, 0, 0);

        // 输出结果
        for (int i = 0; i < size; ++i) {
            // 题目要求：去掉行末多余空格可能会导致不通过，
            // 建议直接输出整行。
            // 此时由于末尾有 \0，可以直接按字符串输出或遍历
            for (int j = 0; j < size; ++j) {
                cout << canvas[i][j];
            }
            cout << endl;
        }
        cout << "-" << endl;
    }
    return 0;
}
