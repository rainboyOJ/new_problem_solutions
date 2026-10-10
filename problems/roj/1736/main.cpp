/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 20:20
 * update_at: 2026-10-07 20:40
 */
// main.cpp：一本通 1736《最大连通块》，删掉一个点使剩余图的最大连通块最小。
//
// 关键观察：gcd(a_u, a_v) 是合数 <=> gcd 的质因数分解里至少有两个质因子（按重数计）
//   <=> 存在“见证数” w ∈ { p*q | p<q 为质数 } ∪ { p^2 | p 为质数 }
// 同时整除 a_u 与 a_v。于是把每个出现过的见证数也当成一个点，建成二部图
//   （左侧 = 原来的 n 个点，右侧 = 见证数），原点 u 连向它所有的见证数。
// 引理 1：二部图里两个原点的连通性与原图中一样（相邻原点夹着一个公共见证数，
//         反过来原图的每条边都对应一个公共见证数）。
// 引理 2：见证数点永远不会被删掉，所以删掉原点 x 后，原图的连通块 = 二部图删 x 后
//         的连通块（只数原点）。
// 于是只需在二部图上跑一趟 Tarjan（dfn / low / 子树里的原点个数），就能对每个原点 x
// 在 O(deg x) 内算出“删 x 后的最大连通块”，取最小值即答案。
//
// 复杂度：线性筛 O(maxA)，每组数据 O(n log maxA) 分解 + O((n + |W|)·36) 建图与 Tarjan。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 100000;                      // n 的上限
const int MAXA = 10000000;                    // a_i 的上限（筛法只开到实际最大值）
const int MAXWIT = 36;                        // 单点见证数上限：C(8,2)+8 = 36（1e7 内最多 8 个不同质因子）
const int MAXWREL = MAXWIT * MAXN + 10;       // “原点 -> 见证数”关系条数上限（见证数个数不超过它）
const int MAXNODE = (MAXWIT + 1) * MAXN + 10; // 二部图点数上限：原点 + 见证数

int spf[MAXA + 1];   // spf[x] = x 的最小质因子，线性筛（x 为质数时即 x 本身）
int wid[MAXA + 1];   // wid[d] = 见证数 d 在当前这组数据内分到的局部编号；配合 baseId 判“本轮是否已分配”
int wrel[MAXWREL];   // 扁平存“原点 i 的见证数”，第 i 个原点的区间由 woff[i] 起
int woff[MAXN + 2];  // 原点的关系区间起点

int wdeg[MAXWREL];   // 每个见证数（局部编号）被多少个原点共享

// 一组数据：点数 + 点权序列。用 struct 聚合，避免下标平行的多个数组。
struct TestCase {
    int n;          // 这组数据的点数
    vector<int> a;  // 这组数据的点权 a[0..n-1]
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    if (!(cin >> T)) return 0;

    // 先把所有数据读进来，才知道最小质因子筛要开到多大
    vector<TestCase> tests(T);
    int maxA = 2; // 筛法上界 = 所有 a_i 的最大值
    for (int t = 0; t < T; t++) {
        cin >> tests[t].n;
        tests[t].a.resize(tests[t].n);
        for (int i = 0; i < tests[t].n; i++) {
            cin >> tests[t].a[i];
            if (tests[t].a[i] > maxA) maxA = tests[t].a[i];
        }
    }

    // 线性筛最小质因子：分解一个数时每次至少消掉一个质因子
    {
        vector<int> primes;
        primes.reserve(maxA / 10 + 16);
        for (int i = 2; i <= maxA; i++) {
            if (spf[i] == 0) {
                spf[i] = i;
                primes.push_back(i);
            }
            for (size_t j = 0; j < primes.size(); j++) {
                ll p = primes[j]; // 声明成 ll，p * i 就按 64 位算，不会溢出
                if (p > spf[i] || p * i > maxA) break;
                spf[p * i] = p;
            }
        }
    }

    int fresh = 0;        // 全局单调递增的见证数计数；本组新建的见证数编号是 baseId+1 .. fresh
    int pr[16];           // 临时存放一个数的不同质因子
    int pe[16];           // 对应的指数
    vector<int> ofs;      // CSR 的行起始下标，ofs[N] 是总边数（无向边双向各存一条）
    vector<int> adj;      // CSR 的边表
    vector<int> disc, low, par, itp, sz, comp;
    vector<int> compTot;  // compTot[c] = 连通块 c 里的原点个数
    vector<int> stk;      // 迭代 DFS 的手写栈

