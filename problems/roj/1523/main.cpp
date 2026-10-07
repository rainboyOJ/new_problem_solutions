/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:37
 * update_at: 2026-10-06 00:37
 */
// main.cpp：嗅探器——找编号最小的 a-b 必经点（删点 + DFS 连通性判定）。
#include <iostream>

typedef long long ll;

int n;                   // 服务器数目
bool conn[105][105];     // conn[i][j] 表示 i、j 之间有双向连接（n<=100 用邻接矩阵）
bool vis[105];           // DFS 的已访问标记

// 从 cur 出发找 dst，跳过点 ban（预置为"已删"），能到返回 true
bool dfs(int cur, int dst, int ban) {
    if (cur == dst) return true;
    vis[cur] = true;
    for (int i = 1; i <= n; i++)
        if (conn[cur][i] && i != ban && !vis[i] && dfs(i, dst, ban)) return true;
    return false;
}

int main() {
    std::cin >> n;
    int i, j;
    while (std::cin >> i >> j) {
        if (i == 0 && j == 0) break; // 0 0 标志拓扑描述结束
        conn[i][j] = conn[j][i] = true;
    }
    int a, b; // 两个信息中心
    std::cin >> a >> b;

    // v 是必经点 <=> 删掉 v 后 a 到不了 b；排除 a、b 自身（它们不是"中间"服务器）
    for (int v = 1; v <= n; v++) {
        if (v == a || v == b) continue;
        for (int k = 1; k <= n; k++) vis[k] = false;
        if (!dfs(a, b, v)) {
            std::cout << v << std::endl;
            return 0;
        }
    }
    std::cout << "No solution" << std::endl;
    return 0;
}
