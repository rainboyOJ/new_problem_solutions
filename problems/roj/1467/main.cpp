/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:53
 * update_at: 2026-10-05 02:53
 */
// 求最短生成元长度：w 是某周期串的子串，等价于求 w 的最小周期。
// 由「周期–border 对偶」，最小周期 = L − 最长 border，KMP 失配函数一次线性扫描即可。
#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

const int MAXN = 1000005;

ll L;      // 题面给出的字符串长度
string w;  // 待求最小周期的字符串，下标从 0 开始

int fail[MAXN]; // fail[i]：w 的长度 i 前缀的最长 border 长度；值不超过 10^6，用 int 控制内存

// KMP 失配函数：求出每个前缀的最长 border。
void build_fail() {
    fail[0] = 0;
    int k = 0; // 扫描到 i 时，k 恰好等于 fail[i]
    for (int i = 1; i < L; i++) {
        while (k > 0 && w[i] != w[k]) {
            k = fail[k]; // 沿 border 链回退：次长 border 仍是 border
        }
        if (w[i] == w[k]) {
            k++;
        }
        fail[i + 1] = k;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> L >> w;

    build_fail();

    // 答案就是 w 的最小周期，也就是能自我连接生成 w 的最短元串长度
    cout << L - fail[L] << "\n";

    return 0;
}
