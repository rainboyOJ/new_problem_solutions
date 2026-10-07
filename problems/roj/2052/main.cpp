/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 09:51
 * update_at: 2026-10-06 09:51
 */
#include <cstdio>

typedef long long ll;

const int MAXV = 501;
const int MAXE = 1025;

// 邻接表：adj[v] 存与 v 相连的 (邻居, 边号)，按邻居升序排好
int adj_v[MAXV][MAXV]; // adj_v[v][k] = v 的第 k 条邻边的另一端
int adj_e[MAXV][MAXV]; // adj_e[v][k] = v 的第 k 条邻边的边编号（区分重边）
int deg[MAXV];         // deg[v] = v 的度数
int scan_p[MAXV];      // scan_p[v] = v 在邻接表上的扫描位置，只前进不后退
bool used[MAXE];       // used[eid] = 该栅栏是否已走过
int stk[MAXV * 2];     // 模拟 DFS 的栈，栈中顶点数最多 F+1
int path[MAXV * 2];    // 逆后序答案，最后倒转输出

int main() {
    int F;
    scanf("%d", &F);
    for (int eid = 0; eid < F; ++eid) {
        int a, b;
        scanf("%d %d", &a, &b);
        adj_v[a][deg[a]] = b; adj_e[a][deg[a]] = eid; ++deg[a];
        adj_v[b][deg[b]] = a; adj_e[b][deg[b]] = eid; ++deg[b];
    }

    // 邻接表本身按读入的邻居升序排：每个点的邻边按邻居编号排序，贪心走最小邻居
    for (int v = 1; v <= MAXV - 1; ++v) {
        for (int i = 0; i < deg[v]; ++i) {
            for (int j = i + 1; j < deg[v]; ++j) {
                if (adj_v[v][j] < adj_v[v][i]) {
                    int tv = adj_v[v][i], te = adj_e[v][i];
                    adj_v[v][i] = adj_v[v][j]; adj_e[v][i] = adj_e[v][j];
                    adj_v[v][j] = tv;          adj_e[v][j] = te;
                }
            }
        }
    }

    // 有奇点必须从奇点出发；取最小奇点保证路径第一位最小
    // 全偶时是欧拉回路，取最小顶点
    int start = 0;
    for (int v = 1; v <= MAXV - 1; ++v) {
        if (deg[v] % 2 == 1) { start = v; break; }
    }
    if (start == 0) {
        for (int v = 1; v <= MAXV - 1; ++v) {
            if (deg[v] > 0) { start = v; break; }
        }
    }

    // Hierholzer：顶点所有关联边用完后才出栈记入 path（逆后序）
    int top = 0, cnt = 0;
    stk[top++] = start;
    while (top > 0) {
        int v = stk[top - 1];
        // 跳过已走过的边，每个位置最多被扫一次，主循环总计 O(F)
        while (scan_p[v] < deg[v] && used[adj_e[v][scan_p[v]]]) ++scan_p[v];
        if (scan_p[v] == deg[v]) {      // 没有剩余边，该顶点走完
            --top;
            path[cnt++] = v;
        } else {                        // 贪心走最小未用邻居
            int k = scan_p[v];
            used[adj_e[v][k]] = true;
            stk[top++] = adj_v[v][k];
        }
    }

    // 逆后序倒转即为从 start 出发的欧拉路径
    for (int i = cnt - 1; i >= 0; --i) printf("%d\n", path[i]);
    return 0;
}
