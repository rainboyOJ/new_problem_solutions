/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:04
 * update_at: 2026-10-13 16:35
 */
#include <cstdio>
#include <algorithm>
#include <vector>
using namespace std;

typedef long long ll;

// 骑马修栅栏：每条栅栏恰好走一次 = 无向图欧拉路
// 精简版迭代 Hierholzer（不用 struct 图、不用递归）：
// 口诀「走不动了再记点，记完 reverse」
// 字典序最小：邻接表按另一端点升序，每步贪心走当前最小的可用邻点

const int MAXV = 500;  // 顶点编号 1~500
const int MAXF = 1024; // 栅栏数 F <= 1024，路径长度为 F+1

struct Edge {
    int to; // 这条栅栏的另一个端点
    int id; // 栅栏编号，用来标记这条边走过没有
};

vector<Edge> g[MAXV + 5]; // g[v]：v 连出的所有栅栏，按 to 升序
int deg[MAXV + 5];        // deg[v]：v 的度数，自环一条边要 +2
int used[MAXF + 5];       // used[id]：第 id 条栅栏是否已经走过
int cur[MAXV + 5];        // cur[v]：当前弧，v 的边从这里继续找，每条边只被扫过常数次
int path[MAXF + 5];       // path[]：走不动时记下的顶点，反转后才是答案
int path_len;             // path_len：路径上的顶点个数

// 邻接表排序用：按另一端点编号升序，保证每步都能贪心取最小邻点
bool cmp_edge(const Edge &a, const Edge &b) {
    return a.to < b.to;
}

// 从起点 s 出发走欧拉路：显式栈模拟递归，避免 F 条边递归爆栈
void hierholzer(int s) {
    int stack_vertex[MAXF + 5]; // 当前还没走完的顶点栈
    int top = 0;
    stack_vertex[++top] = s;
    while (top > 0) {
        int u = stack_vertex[top];
        ll sz = g[u].size(); // 当前点还没走的边数上界
        // 跳过已经走过的边；cur 保证总复杂度 O(F)
        while (cur[u] < sz && used[g[u][cur[u]].id] == 1) cur[u]++;
        if (cur[u] == sz) {
            path[++path_len] = u; // 走不动才记点（后序），最后要 reverse
            top--;
        } else {
            Edge e = g[u][cur[u]]; // 用掉这条边，走向另一端点
            cur[u]++;
            used[e.id] = 1;
            stack_vertex[++top] = e.to;
        }
    }
}

int main() {
    int fences;
    scanf("%d", &fences);

    for (int id = 1; id <= fences; id++) {
        int u, v;
        scanf("%d %d", &u, &v);
        g[u].push_back(Edge{v, id});
        g[v].push_back(Edge{u, id}); // 无向边两个方向共用编号，不会来回走同一条
        deg[u] += (u == v ? 2 : 1);  // 易错点：自环让度数 +2
        if (u != v) deg[v]++;
    }

    // 每个点的邻接表升序排序：每步贪心走最小邻点，答案才是字典序最小
    for (int v = 1; v <= MAXV; v++) sort(g[v].begin(), g[v].end(), cmp_edge);

    // 奇度点只能是欧拉路的两端，起点取较小的那个；
    // 全偶度时是欧拉回路，任取编号最小的有边点（题目保证有解，F >= 1 一定找得到）
    int start = -1;
    for (int v = 1; v <= MAXV; v++) {
        if (deg[v] % 2 == 1) {
            start = v;
            break;
        }
    }
    if (start == -1) {
        for (int v = 1; v <= MAXV; v++) {
            if (deg[v] > 0) {
                start = v;
                break;
            }
        }
    }

    hierholzer(start);

    // path 是后序记录，倒着输出就是从起点到终点的顺序，每行一个顶点
    for (int i = path_len; i >= 1; i--) printf("%d\n", path[i]);
    return 0;
}
