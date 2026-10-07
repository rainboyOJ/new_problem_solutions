/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 11:23
 * update_at: 2026-10-05 11:23
 */
#include <cstdio>
#include <vector>
#include <queue>
using namespace std;

typedef long long ll;

const int MAXN = 105; // 家族人数上限

int n;                // 家族人数
vector<int> g[MAXN];  // 邻接表，g[u] 存 u 的儿子
int in_deg[MAXN];     // 每个节点的入度
queue<int> q;         // Kahn 拓扑排序用的队列
int ans[MAXN];        // 拓扑序结果
int ans_len;          // 结果长度

// 读入第 u 个人的儿子列表，建边并统计入度
void read_input() {
    scanf("%d", &n);
    for (int u = 1; u <= n; u++) {
        int v;
        while (scanf("%d", &v) == 1 && v != 0) {
            g[u].push_back(v); // u 是 v 的父亲，建边 u -> v
            in_deg[v]++;       // v 的入度加 1
        }
    }
}

// Kahn 拓扑排序：每次输出入度为 0 的节点
void solve() {
    for (int u = 1; u <= n; u++) {
        if (in_deg[u] == 0) {
            q.push(u);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans[++ans_len] = u;

        // 把 u 的所有儿子 v 的入度减 1，入度变为 0 就入队
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            in_deg[v]--;
            if (in_deg[v] == 0) {
                q.push(v);
            }
        }
    }
}

int main() {
    read_input();
    solve();

    for (int i = 1; i <= ans_len; i++) {
        if (i > 1) printf(" ");
        printf("%d", ans[i]);
    }
    printf("\n");
    return 0;
}
