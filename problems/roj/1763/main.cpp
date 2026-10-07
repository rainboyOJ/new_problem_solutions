/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 23:00
 * update_at: 2026-10-07 23:00
 */
// main.cpp：一本通 1763《简单树》。带权树上的「编号区间到定点距离和」询问，可强制在线。
//
// 与 main.py 同一算法：点分治 + 前缀和 + 二分。
// 记 c 为 i、x 在点分树上的 LCA，此时 c 一定落在树上 i→x 的路径上，于是
//     dist(i,x) = dist(i,c) + dist(c,x)。
// 把 i 按 c = LCA(i,x) 分组（c 恰好遍历 x 的点分树祖先链），
//     Σ_{i∈[L,R]} dist(i,x) = Σ_c [ Σ_{i∈[L,R], LCA=c} dist(i,c)
//                                 + #{i∈[L,R], LCA=c} * dist(c,x) ]，
// 其中「LCA(i,x) = c」的 i 集合 = comp(c) \ comp(b)，b 是 c 在点分树上通往 x 的儿子。
// 对每个重心 c 预处理：
//   compNodes[c] / compPref[c]  —— 其管辖连通块内的点按编号升序 + 到 c 的距离前缀和；
//   brNodes[b]   / brPref[b]    —— b 管辖的连通块内的点按编号升序 + 到「父重心」的距离前缀和。
// 两者都用编号升序排列，故 #{i ≤ k, i∈S} 与对应的距离和都是一次二分 + 前缀和。
// 复杂度：预处理 O(n log n)，单次询问 O(log^2 n)（沿祖先链 O(log n) 次二分），空间 O(n log n)。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 60005;

int n, m, typeFlag;

// 邻接表（链式前向星）
int head[MAXN], nxt[MAXN << 1], to[MAXN << 1], ecnt;
ll wt[MAXN << 1];

bool removed[MAXN];      // 点分治中已被摘掉的重心
int sz[MAXN];            // 连通块内以 start 为根时的子树大小
int par[MAXN];           // 上面那次 BFS 的父指针（多次复用）
ll distc[MAXN];          // 到当前重心的距离
int order[MAXN];         // BFS 序缓冲

vector<int> ancC[MAXN];  // ancC[v]：v 的点分树祖先链（根在前，末尾是 v 自己）
vector<ll> ancD[MAXN];   // ancD[v][j] = dist(ancC[v][j], v)

vector<int> compNodes[MAXN];  // 重心 c 管辖连通块内的点，按编号升序
vector<ll> compPref[MAXN];    // 对应的「到 c 的距离」前缀和，compPref[c][0] = 0
vector<int> brNodes[MAXN];    // 重心 b 管辖连通块内的点，按编号升序
vector<ll> brPref[MAXN];      // 对应的「到 b 的父重心」的距离前缀和

void addEdge(int a, int b, ll c) {
    to[++ecnt] = b; wt[ecnt] = c; nxt[ecnt] = head[a]; head[a] = ecnt;
}

