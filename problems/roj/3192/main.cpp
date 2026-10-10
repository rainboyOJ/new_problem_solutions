/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:30
 * update_at: 2026-10-10 13:30
 */

// Freda 的传呼机：仙人掌最短路 —— 建圆方树（每个环缩成挂在环顶下的方点），
// 环上非顶点的父边权取「环顶沿环内最短路到它」的距离，于是方树距离 = 仙人掌最短路；
// 询问的 LCA 是方点时再在环内取一条弧。
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 10005;   // 圆点个数
const int MAXEDGE = 12005; // 边数
const int MAXTOT = 30005; // 圆方树总点数
const int MAXLOG = 20;

int n, m, q, tot;
int head[MAXN + 2];
int toArr[2 * MAXEDGE], wtArr[2 * MAXEDGE], eidArr[2 * MAXEDGE];
int par[MAXN + 1], pare[MAXN + 1], dep[MAXN + 1];
ll dtree[MAXN + 1];
vector<vector<int> > rings; // 每个环的顶点表（环顶在前）
vector<vector<ll> > arcs;   // 环顶沿生成树到各点的距离
vector<ll> ringW;           // 每个环的真环长

int sqPar[MAXTOT + 1], sqDep[MAXTOT + 1];
ll sqW[MAXTOT + 1], sqPos[MAXTOT + 1], sd[MAXTOT + 1];
vector<int> sqChildren[MAXTOT + 1];
int up[MAXLOG][MAXTOT + 1];

void readGraph(const vector<int> &ex, const vector<int> &ey, const vector<int> &ew) {
    // CSR 邻接表：v 的出边在 [head[v], head[v+1])，按输入顺序
    vector<int> deg(n + 2, 0);
    for (int i = 0; i < m; ++i) {
        deg[ex[i]] += 1;
        deg[ey[i]] += 1;
    }
    head[0] = 0;
    head[1] = 0;
    for (int v = 1; v <= n; ++v) head[v + 1] = head[v] + deg[v];
    vector<int> fill(head, head + n + 2);
    for (int i = 0; i < m; ++i) {
        int j = fill[ex[i]];
        toArr[j] = ey[i]; wtArr[j] = ew[i]; eidArr[j] = i; fill[ex[i]] = j + 1;
        j = fill[ey[i]];
        toArr[j] = ex[i]; wtArr[j] = ew[i]; eidArr[j] = i; fill[ey[i]] = j + 1;
    }
}

void findRings() { // 迭代 DFS 建生成树，再让每条非树边圈出它所在的环
    vector<int> seen(n + 1, 0), used(m, 0);
    vector<int> ptr(head, head + n + 2), stk;
    for (int i = 1; i <= n; ++i) pare[i] = -1;
    seen[1] = 1;
    stk.push_back(1);
    while (!stk.empty()) {
        int v = stk.back();
        int j = ptr[v];
        if (j >= head[v + 1]) { // v 的出边扫完了
            stk.pop_back();
            continue;
        }
        ptr[v] = j + 1;
        if (eidArr[j] == pare[v]) continue; // 这条正是通向父节点的树边
        int u = toArr[j];
        if (seen[u]) {
            if (!used[eidArr[j]]) { // 两端都访问过，它就是非树边
                used[eidArr[j]] = 1;
                int top, bottom;
                if (dep[u] < dep[v]) { top = u; bottom = v; }
                else { top = v; bottom = u; }
                vector<int> nodes;
                vector<ll> arc;
                nodes.push_back(bottom);
                arc.push_back(dtree[bottom] - dtree[top]);
                int x = par[bottom];
                while (x != top) {
                    nodes.push_back(x);
                    arc.push_back(dtree[x] - dtree[top]);
                    x = par[x];
                }
                nodes.push_back(top);
                arc.push_back(0);
                reverse(nodes.begin(), nodes.end()); // 排成从环顶到环底
                reverse(arc.begin(), arc.end());
                rings.push_back(nodes);
                arcs.push_back(arc);
                ringW.push_back(arc.back() + wtArr[j]); // 生成树弧长 + 非树边 = 真环长
            }
            continue;
        }
        seen[u] = 1;
        par[u] = v; pare[u] = eidArr[j]; dep[u] = dep[v] + 1;
        dtree[u] = dtree[v] + wtArr[j];
        stk.push_back(u);
    }
}

