/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-17 01:40
 * update_at: 2026-10-20 14:55
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：枚举每一对端点，真的加一条 0 权边，然后重新跑完整的 Floyd，再求和。
// 与 main.cpp 的差别只有一点——它老老实实重跑了 Floyd，不依赖"至多用一次"的化简。
// 复杂度 O(n^5)，只适合 n 很小的情况。
#include <bits/stdc++.h>
using namespace std;

const int maxn = 25;
const long long INF = (1LL << 60);

int n, m;
long long original[maxn][maxn];  // 原图距离矩阵
long long work[maxn][maxn];      // 每次尝试时的临时矩阵

void floyd(long long d[maxn][maxn], int cnt) {
    for (int k = 1; k <= cnt; k++) {
        for (int i = 1; i <= cnt; i++) {
            if (d[i][k] == INF) continue;
            for (int j = 1; j <= cnt; j++) {
                if (d[k][j] == INF) continue;
                if (d[i][k] + d[k][j] < d[i][j]) {
                    d[i][j] = d[i][k] + d[k][j];
                }
            }
        }
    }
}

// 计算所有无序点对距离之和
long long total_of(long long d[maxn][maxn], int cnt) {
    long long sum = 0;
    for (int i = 1; i <= cnt; i++) {
        for (int j = i + 1; j <= cnt; j++) sum += d[i][j];
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            original[i][j] = (i == j) ? 0 : INF;
        }
    }
    for (int i = 1; i <= m; i++) {
        int u, v;
        long long w;
        cin >> u >> v >> w;
        original[u][v] = w;
        original[v][u] = w;
    }

    long long answer = INF;
    for (int a = 1; a <= n; a++) {
        for (int b = a + 1; b <= n; b++) {
            // 真的加一条 0 权边，然后重新跑一遍 Floyd
            for (int i = 1; i <= n; i++) {
                for (int j = 1; j <= n; j++) work[i][j] = original[i][j];
            }
            work[a][b] = 0;
            work[b][a] = 0;
            floyd(work, n);

            long long sum = total_of(work, n);
            if (sum < answer) answer = sum;
        }
    }

    cout << answer << '\n';
    return 0;
}