// 点分治：迭代实现（显式栈 + BFS），避免链形数据深度 6e4 时爆栈。
// 顺带把每个重心管辖块的「编号升序点表 + 距离前缀和」建好，
// 并把 (重心, 距离) 追加到块内每个点的祖先链上（父重心先于子重心处理，故链天然根在前）。
void decompose() {
    vector<int> stk;
    stk.push_back(1);
    while (!stk.empty()) {
        int start = stk.back();
        stk.pop_back();

        // 1) BFS 收集连通块，并得到以 start 为根的父子关系
        int qt = 0;
        order[qt++] = start;
        par[start] = 0;
        for (int qi = 0; qi < qt; ++qi) {
            int u = order[qi];
            for (int e = head[u]; e; e = nxt[e]) {
                int v = to[e];
                if (v != par[u] && !removed[v]) { par[v] = u; order[qt++] = v; }
            }
        }
        int total = qt;

        // 2) 逆 BFS 序求子树大小
        for (int i = total - 1; i >= 0; --i) {
            int u = order[i];
            sz[u] = 1;
            for (int e = head[u]; e; e = nxt[e]) {
                int v = to[e];
                if (v != par[u] && !removed[v]) sz[u] += sz[v];
            }
        }

        // 3) 从 start 沿「大小 > total/2 的重儿子」往下走，落到重心
        int c = start;
        for (;;) {
            int go = 0;
            for (int e = head[c]; e; e = nxt[e]) {
                int v = to[e];
                if (v != par[c] && !removed[v] && sz[v] * 2 > total) { go = v; break; }
            }
            if (!go) break;
            c = go;
        }

        // 3.5) 本块是上一层的某个分支，父重心侧的「到父重心距离前缀和」挂在分支代表 start 上，
        //      现在本块的重心 c 才是点分树上这一层的节点，把它转交给 c。
        if (start != c) {
            brNodes[c].swap(brNodes[start]);
            brPref[c].swap(brPref[start]);
        }

        // 4) 从重心 c 出发 BFS，求块内各点到 c 的距离
        qt = 0;
        order[qt++] = c;
        par[c] = 0;
        distc[c] = 0;
        for (int qi = 0; qi < qt; ++qi) {
            int u = order[qi];
            for (int e = head[u]; e; e = nxt[e]) {
                int v = to[e];
                if (v != par[u] && !removed[v]) {
                    par[v] = u;
                    distc[v] = distc[u] + wt[e];
                    order[qt++] = v;
                }
            }
        }
        total = qt;

        // 5) 登记祖先链 + 该重心管辖块的「编号升序点表 / 距离前缀和」
        compNodes[c].reserve(total);
        compPref[c].reserve(total + 1);
        compPref[c].push_back(0);
        for (int i = 0; i < total; ++i) compNodes[c].push_back(order[i]);
        sort(compNodes[c].begin(), compNodes[c].end());
        for (int i = 0; i < total; ++i) {
            int v = compNodes[c][i];
            ancC[v].push_back(c);
            ancD[v].push_back(distc[v]);
            compPref[c].push_back(compPref[c].back() + distc[v]);
        }

        // 6) 摘掉重心，各分支成为独立的子问题；分支代表就是 c 的未摘邻居
        removed[c] = true;
        for (int e = head[c]; e; e = nxt[e]) {
            int v = to[e];
            if (!removed[v]) {
                stk.push_back(v);
                // 该分支内的点到「父重心 c」的距离前缀和（分支重心稍后才知道是谁，
                // 这里先挂在分支代表 v 上，等该分支处理时再转交给它的重心）
                int bt = 0;
                order[bt++] = v;
                par[v] = c;
                distc[v] = wt[e];
                for (int qi = 0; qi < bt; ++qi) {
                    int u = order[qi];
                    for (int f = head[u]; f; f = nxt[f]) {
                        int w = to[f];
                        if (w != par[u] && !removed[w]) {
                            par[w] = u;
                            distc[w] = distc[u] + wt[f];
                            order[bt++] = w;
                        }
                    }
                }
                vector<int> &bn = brNodes[v];
                bn.assign(order, order + bt);
                sort(bn.begin(), bn.end());
                vector<ll> &bp = brPref[v];
                bp.assign(bt + 1, 0);
                for (int i = 0; i < bt; ++i) bp[i + 1] = bp[i] + distc[bn[i]];
            }
        }
    }
}

// Σ_{i=L..R} dist(i,x)：沿 x 的点分树祖先链累加「按 LCA 分组」的两项贡献。
ll queryRange(int L, int R, int x) {
    const vector<int> &cs = ancC[x];
    const vector<ll> &ds = ancD[x];
    int len = (int)cs.size();
    ll tot = 0;
    for (int j = 0; j + 1 < len; ++j) {
        int c = cs[j], b = cs[j + 1];
        const vector<int> &cn = compNodes[c];
        const vector<ll> &cp = compPref[c];
        const vector<int> &bn = brNodes[b];
        const vector<ll> &bp = brPref[b];
        // 编号 ≤ k 的点数（即 [1,k] 与集合的交集大小）
        int nR = (int)(upper_bound(cn.begin(), cn.end(), R) - cn.begin());
        int nL = (int)(upper_bound(cn.begin(), cn.end(), L - 1) - cn.begin());
        int mR = (int)(upper_bound(bn.begin(), bn.end(), R) - bn.begin());
        int mL = (int)(upper_bound(bn.begin(), bn.end(), L - 1) - bn.begin());
        // (comp(c) \ comp(b)) ∩ [L,R] 内的「到 c 的距离和」+ 「点数 * dist(c,x)」
        tot += (cp[nR] - cp[nL]) - (bp[mR] - bp[mL]) + (ll)((nR - nL) - (mR - mL)) * ds[j];
    }
    int c = cs[len - 1];  // c == x 这一层：分支为空，dist(c,x) = 0，只剩距离和
    const vector<int> &cn = compNodes[c];
    const vector<ll> &cp = compPref[c];
    int nR = (int)(upper_bound(cn.begin(), cn.end(), R) - cn.begin());
    int nL = (int)(upper_bound(cn.begin(), cn.end(), L - 1) - cn.begin());
    tot += cp[nR] - cp[nL];
    return tot;
}

int main() {
    if (scanf("%d %d %d", &n, &m, &typeFlag) != 3) return 0;

    for (int i = 1; i < n; ++i) {
        int a, b;
        ll c;
        scanf("%d %d %lld", &a, &b, &c);
        addEdge(a, b, c);
        addEdge(b, a, c);
    }

    decompose();

    ll last = 0;
    for (int i = 0; i < m; ++i) {
        ll L, R, X;
        scanf("%lld %lld %lld", &L, &R, &X);
        if (typeFlag) { L ^= last; R ^= last; X ^= last; }
        ll ans = queryRange((int)L, (int)R, (int)X);
        printf("%lld\n", ans);
        last = ans % n;
    }
    return 0;
}
