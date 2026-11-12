/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-12 15:18
 * update_at: 2026-11-12 15:18
 */
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const int maxn = 300000 + 50;

vector<int> g[maxn];   // 全局邻接表
int in_deg[maxn];       // 每个节点的入度
int q[maxn];           // 数组模拟拓扑排序队列
string s;              // 节点对应的字符

// dp[u][c] 表示以节点 u 结尾的所有路径中，字符 c（'a' + c）出现的最大次数
int dp[maxn][26];

int main() {
    // 提升标准流输入输出性能
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;
    cin >> s;

    for (int i = 0; i < m; ++i) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        in_deg[v]++;
    }

    // 1. 初始化队列：将所有入度为 0 的节点加入队列
    int head = 0, tail = 0;
    for (int i = 1; i <= n; ++i) {
        if (in_deg[i] == 0) {
            q[tail++] = i;
        }
        // 初始化：每个节点作为路径起点时，自身字母出现 1 次
        dp[i][s[i - 1] - 'a'] = 1;
    }

    // 2. 拓扑排序与顺推 DP 状态转移
    int visited_cnt = 0;
    while (head < tail) {
        int u = q[head++];
        visited_cnt++;

        int u_char = s[u - 1] - 'a';

        for (int v : g[u]) {
            int v_char = s[v - 1] - 'a';

            // 沿着有向边 u -> v 推进 26 种字符的最优值
            for (int c = 0; c < 26; ++c) {
                int add = (c == v_char ? 1 : 0);
                if (dp[u][c] + add > dp[v][c]) {
                    dp[v][c] = dp[u][c] + add;
                }
            }

            // 拓扑排序入度更新
            if (--in_deg[v] == 0) {
                q[tail++] = v;
            }
        }
    }

    // 3. 判环：如果出队节点数小于 n，说明图中存在至少一个有向环
    if (visited_cnt < n) {
        cout << -1 << "\n";
        return 0;
    }

    // 4. 统计全局最大路径价值
    int ans = 0;
    for (int i = 1; i <= n; ++i) {
        for (int c = 0; c < 26; ++c) {
            if (dp[i][c] > ans) {
                ans = dp[i][c];
            }
        }
    }

    cout << ans << "\n";
    return 0;
}
