// ===========================================================================
//  题目：消息传递（ROJ 1773 / 信息学奥赛一本通 · 高手训练篇 动态规划）
//  算法：树上换根 DP + 前缀 / 后缀最大值
// ---------------------------------------------------------------------------
//  1. 上下级关系只是一棵无向树：消息既能上报也能下达，所以直接按无向边建树。
//  2. 以 1 号（国王）为根，自底向上求 f[u]：u 在 0 时刻收到消息时，
//     把消息传遍 u 的整棵子树所需的时间。
//     若 u 有 k 个儿子，按 f 从大到小排序后第 i 个儿子在第 i 秒被通知，
//     故 f[u] = max_i ( i + f[son_i] )，叶子 f[u] = 0。
//  3. 自顶向下换根：把 u 的所有“方向”放在一起降序排序成 w[1..m]
//     （儿子方向取 f[son]，父亲方向取 up[u]），预处理
//        pref[i] = max_{j<=i} ( j + w[j] )
//        suff[i] = max_{j>=i} ( j - 1 + w[j] )
//     去掉排在第 idx 位的儿子 v 之后，u 这一侧从 u 开始扩散完的时间
//        up[v] = max( pref[idx-1], suff[idx+1] )
//     这正是 v 作为根时“父亲方向”的耗时（后面的元素集体前移一位）。
//  4. g[u] = pref[m]（u 无邻居时为 0）= u 在 0 时刻收到消息后传遍全树的时间。
//     答案第一行 = 1 + min g[u]（初始通知那个人要花 1 单位时间），
//     第二行 = 所有取到最小值的 u，按编号升序输出。
//  复杂度：时间 O(N log N)（每个点的邻居排序，Σd = 2N-2），空间 O(N)。
// ===========================================================================
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<int, int> pii;

const int MAXN = 200005;

int n;
int head[MAXN], nxt[2 * MAXN], to[2 * MAXN], ecnt;  // 邻接表（链式前向星）
int par[MAXN];    // 以 1 为根时的父亲
int ord[MAXN];    // BFS 序（父亲一定排在儿子前面）
int f[MAXN];      // f[u]：u 的子树内部扩散耗时
int up_[MAXN];    // up_[u]：u 的父亲方向那半棵树的扩散耗时
int g[MAXN];      // g[u]：以 u 为起点时，全树扩散耗时（不含最初那 1 单位）

void addEdge(int u, int v) {
    to[++ecnt] = v;
    nxt[ecnt] = head[u];
    head[u] = ecnt;
}

int main() {
    scanf("%d", &n);
    for (int i = 2; i <= n; i++) {
        int p;
        scanf("%d", &p);
        addEdge(p, i);
        addEdge(i, p);
    }

    // 第一步：BFS 定序（避免 N=200000 的链把递归栈爆掉）
    int cnt = 0;
    ord[++cnt] = 1;
    par[1] = 0;
    for (int i = 1; i <= cnt; i++) {
        int u = ord[i];
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v == par[u]) continue;
            par[v] = u;
            ord[++cnt] = v;
        }
    }

    // 第二步：自底向上求 f[u]
    for (int i = n; i >= 1; i--) {
        int u = ord[i];
        vector<int> vals;
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v != par[u]) vals.push_back(f[v]);
        }
        sort(vals.begin(), vals.end(), greater<int>());  // 耗时大的子树优先通知
        int best = 0;
        for (int j = 0; j < (int)vals.size(); j++) {
            best = max(best, (j + 1) + vals[j]);
        }
        f[u] = best;
    }

    // 第三步：自顶向下换根，顺便算出 g[u]
    for (int i = 1; i <= n; i++) {
        int u = ord[i];
        vector<pii> items;  // (该方向的耗时, 该方向的邻居编号)
        for (int e = head[u]; e; e = nxt[e]) {
            int v = to[e];
            if (v == par[u]) {
                if (u != 1) items.push_back(pii(up_[u], v));  // 父亲方向
            } else {
                items.push_back(pii(f[v], v));                // 儿子方向
            }
        }
        sort(items.begin(), items.end(), greater<pii>());
        int m = items.size();
        vector<int> pref(m + 2, 0), suff(m + 3, 0);
        for (int j = 1; j <= m; j++) pref[j] = max(pref[j - 1], j + items[j - 1].first);
        for (int j = m; j >= 1; j--) suff[j] = max(suff[j + 1], (j - 1) + items[j - 1].first);
        g[u] = pref[m];
        for (int j = 1; j <= m; j++) {
            int v = items[j - 1].second;
            if (par[v] == u) {  // v 是 u 的儿子：算出 v 的父亲方向耗时
                up_[v] = max(pref[j - 1], suff[j + 1]);
            }
        }
    }

    // 第四步：统计答案
    int best = g[1];
    for (int u = 2; u <= n; u++) best = min(best, g[u]);
    int T = 1 + best;  // 初始通知要花 1 单位时间

    printf("%d\n", T);
    bool first = true;
    for (int u = 1; u <= n; u++) {
        if (g[u] == best) {
            if (!first) printf(" ");
            printf("%d", u);
            first = false;
        }
    }
    printf("\n");
    return 0;
}
