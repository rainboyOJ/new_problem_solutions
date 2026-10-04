/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:11
 * update_at: 2026-10-05 04:11
 */
// main.cpp：计算 2^N 的精确值。N ≤ 100，2^N 最多 31 位十进制数字，
// 超出 64 位整数范围，必须用十进制位数组手动维护高精度。

#include <iostream>

typedef long long ll;

const int MAXD = 50;    // 答案最多 31 位，开到 50 留点余量

int digit[MAXD];        // digit[0] 是低位、digit[len-1] 是高位；每轮做完乘 2 + 进位
int n;                  // 输入的指数 N
int len;                // 当前答案在 digit[] 里实际占用的位数

int main() {
    // 关同步：单次输入输出不必，本题数据小，但保持 OI 习惯写法。
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin >> n;

    // 初始：2^0 = 1，用最低位 digit[0] = 1 表示。
    digit[0] = 1;
    len = 1;

    // 外层跑 N 轮，每轮把整组十进制位乘 2，再统一处理进位。
    for (int round = 1; round <= n; round++) {
        int carry = 0; // 本轮累加出来的进位
        for (int i = 0; i < len; i++) {
            int cur = digit[i] * 2 + carry; // 当前位乘 2 并加上上一位的进位
            digit[i] = cur % 10;            // 当前位只留个位
            carry = cur / 10;                // 多出来的部分作为进位传给更高位
        }
        // 最高位可能还会再产生新的进位，循环写到 carry 为 0 为止。
        while (carry > 0) {
            digit[len] = carry % 10;
            carry = carry / 10;
            len++;
        }
    }

    // 倒序输出：从最高位到最低位拼接成十进制串。
    for (int i = len - 1; i >= 0; i--) {
        std::cout << digit[i];
    }
    std::cout << "\n";

    return 0;
}
