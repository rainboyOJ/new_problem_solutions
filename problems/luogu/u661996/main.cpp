#include <bits/stdc++.h>
using namespace std;

const int maxn = 105;
int N, V;
int v[maxn], w[maxn];          // 每个节点的体积和价值
vector<int> children[maxn];    // 树形依赖关系
// dp[u][j] 表示以 u 为根的子树，占用容量 j 时的最大价值。
int dp[maxn][maxn];

void dfs(int u) {
    // 先把节点 u 本身的价值放入（必须选 u 才能选其子节点）。
    for (int j = v[u]; j <= V; j++)
        dp[u][j] = w[u];
    for (int c : children[u]) {
        dfs(c);
        // 给子节点分配容量，类似分组背包：子节点只能选一个「分配量」。
        for (int j = V; j >= v[u]; j--)
            for (int k = 0; k <= j - v[u]; k++)
                dp[u][j] = max(dp[u][j], dp[u][j - k] + dp[c][k]);
    }
}

int main() {
    ios::sync_with_stdio(false); cin.tie(0);
    cin >> N >> V;
    for (int i = 1; i <= N; i++) {
        int p;
        cin >> v[i] >> w[i] >> p;
        if (p == -1) {                   // 根节点挂在虚拟根 0 下
            children[0].push_back(i);
        } else {
            children[p].push_back(i);
        }
    }
    dfs(0);
    cout << dp[0][V] << '\n';
    return 0;
}
