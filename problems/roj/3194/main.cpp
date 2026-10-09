/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 21:30
 * update_at: 2026-10-09 23:08
 */
// ROJ 3194《Intervals 区间》：区间选点，差分约束 + SPFA 最长路。
//
// 设 S_x = 集合 Z 中 <= x 的整数个数（前缀和），区间约束 [a,b] >= c 变成
//     S_b - S_{a-1} >= c   =>   S_b >= S_{a-1} + c
// 再加上前缀和自身的两条限制：
//     S_x - S_{x-1} <= 1   =>   S_{x-1} >= S_x - 1
//     S_x - S_{x-1} >= 0   =>   S_x >= S_{x-1} + 0
// 全部化成 v >= u + w 的形式后连有向边 u->v 权 w，跑最长路，答案 = dist[终点]。
//
// 坐标偏移：a_i 可为 0，a_i-1 会到 -1，所以整体 +1，令 u=a_i、v=b_i+1（原坐标）。
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

typedef long long ll;

const int MAXV = 50005;    // 坐标节点上限（原坐标 0..50000 各占一个节点）
const int MAXT = 200005;   // 输入 token 上限：2 + 3*50000
const int NEG = -1000000000;

struct Edge {
    int v;
    int w;
};

vector<Edge> adj[MAXV];    // adj[u] = 从 u 出发的长路边
int token[MAXT];           // 全部输入 token（用于自动识别首行格式）
int dist_val[MAXV];        // 最长路距离
bool in_queue[MAXV];       // SPFA 入队标记

void solve() {
    int cnt = 0;
    while (cnt < MAXT && (cin >> token[cnt])) cnt++;
    if (cnt == 0) return;

    // 首行格式有两种：题面写的是「第一行 n」（1 个 token），
    // 官方数据实测首行是「上界 n」（2 个 token）。用 token 总数 3 同余自动判定：
    // 1 + 3n ≡ 1，2 + 3n ≡ 2 (mod 3)，两者绝不相混。
    int n;
    int head;
    if ((cnt - 1) % 3 == 0) { n = token[0]; head = 1; }
    else { n = token[1]; head = 2; }

    int min_val = MAXV;
    int max_val = 0;

    for (int i = 0; i < n; i++) {
        int a = token[head + 3 * i] + 1;          // 坐标右移 1，等价于用 a_i-1 建点
        int b = token[head + 3 * i + 1] + 1;
        int c = token[head + 3 * i + 2];
        adj[a - 1].push_back({b, c});   // S_{b} >= S_{a-1} + c
        if (a - 1 < min_val) min_val = a - 1;
        if (b > max_val) max_val = b;
    }

    // 前缀和的相邻两条限制：S_{x} >= S_{x-1} + 0 与 S_{x-1} >= S_{x} - 1
    for (int i = min_val; i < max_val; i++) {
        adj[i].push_back({i + 1, 0});
        adj[i + 1].push_back({i, -1});
    }

    for (int i = 0; i <= max_val + 1; i++) {
        dist_val[i] = NEG;
        in_queue[i] = false;
    }

    // 起点是 min_val：它下面没有任何约束，取 dist = 0 即 S_{min_val} = 0
    queue<int> q;
    dist_val[min_val] = 0;
    q.push(min_val);
    in_queue[min_val] = true;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        in_queue[u] = false;

        for (int k = 0; k < (int)adj[u].size(); k++) {
            int v = adj[u][k].v;
            int w = adj[u][k].w;
            if (dist_val[u] + w > dist_val[v]) {
                dist_val[v] = dist_val[u] + w;
                if (!in_queue[v]) {
                    q.push(v);
                    in_queue[v] = true;
                }
            }
        }
    }

    cout << dist_val[max_val] << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