    for (int t = 0; t < T; t++) {
        int n = tests[t].n;
        int baseId = fresh;

        // 1) 分解每个 a_i，枚举它的全部见证数，给“本组首次出现”的见证数分配局部编号
        woff[0] = 0;
        int we = 0;
        for (int i = 0; i < n; i++) {
            int x = tests[t].a[i];
            int k = 0;
            while (x > 1) {
                int p = spf[x], e = 0;
                while (x % p == 0) {
                    x /= p;
                    e++;
                }
                pr[k] = p;
                pe[k] = e;
                k++;
            }
            // p*q 型见证：两个不同质数同时整除等号右边的 gcd
            for (int j = 0; j < k; j++) {
                for (int j2 = j + 1; j2 < k; j2++) {
                    int d = pr[j] * pr[j2];
                    if (wid[d] <= baseId) wid[d] = ++fresh;
                    wrel[we++] = wid[d] - baseId - 1; // 见证数的局部编号
                }
                // p^2 型见证：某个质数在 gcd 里出现两次以上
                if (pe[j] >= 2) {
                    int d = pr[j] * pr[j];
                    if (wid[d] <= baseId) wid[d] = ++fresh;
                    wrel[we++] = wid[d] - baseId - 1;
                }
            }
            woff[i + 1] = we;
        }

        int W = fresh - baseId; // 本组用到的见证数个数
        int N = n + W;          // 二部图点数：前 n 个是原点，后面是见证数

        // 2) 建二部图的 CSR：先数见证数度数，再算行起始，最后填边表
        for (int w = 0; w < W; w++) wdeg[w] = 0;
        for (int e = 0; e < we; e++) wdeg[wrel[e]]++;
        ofs.assign(N + 1, 0);
        for (int v = 0; v < n; v++) ofs[v + 1] = ofs[v] + (woff[v + 1] - woff[v]);
        for (int w = 0; w < W; w++) ofs[n + w + 1] = ofs[n + w] + wdeg[w];
        adj.assign(ofs[N], 0);
        {
            vector<int> pos(ofs.begin(), ofs.begin() + N); // 每个顶点的“下一个空位”
            for (int i = 0; i < n; i++) {
                for (int e = woff[i]; e < woff[i + 1]; e++) {
                    int w = n + wrel[e];
                    adj[pos[i]++] = w;
                    adj[pos[w]++] = i;
                }
            }
        }

        // 3) 迭代 Tarjan：dfn / low / 父亲 / 子树里的原点个数 / 连通块原点总数
        disc.assign(N, 0);
        low.assign(N, 0);
        par.assign(N, -1);
        itp.assign(N, 0);
        sz.assign(N, 0);
        comp.assign(N, 0);
        compTot.clear();
        stk.reserve(N);

        int timer = 0;
        for (int s = 0; s < N; s++) {
            if (disc[s]) continue;
            int cid = (int)compTot.size();
            int cnt = 0;
            disc[s] = low[s] = ++timer;
            par[s] = -1;
            itp[s] = ofs[s];
            sz[s] = (s < n) ? 1 : 0; // 只有原点计入块大小
            comp[s] = cid;
            if (s < n) cnt++;
            stk.clear();
            stk.push_back(s);
            while (!stk.empty()) {
                int v = stk.back();
                if (itp[v] < ofs[v + 1]) {
                    int u = adj[itp[v]++];
                    if (u == par[v]) continue; // 不走回 DFS 树上父亲的那条边
                    if (disc[u] == 0) {
                        disc[u] = low[u] = ++timer;
                        par[u] = v;
                        itp[u] = ofs[u];
                        sz[u] = (u < n) ? 1 : 0;
                        comp[u] = cid;
                        if (u < n) cnt++;
                        stk.push_back(u);
                    } else if (disc[u] < low[v]) {
                        low[v] = disc[u]; // 回边：low 取 dfn 更小的那个
                    }
                } else {
                    stk.pop_back();
                    int p = par[v];
                    if (p != -1) {
                        if (low[v] < low[p]) low[p] = low[v];
                        sz[p] += sz[v];
                    }
                }
            }
            compTot.push_back(cnt);
        }

        // 4) 各连通块原点数的最大 / 次大 / 最大者个数
        //    （最大值并列时，“其他连通块的最大值”仍然等于最大值，所以必须记个数）
        int t1 = 0, t2 = 0, cnt1 = 0;
        for (size_t c = 0; c < compTot.size(); c++) {
            int v = compTot[c];
            if (v > t1) {
                t2 = t1;
                t1 = v;
                cnt1 = 1;
            } else if (v == t1) {
                cnt1++;
            } else if (v > t2) {
                t2 = v;
            }
        }

        // 5) 对每个原点 x 算“删 x 后最大连通块”，取最小值
        int best = INT_MAX;
        for (int x = 0; x < n; x++) {
            int cid = comp[x];
            int ctot = compTot[cid];
            int other = (ctot == t1 && cnt1 == 1) ? t2 : t1; // x 之外其他连通块的最大值
            int rest = ctot - 1;  // x 所在块去掉 x 与被切出的子树后剩下的主体
            int sepMax = 0;       // 被 x 切出去的最大子树
            for (int e = ofs[x]; e < ofs[x + 1]; e++) {
                int u = adj[e];
                if (par[u] == x && low[u] >= disc[x]) { // 这个儿子子树被 x 切掉
                    if (sz[u] > sepMax) sepMax = sz[u];
                    rest -= sz[u];
                }
            }
            int M = max(sepMax, max(rest, other));
            if (M < best) best = M;
        }
        cout << best << "\n";
    }
    return 0;
}
