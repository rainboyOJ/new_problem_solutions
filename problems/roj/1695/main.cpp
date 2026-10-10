/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 16:01
 * update_at: 2026-10-07 16:01
 */
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int MAXN = 100005; // n <= 10^5，树 B 有 n + 1 <= 100001 个点，编号 1 .. n+1

int n;                // 树 A 的点数（题面的 N）
vector<int> gA[MAXN]; // 树 A 的邻接表
vector<int> gB[MAXN]; // 树 B 的邻接表，点数 n + 1

// 一棵被"固定根"的树里，每个点的信息聚合成 node[u]（先服务树 A，再复用来服务树 B）
struct Node {
    int par;   // 当前固定根意义下 u 的父亲，根的 par 为 0
    int sz;    // 以 u 为根的子树大小（点数）
    ull sub;   // u 子树的哈希：sub(u) = mix(sz(u)) + Σ mix(sub(孩子))
    ull full;  // 整棵树换成以 u 为根时的哈希
};
Node node[MAXN];

int order[MAXN];  // DFS 序，保证父亲排在儿子前面
int ordCnt;       // DFS 序的长度，也就是当前被处理树的点数
ull rootA[MAXN];  // 树 A 在 n 个点分别作根时的整树哈希，升序排列，供二分查找

// splitmix64 的收尾混淆：把整数打散成雪崩良好的 64 位伪随机数
ull mix(ull x) {
    x += 0x9e3779b97f4a7c15ULL;
    x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ULL;
    x = (x ^ (x >> 27)) * 0x94d049bb133111ebULL;
    return x ^ (x >> 31);
}

// 无向边加进邻接表
void add_edge(vector<int> *g, int u, int v) {
    g[u].push_back(v);
    g[v].push_back(u);
}

// 迭代式 DFS：求以 root 为根的 par 与"先父后子"的 order（深链也不会爆栈）
void dfs_order(vector<int> *g, int root) {
    static int stk[MAXN];
    int top = 0;
    ordCnt = 0;
    node[root].par = 0;
    stk[top] = root;
    top++;
    while (top > 0) {
        top--;
        int u = stk[top];
        order[ordCnt] = u;
        ordCnt++;
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == node[u].par) continue; // 树上只有父亲这一个邻居已经走过
            node[v].par = u;
            stk[top] = v;
            top++;
        }
    }
}

// 按 order 的逆序自底向上求子树大小与子树哈希
// 孩子哈希先过 mix 再相加，这样"去掉一个孩子"只需从和里减去它的贡献
void calc_subtree(vector<int> *g) {
    for (int i = ordCnt - 1; i >= 0; i--) {
        int u = order[i];
        int s = 1;  // 先算上自己这个点
        ull h = 0;  // 孩子贡献之和
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (v == node[u].par) continue;
            s += node[v].sz;
            h += mix(node[v].sub);
        }
        node[u].sz = s;
        node[u].sub = mix((ull)s) + h;
    }
}

// 换根：整棵树共 total 个点，由 u 的 full 推出儿子 v 的 full
//   割掉边 (u,v) 后 u 那一侧的哈希（共 total - sz(v) 个点）：
//       up = mix(total - sz(v)) + (full(u) - mix(total) - mix(sub(v)))
//   括号里就是把 u 的大小项和儿子 v 的贡献摘掉，剩下的正是 u 朝其余方向的一切
//   full(v) = mix(total) + (sub(v) - mix(sz(v))) + mix(up)
void calc_full(vector<int> *g, int total) {
    ull mixTotal = mix((ull)total);
    node[order[0]].full = node[order[0]].sub; // 出发点没有"上方"，full 就等于子树哈希
    for (int i = 0; i < ordCnt; i++) {
        int u = order[i];
        for (int j = 0; j < (int)g[u].size(); j++) {
            int v = g[u][j];
            if (v == node[u].par) continue;
            ull up = mix((ull)(total - node[v].sz)) + node[u].full - mixTotal - mix(node[v].sub);
            node[v].full = mixTotal + (node[v].sub - mix((ull)node[v].sz)) + mix(up);
        }
    }
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n - 1; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(gA, x, y);
    }
    for (int i = 1; i <= n; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        add_edge(gB, x, y);
    }

    if (n == 1) {
        // 树 A 是单点树，树 B 只有一条边，删掉哪个叶子剩下的都是单点树
        printf("1\n");
        return 0;
    }

    // ---- 树 A：求出以每个点为根时的整树哈希，排序后备用 ----
    dfs_order(gA, 1);
    calc_subtree(gA);
    calc_full(gA, n);
    for (int u = 1; u <= n; u++) rootA[u] = node[u].full;
    sort(rootA + 1, rootA + n + 1);

    // ---- 树 B：n + 1 个点，取一个度数大于 1 的点当根（n >= 2 时一定存在） ----
    int rootB = 1;
    for (int v = 1; v <= n + 1; v++) {
        if ((int)gB[v].size() > 1) {
            rootB = v;
            break;
        }
    }
    dfs_order(gB, rootB);
    calc_subtree(gB);
    calc_full(gB, n + 1);

    // 逐个检查 B 的叶子 x：设它的唯一邻居是 u，删掉 x 后以 u 为根的 n 点树哈希为
    //   full(u) - mix(n+1) + mix(n) - mix(sub(x))
    // 叶子没有孩子，sub(x) 就是 mix(1)，直接减掉这一份贡献即可
    int ans = n + 2; // 题面保证有解，这是保险初值
    ull mixB = mix((ull)(n + 1));
    ull mixN = mix((ull)n);
    for (int x = 1; x <= n + 1; x++) {
        if ((int)gB[x].size() != 1) continue; // 只看叶子
        int u = node[x].par;                  // 叶子唯一的邻居
        ull h = node[u].full - mixB + mixN - mix(node[x].sub);
        if (binary_search(rootA + 1, rootA + n + 1, h) && x < ans) ans = x;
    }

    printf("%d\n", ans);
    return 0;
}
