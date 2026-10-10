/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:30
 * update_at: 2026-10-10 13:30
 */

// 桥 + 块树询问：先 Tarjan 求桥，删桥后给每个点标出 2-边连通块号，
// 再把块当点、桥当边建出桥森林；每次询问把 u,v 在森林路径上的桥逐一缩掉，
// 输出当前还没被任何一次询问覆盖过的桥数。
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

int n, m;
vector<int> head, nxt, toArr;

struct Frame { // 迭代 Tarjan 的栈帧
    int u, e, inArc; // 点、待处理的邻接弧、进入当前点的那条弧
};

vector<char> markBridges() { // 求桥：bridge[e] = 1 表示弧 e 属于某条桥
    vector<int> tin(n + 1, 0), low(n + 1, 0); // 0 兼作「没访问过」
    vector<char> bridge(toArr.size(), 0);
    int timer = 0;
    for (int s = 1; s <= n; ++s) {
        if (tin[s]) continue;
        timer += 1;
        tin[s] = low[s] = timer;
        vector<Frame> stk;
        Frame f;
        f.u = s; f.e = head[s]; f.inArc = -1;
        stk.push_back(f);
        while (!stk.empty()) {
            Frame top = stk.back();
            if (top.e) {
                stk.back().e = nxt[top.e];
                if (top.e == (top.inArc ^ 1)) continue; // 配对弧：无向边不能当回边用
                int v = toArr[top.e];
                if (tin[v]) {
                    if (tin[v] < low[top.u]) low[top.u] = tin[v];
                } else {
                    timer += 1;
                    tin[v] = low[v] = timer;
                    Frame nf;
                    nf.u = v; nf.e = head[v]; nf.inArc = top.e;
                    stk.push_back(nf);
                }
            } else {
                stk.pop_back();
                if (!stk.empty()) {
                    int p = stk.back().u;
                    if (low[top.u] < low[p]) low[p] = low[top.u];
                    if (low[top.u] > tin[p]) { // 子树回不到 p 之上，这条弧的边是桥
                        bridge[top.inArc] = 1;
                        bridge[top.inArc ^ 1] = 1;
                    }
                }
            }
        }
    }
    return bridge;
}

int findUF(vector<int> &uf, int x) { // 并查集找根 + 路径压缩（迭代写法）
    int r = x;
    while (uf[r] != r) r = uf[r];
    while (uf[x] != r) {
        int old = uf[x];
        uf[x] = r;
        x = old;
    }
    return r;
}

int main() {
    int caseNo = 0;
    while (true) {
        if (scanf("%d %d", &n, &m) != 2) break; // 输入结束
        if (n == 0 && m == 0) break;
        caseNo += 1;

        head.assign(n + 1, 0);
        nxt.assign(2 * m + 2, 0);
        toArr.assign(2 * m + 2, 0);
        for (int i = 1; i <= m; ++i) { // 无向边存成两条配对弧 2i 与 2i+1
            int a, b;
            scanf("%d %d", &a, &b);
            nxt[2 * i] = head[a]; toArr[2 * i] = b; head[a] = 2 * i;
            nxt[2 * i + 1] = head[b]; toArr[2 * i + 1] = a; head[b] = 2 * i + 1;
        }

        vector<char> bridge = markBridges();

        // 删掉所有桥后给每个点标出它所属的块
        vector<int> block(n + 1, 0);
        int blocks = 0;
        for (int s = 1; s <= n; ++s) {
            if (block[s]) continue;
            blocks += 1;
            block[s] = blocks;
            vector<int> stk;
            stk.push_back(s);
            while (!stk.empty()) {
                int u = stk.back();
                stk.pop_back();
                for (int e = head[u]; e; e = nxt[e]) {
                    int v = toArr[e];
                    if (!bridge[e] && !block[v]) {
                        block[v] = blocks;
                        stk.push_back(v);
                    }
                }
            }
        }

        int treeEdges = 0; // 桥数：两条配对弧都被标记，除以 2
        for (int i = 0; i < (int)bridge.size(); ++i) if (bridge[i]) treeEdges += 1;
        treeEdges /= 2;

        // 块当点、桥当边建桥森林（端点由配对弧 e 与 e^1 直接给出，只扫偶数弧）
        vector<int> thead(blocks + 1, 0), tnxt(2 * treeEdges + 2, 0), tto(2 * treeEdges + 2, 0);
        int cnt = 0;
        for (int e = 2; e < (int)toArr.size(); e += 2) {
            if (!bridge[e]) continue;
            int x = block[toArr[e]], y = block[toArr[e ^ 1]];
            cnt += 1;
            tnxt[cnt] = thead[x]; tto[cnt] = y; thead[x] = cnt;
            cnt += 1;
            tnxt[cnt] = thead[y]; tto[cnt] = x; thead[y] = cnt;
        }
        vector<int> tparent(blocks + 1, 0), tdepth(blocks + 1, 0); // 0 = 没访问过，-1 = 树根
        for (int s = 1; s <= blocks; ++s) {
            if (tparent[s]) continue;
            tparent[s] = -1;
            vector<int> stk;
            stk.push_back(s);
            while (!stk.empty()) {
                int u = stk.back();
                stk.pop_back();
                for (int e = thead[u]; e; e = tnxt[e]) {
                    int v = tto[e];
                    if (tparent[v] == 0) {
                        tparent[v] = u;
                        tdepth[v] = tdepth[u] + 1;
                        stk.push_back(v);
                    }
                }
            }
        }

        int remaining = treeEdges;
        vector<int> uf(blocks + 1);
        for (int i = 0; i <= blocks; ++i) uf[i] = i;

        int q;
        scanf("%d", &q);
        if (caseNo > 1) printf("\n"); // 复刻 py 的用例之间空一行
        printf("Case %d:\n", caseNo);
        for (int i = 0; i < q; ++i) {
            int a, b;
            scanf("%d %d", &a, &b);
            int u = findUF(uf, block[a]), v = findUF(uf, block[b]);
            while (u != v) { // 只会往上并
                if (tdepth[u] < tdepth[v]) { int t = u; u = v; v = t; }
                int up = tparent[u]; // 深的一侧到父亲的桥必然落在路径上
                uf[u] = findUF(uf, up);
                u = uf[u];
                remaining -= 1;
            }
            printf("%d\n", remaining);
        }
    }
    return 0;
}
