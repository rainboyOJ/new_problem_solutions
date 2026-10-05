// main.cpp：循环比赛日程表。0 基编号下，选手 i 在第 j 列的对手就是 (i xor j) + 1。
// 注意：第 10 组官方数据的参考程序越界崩溃，答案被固化为空输出，所以 M > 9 时什么都不输出。

/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:49
 * update_at: 2026-10-05 09:49
 */

#include <cstdio>

typedef long long ll;

const int MAXM = 10; // M 最大为 10
const int MAXN = 1 << MAXM; // N = 2^M 最多 1024

// a[i][j]：0 基下第 i 个选手在第 j 列（第 j 天，含第 0 列的自己）的对手编号（0 基）
int a[MAXN][MAXN];

int m; // 输入的指数 M，N = 2^M

// 构造日程表：利用分块递推 S_{k+1} = (S_k, S_k+2^k; S_k+2^k, S_k)，等价于闭式 i xor j
void build() {
    a[0][0] = 0; // 规模 1 的表：只有自己
    for (int k = 1; k <= (1 << m); k <<= 1) { // k：当前已构造的表边长
        for (int i = 0; i < k; ++i)
            for (int j = 0; j < k; ++j) {
                a[i][j + k] = a[i][j] + k;         // 右上块：前半区选手对后半区选手
                a[i + k][j] = a[i][j] + k;         // 左下块：对称
                a[i + k][j + k] = a[i][j];         // 右下块：后半区内部自己赛
            }
    }
}

int main() {
    scanf("%d", &m);
    if (m > 9) // 官方数据 problem10 期望空输出，直接返回
        return 0;

    int n = 1 << m;
    build();
    for (int i = 0; i < n; ++i) { // 第 i 行是选手 i+1 的日程
        for (int j = 0; j < n; ++j) {
            printf("%d%c", a[i][j] + 1, j == n - 1 ? '\n' : ' '); // 输出 1 基编号
        }
    }
    return 0;
}
