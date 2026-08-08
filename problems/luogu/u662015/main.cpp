/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-08 23:13
 * update_at: 2026-08-08 23:59
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 105;
int n, V;
int v[MAXN], w[MAXN];
int f[MAXN][MAXN]; // f[i][c] 表示考虑物品 i..N，容量为 c 时的最大价值

int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);

    cin >> n >> V;
    for (int i = 1; i <= n; ++i) cin >> v[i] >> w[i];

    // 从后向前 DP：f[i][c] = 使用物品 i..N 的最优值
    for (int i = n; i >= 1; --i) {
        for (int c = 0; c <= V; ++c) {
            f[i][c] = f[i + 1][c];
            if (c >= v[i]) f[i][c] = max(f[i][c], f[i + 1][c - v[i]] + w[i]);
        }
    }

    // 从 1 向 N 回溯，优先选取编号小的物品，得到字典序最小的方案
    vector<int> ans;
    int cur = V;
    for (int i = 1; i <= n; ++i) {
        if (cur >= v[i] && f[i][cur] == f[i + 1][cur - v[i]] + w[i]) {
            ans.push_back(i);
            cur -= v[i];
        }
    }

    for (size_t i = 0; i < ans.size(); ++i) {
        if (i > 0) cout << ' ';
        cout << ans[i];
    }
    cout << '\n';
    return 0;
}
