/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-12 23:00
 * update_at: 2026-08-12 23:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int MOD = 10007;

int n;
int w[MAXN];         // w[i] 表示点 i 的权值
vector<int> g[MAXN]; // 邻接表存树，仿照 rbook 模板 dfs-traversal 的建图方式

long long sum_total; // 所有有序点对联合权值之和，最后统一对 10007 取模
int max_value;       // 联合权值最大值

// 对中间点 u 的邻居做一次扫描：维护权值和、权值平方和、最大与次大权值。
void update_node(int u) {
    if ((int)g[u].size() < 2) return; // 少于两个邻居不会产生距离为 2 的点对

    long long sum = 0; // 邻居权值之和 S
    long long sq = 0;  // 邻居权值平方和 Q
    int max1 = 0;      // 邻居中最大权值
    int max2 = 0;      // 邻居中次大权值

    for (int i = 0; i < (int)g[u].size(); i++) {
        int value = w[g[u][i]];
        sum += value;
        sq += (long long)value * value;
        if (value > max1) {
            max2 = max1;
            max1 = value;
        } else if (value > max2) {
            max2 = value;
        }
    }

    // 经过 u 的有序点对总和 = S^2 - Q = 2 * sum_{a<b} w[a]*w[b]
    // 每个无序对的两个方向 (a,b)、(b,a) 都恰好被算一次。
    sum_total += sum * sum - sq;
    if (max1 * max2 > max_value) max_value = max1 * max2; // 有序对两个方向乘积相同
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) cin >> w[i];

    for (int u = 1; u <= n; u++) {
        update_node(u);
    }

    cout << max_value << ' ' << sum_total % MOD << '\n';
    return 0;
}
