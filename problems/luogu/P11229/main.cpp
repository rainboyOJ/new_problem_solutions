/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 17:33
 * update_at: 2026-10-02 21:58
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// main.cpp：n <= 50 直接查打表数组 tables[]，n > 50 按 n = 7k + r 的规律输出。
// tables[] 由 brute-dfs-clip.cpp（DFS 暴力打表）生成。

// tables[i]：恰好用 i 根木棍拼出的最小正整数（下标 0 不用，n = 1 无解记为 -1）
// 由 brute-dfs-clip.cpp 的 DFS 暴力打表得到，范围 n = 1..50
ll tables[] = {
    -1,      // n = 0（不用）
    -1,      // n = 1：无解
    1, 7, 4, 2, 6, 8, 10, 18, 22, 20,
    28, 68, 88, 108, 188, 200, 208, 288, 688, 888,
    1088, 1888, 2008, 2088, 2888, 6888, 8888, 10888, 18888, 20088,
    20888, 28888, 68888, 88888, 108888, 188888, 200888, 208888, 288888, 688888,
    888888, 1088888, 1888888, 2008888, 2088888, 2888888, 6888888, 8888888, 10888888,
}; // tables[50] = 10888888

// 规律：n > 50 时答案位数 len = ceil(n/7)，高位放一个固定前缀，其余位全是 8。
// 前缀由 r = n % 7 决定（对应题解的规律表），用字符串直接列出：
//   r = 0 -> ""（全 8），r = 1 -> "10"，r = 2 -> "1"，r = 3 -> "200"，
//   r = 4 -> "20"，r = 5 -> "2"，r = 6 -> "6"。
// n > 50 时 k >= 7，像 r = 3 的 "22"（k = 1）、r = 4 的 "4"（k = 0）这类短前缀
// 都已经写在 tables[] 里，走不到这里。
const char* prefix[7] = {"", "10", "1", "200", "20", "2", "6"};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T;
    cin >> T;
    while (T--) {
        ll n;
        cin >> n;

        if (n <= 50) { // 小数据：直接查打表数组
            cout << tables[n] << '\n';
            continue;
        }

        // 大数据：固定前缀 + 若干 8，补满 len 位
        ll len = (n + 6) / 7; // 答案位数 = ceil(n/7)
        ll r = n % 7;
        ll done = strlen(prefix[r]); // 前缀已经占用的位数
        cout << prefix[r];
        for (ll i = done; i < len; i++)
            cout << '8';
        cout << '\n';
    }

    return 0;
}
