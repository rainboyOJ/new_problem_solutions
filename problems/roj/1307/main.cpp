/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 08:49
 * update_at: 2026-10-05 08:49
 */
// main.cpp：高精度乘法。两个不超过 100 位的十进制正整数 M、N，求 M*N。

#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

const int MAXN = 205; // 两个 100 位数相乘，结果最多 200 位

// 全局位数组：a[1..la] 存 M 的逆序低位在前数字，b[1..lb] 存 N 的逆序低位在前数字，c[1..lc] 存积的逆序低位在前数字
int a[MAXN];
int b[MAXN];
int c[MAXN];

int la, lb, lc; // M、N、积的位数

void mul() {
    // 双重循环：第 i 位 × 第 j 位累加到第 i+j-1 位
    for (int i = 1; i <= la; ++i) {
        for (int j = 1; j <= lb; ++j) {
            c[i + j - 1] += a[i] * b[j];
        }
    }

    // 从低位到高位统一进位
    lc = la + lb;
    for (int i = 1; i <= lc; ++i) {
        if (c[i] >= 10) {
            c[i + 1] += c[i] / 10;
            c[i] %= 10;
        }
    }

    // 去掉前导零：lc 可能比真实位数多 1（最高位刚好为 0 的情况）
    while (lc > 1 && c[lc] == 0) {
        --lc;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string M, N;
    cin >> M >> N;

    la = (int)M.size();
    lb = (int)N.size();

    // 逆序写入：a[1] = M 的最低位
    for (int i = 0; i < la; ++i) {
        a[i + 1] = M[la - 1 - i] - '0';
    }
    for (int i = 0; i < lb; ++i) {
        b[i + 1] = N[lb - 1 - i] - '0';
    }

    mul();

    // 倒序输出
    for (int i = lc; i >= 1; --i) {
        cout << c[i];
    }
    cout << '\n';

    return 0;
}