void buildSquareTree() {
    tot = n + rings.size();
    for (int v = 2; v <= n; ++v) { // 不在环里的点：父边就是生成树的边
        sqPar[v] = par[v];
        sqW[v] = dtree[v] - dtree[par[v]];
    }
    for (int r = 1; r <= (int)rings.size(); ++r) {
        int S = n + r;
        ll L = ringW[r - 1];
        sqPar[S] = rings[r - 1][0]; // 方点挂在环顶下，边权 0
        for (int t = 1; t < (int)rings[r - 1].size(); ++t) {
            int v = rings[r - 1][t];
            ll pos = arcs[r - 1][t];
            sqPar[v] = S;
            sqW[v] = min(pos, L - pos); // 环顶到 t 的两条弧取短
            sqPos[v] = pos;             // t 在父环上的弧长坐标
        }
    }
    for (int v = 2; v <= tot; ++v) sqChildren[sqPar[v]].push_back(v);
    vector<int> order; // 层序遍历：同时算方树深度与根到点最短路
    order.push_back(1);
    for (int i = 0; i < (int)order.size(); ++i) {
        int v = order[i];
        for (int j = 0; j < (int)sqChildren[v].size(); ++j) {
            int c = sqChildren[v][j];
            sqDep[c] = sqDep[v] + 1;
            sd[c] = sd[v] + sqW[c];
            order.push_back(c);
        }
    }
}

int upK(int x, int k, int rows) { // 把 x 向上跳恰好 k 步
    int i = 0;
    while (k) {
        if (k & 1) x = up[i][x];
        k >>= 1;
        ++i;
    }
    return x;
}

int lca(int x, int y, int rows) {
    if (sqDep[x] < sqDep[y]) { int t = x; x = y; y = t; }
    x = upK(x, sqDep[x] - sqDep[y], rows);
    if (x == y) return x;
    for (int i = rows - 1; i >= 0; --i) {
        if (up[i][x] != up[i][y]) { x = up[i][x]; y = up[i][y]; }
    }
    return up[0][x];
}

int main() {
    if (scanf("%d %d %d", &n, &m, &q) != 3) return 0; // 空输入安全返回
    vector<int> ex(m), ey(m), ew(m);
    for (int i = 0; i < m; ++i) scanf("%d %d %d", &ex[i], &ey[i], &ew[i]);
    readGraph(ex, ey, ew);
    findRings();
    buildSquareTree();

    int rows = 1;
    while ((1 << rows) <= tot) ++rows; // rows = tot.bit_length()
    if (rows < 1) rows = 1;
    if (rows > MAXLOG) rows = MAXLOG;
    for (int v = 0; v <= tot; ++v) up[0][v] = sqPar[v];
    for (int k = 1; k < rows; ++k) {
        for (int v = 0; v <= tot; ++v) up[k][v] = up[k - 1][up[k - 1][v]];
    }

    for (int i = 0; i < q; ++i) {
        int x, y;
        scanf("%d %d", &x, &y);
        int a = lca(x, y, rows);
        if (a <= n) { // LCA 是圆点：两端最短路互不干扰
            printf("%lld\n", sd[x] + sd[y] - 2 * sd[a]);
        } else { // LCA 是方点：看清两端各自从环的哪个点进来，再在环内选一条弧
            int ax = upK(x, sqDep[x] - sqDep[a] - 1, rows);
            int ay = upK(y, sqDep[y] - sqDep[a] - 1, rows);
            ll d = sqPos[ax] - sqPos[ay];
            if (d < 0) d = -d;
            ll L = ringW[a - n - 1];
            ll other = L - d;
            printf("%lld\n", sd[x] + sd[y] - sd[ax] - sd[ay] + (d < other ? d : other));
        }
    }
    if (q == 0) printf("\n"); // 复刻 py 的空 out 仍输出一个换行
    return 0;
}
