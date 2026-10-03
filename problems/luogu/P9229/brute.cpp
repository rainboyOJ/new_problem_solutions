/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-02 15:07
 */
// brute.cpp：小数据暴力解，直接按定义建图跑 BFS，用来对拍验证正解。
//
// 状态 t 用 n+1 位二进制表示（第 i 位表示第 i+1 个环，0 下标）。
// 第 i 个环（1..m）可以翻转，当且仅当 t_1..t_{i-1} 恰好等于 s 的长度 i-1 的后缀。
// 从全 0 状态 BFS 到全 1 状态，最短路长度就是答案。
#include <iostream>
#include <queue>
using namespace std;
const int maxn = 1 << 16;   // 支持 n+1 <= 16，即 n <= 15

int n, m;
char str[64];
int req[64];      // req[i]：第 i 个环可翻转时，低位 i-1 位应该是什么
int dist[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (!(cin >> n)) return 0;
    cin >> (str + 1);
    m = n + 1;

    // 预处理每个环的“前置条件”：t_1..t_{i-1} == s 的长度 i-1 的后缀
    req[1] = 0;
    for (int i = 2; i <= m; i++) {
        int k = i - 1;          // k <= n
        int val = 0;
        for (int j = 1; j <= k; j++) {
            // t_j 对应 s 的第 n-k+j 个字符
            if (str[n - k + j] == '1') val |= 1 << (j - 1);
        }
        req[i] = val;
    }

    int total = 1 << m;
    for (int i = 0; i < total; i++) dist[i] = -1;
    queue<int> q;
    dist[0] = 0;
    q.push(0);
    while (!q.empty()) {
        int st = q.front(); q.pop();
        for (int i = 1; i <= m; i++) {
            int k = i - 1;
            int low = st & ((1 << k) - 1);
            if (low != req[i]) continue;
            int ns = st ^ (1 << (i - 1));
            if (dist[ns] == -1) {
                dist[ns] = dist[st] + 1;
                q.push(ns);
            }
        }
    }

    cout << dist[total - 1] << "\n";
    return 0;
}
