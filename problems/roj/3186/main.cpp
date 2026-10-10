/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:30
 * update_at: 2026-10-10 13:30
 */

// 野餐规划：度限制最小生成树。缩掉 Park 跑 Kruskal，每块接最便宜的公园边，
// 再用剩余车位反复做「加公园边、删路径最重非公园边」的最优交换。
#include <algorithm>
#include <cstdio>
#include <map>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

const int PARK = 0;   // 公园固定编号为 0，人按出现顺序从 1 开始
const int MAXN = 105; // 人数不超过 20，节点总数留足余量

struct Edge { // 一条边：(权值, 端点 a, 端点 b)
    int w, a, b;
};

struct Node { // 树上路径扫描的栈元素
    int u, parent, wmx, eidx;
};

map<string, int> nameId; // 名字 -> 编号
int fa[MAXN];            // 并查集
int nodeCnt;             // 节点总数（含公园）
int chW[MAXN];           // 每个连通块用的最便宜公园边权
int chV[MAXN];           // 该公园边接的人
bool hasCh[MAXN];        // 该连通块是否已经接入
vector<int> roots;       // 连通块根的首次出现顺序
vector<Edge> roadE;      // 人—人边
vector<Edge> linkE;      // 人—公园边，存在 (w, 人, PARK)
vector<Edge> treeE;      // 当前生成树的边
vector<vector<int> > adj; // 邻接表，存 treeE 的下标
vector<Node> stk;

int findRoot(int x) { // 并查集查找（路径减半）
    while (fa[x] != x) {
        fa[x] = fa[fa[x]];
        x = fa[x];
    }
    return x;
}

int ident(const string &name) { // 名字 -> 编号，新名字按出现顺序编号
    map<string, int>::iterator it = nameId.find(name);
    if (it != nameId.end()) return it->second;
    int id = nameId.size();
    nameId[name] = id;
    return id;
}

bool cmpEdge(const Edge &x, const Edge &y) { // 按 (权, a, b) 字典序
    if (x.w != y.w) return x.w < y.w;
    if (x.a != y.a) return x.a < y.a;
    return x.b < y.b;
}

int worstOnPath(int src) { // src 到公园的树上路径中最重的非公园边，返回下标；没有则 -1
    adj.assign(nodeCnt, vector<int>());
    for (int i = 0; i < (int)treeE.size(); ++i) {
        adj[treeE[i].a].push_back(i);
        adj[treeE[i].b].push_back(i);
    }
    stk.clear();
    Node s;
    s.u = src; s.parent = PARK; s.wmx = -1; s.eidx = -1;
    stk.push_back(s);
    while (!stk.empty()) {
        Node cur = stk.back();
        stk.pop_back();
        for (int k = 0; k < (int)adj[cur.u].size(); ++k) {
            int idx = adj[cur.u][k];
            const Edge &e = treeE[idx];
            int v = (e.a == cur.u) ? e.b : e.a;
            if (v == cur.parent) continue;
            if (v == PARK) return cur.eidx; // 树上路径唯一，碰到公园即收工
            Node nx;
            nx.u = v;
            nx.parent = cur.u;
            if (e.w > cur.wmx) { nx.wmx = e.w; nx.eidx = idx; }
            else { nx.wmx = cur.wmx; nx.eidx = cur.eidx; }
            stk.push_back(nx);
        }
    }
    return -1;
}

int main() {
    int n;
    if (scanf("%d", &n) != 1) return 0; // 空输入安全返回
    nameId["Park"] = PARK;
    char s1[64], s2[64];
    int w;
    for (int i = 0; i < n; ++i) {
        if (scanf("%63s %63s %d", s1, s2, &w) != 3) break;
        int a = ident(string(s1)), b = ident(string(s2));
        if (a == PARK && b == PARK) continue; // 公园—公园的边没有意义
        Edge e;
        e.w = w;
        if (a == PARK || b == PARK) { // 人—公园边
            e.a = (a == PARK) ? b : a;
            e.b = PARK;
            linkE.push_back(e);
        } else { // 人—人边
            e.a = a;
            e.b = b;
            roadE.push_back(e);
        }
    }
    int s;
    if (scanf("%d", &s) != 1) s = 0;

    nodeCnt = nameId.size();
    for (int i = 0; i < nodeCnt; ++i) fa[i] = i;

    // 第一步：只用人—人边跑 Kruskal 得最小生成森林
    sort(roadE.begin(), roadE.end(), cmpEdge);
    for (int i = 0; i < (int)roadE.size(); ++i) {
        int ra = findRoot(roadE[i].a), rb = findRoot(roadE[i].b);
        if (ra != rb) {
            fa[ra] = rb;
            treeE.push_back(roadE[i]);
        }
    }

    // 每个连通块用最便宜的公园边接入公园，此时公园度数 = 连通块数 k
    for (int i = 0; i < (int)linkE.size(); ++i) {
        int root = findRoot(linkE[i].a);
        if (!hasCh[root]) {
            hasCh[root] = true;
            chW[root] = linkE[i].w;
            chV[root] = linkE[i].a;
            roots.push_back(root);
        } else if (linkE[i].w < chW[root]) {
            chW[root] = linkE[i].w;
            chV[root] = linkE[i].a;
        }
    }
    for (int i = 0; i < (int)roots.size(); ++i) {
        Edge e;
        e.w = chW[roots[i]];
        e.a = chV[roots[i]];
        e.b = PARK;
        treeE.push_back(e);
    }
    int k = roots.size();

    // 第二步：还有空车位时，反复做「加一条公园边、删路径上最重的非公园边」的交换
    for (int it = 0; it < s - k; ++it) {
        bool has = false;
        int bestGain = 0, bw = 0, bv = 0, bdrop = -1;
        for (int i = 0; i < (int)linkE.size(); ++i) {
            int drop = worstOnPath(linkE[i].a);
            if (drop < 0) continue; // 单人块没有内部边可删，加边只会翻倍停车
            int gain = linkE[i].w - treeE[drop].w;
            if (gain < 0 && (!has || gain < bestGain)) {
                has = true;
                bestGain = gain;
                bw = linkE[i].w;
                bv = linkE[i].a;
                bdrop = drop;
            }
        }
        if (!has) break; // 剩下的交换都会变贵，提前收手
        treeE.erase(treeE.begin() + bdrop);
        Edge e;
        e.w = bw;
        e.a = bv;
        e.b = PARK;
        treeE.push_back(e);
    }

    ll total = 0;
    for (int i = 0; i < (int)treeE.size(); ++i) total += treeE[i].w;
    printf("Total miles driven: %lld\n", total);
    return 0;
}
