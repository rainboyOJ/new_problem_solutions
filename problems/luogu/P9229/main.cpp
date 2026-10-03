/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 15:07
 * update_at: 2026-10-02 15:07
 */
// P9229 简单九连环
//
// 把 n+1 个环的所有状态看成图的点，一次环的上下是一次翻转，这张图是一棵树。
// 记 T_k 为“只看前 k 个环、规则仍用整串 s”的状态树，则 T_k 由两棵 T_{k-1}
// 拼成，中间用第 k 个环那条边相连；连接点恰是 t_1..t_{k-1} 等于 s 的长度
// k-1 后缀的那个状态。
//
// 设 W(k,p) 表示状态 t_i = s[p-k+i]（s 上以 p 结尾的一段，越界当 0 看）。
// 树内距离可以递归：
//   G(k,p1,p2) = dist_{T_k}(W(k,p1), W(k,p2))
//     s[p1]==s[p2]（同侧）: G(k,p1,p2) = G(k-1,p1-1,p2-1)
//     否则（跨桥）        : G(k,p1,p2) = G(k-1,p1-1,n) + 1 + G(k-1,n,p2-1)
//   A(k,p) = dist_{T_k}(0^k, W(k,p))
//     s[p]==0: A(k,p) = A(k-1,p-1)
//     s[p]==1: A(k,p) = A(k-1,n) + 1 + G(k-1,p-1,n)
//   X(k,p) = dist_{T_k}(W(k,p), 1^k)
//     s[p]==1: X(k,p) = X(k-1,p-1)
//     s[p]==0: X(k,p) = G(k-1,p-1,n) + 1 + X(k-1,n)
//
// 起点 0^{n+1} 到终点 1^{n+1} 必然经过第 n+1 个环那条桥，桥的两端在 T_n 中
// 分别是 0^n 与 1^n（都对应 t_1..t_n = s），于是
//   答案 = A(n,n) + 1 + X(n,n)。
//
// 沿 A、X 两条链，每层只产生一个 G 查询；这些查询的 (p1,p2) 再向下展开，
// 总状态数是 O(n^2) 的。实现：先自上而下收集每层要用的 (p1,p2)，再自下而上
// 逐层按上式计算数值。

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int MOD = 1000000007;
const int maxn = 2005;
const int OFF = 3;          // 打包下标时的偏移，保证 -1 也能编码
const int SHIFT = 12;       // n <= 2000，12 位足够放下

int n;
char str[maxn];
int c[maxn];                // c[p] = s[p]，p 越界时按 0 处理

inline int ch(int p) {
    if (p < 1 || p > n) return 0;
    return c[p];
}

// 把 (p1,p2)（可含 -1）打包成非负整数，并统一成 p1 <= p2
inline int pack_pair(int p1, int p2) {
    if (p1 > p2) swap(p1, p2);
    return ((p1 + OFF) << SHIFT) | (p2 + OFF);
}
inline int key_first(int key) { return (key >> SHIFT) - OFF; }
inline int key_second(int key) { return (key & ((1 << SHIFT) - 1)) - OFF; }

vector<int> layer[maxn];    // layer[k]：第 k 层需要计算的 (p1,p2)，有序去重
vector<int> dp[maxn];       // dp[k][i]：layer[k][i] 对应的 G 值

// 查询已算出的 G(k,p1,p2)
int get_g(int k, int p1, int p2) {
    if (k <= 0 || p1 == p2) return 0;
    const vector<int> &vec = layer[k];
    if (vec.empty()) return 0;
    int key = pack_pair(p1, p2);
    int lo = 0, hi = (int)vec.size() - 1;
    while (lo < hi) {
        int mid = (lo + hi) >> 1;
        if (vec[mid] < key) lo = mid + 1;
        else hi = mid;
    }
    return dp[k][lo];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n;
    cin >> (str + 1);
    for (int i = 1; i <= n; i++) c[i] = str[i] - '0';

    // ---------- 第一步：自上而下收集所有用到的 G 状态 ----------
    // A、X 两条链在每层各产生一个 G(k-1, ·, n) 查询
    int pa = n, px = n;
    for (int k = n; k >= 1; k--) {
        if (ch(pa) == 1) {
            layer[k - 1].push_back(pack_pair(pa - 1, n));
            pa = n;
        } else {
            pa = pa - 1;
        }
        if (ch(px) == 0) {
            layer[k - 1].push_back(pack_pair(px - 1, n));
            px = n;
        } else {
            px = px - 1;
        }
    }

    // 把每层状态沿递推式向下展开
    for (int k = n; k >= 1; k--) {
        sort(layer[k].begin(), layer[k].end());
        layer[k].erase(unique(layer[k].begin(), layer[k].end()), layer[k].end());
        const vector<int> cur = layer[k];
        for (int i = 0; i < (int)cur.size(); i++) {
            int p1 = key_first(cur[i]);
            int p2 = key_second(cur[i]);
            if (p1 == p2) continue;
            if (ch(p1) == ch(p2)) {
                layer[k - 1].push_back(pack_pair(p1 - 1, p2 - 1));
            } else {
                layer[k - 1].push_back(pack_pair(p1 - 1, n));
                layer[k - 1].push_back(pack_pair(n, p2 - 1));
            }
        }
    }
    sort(layer[0].begin(), layer[0].end());
    layer[0].erase(unique(layer[0].begin(), layer[0].end()), layer[0].end());

    // ---------- 第二步：自下而上按层计算 G ----------
    dp[0].assign(layer[0].size(), 0);
    for (int k = 1; k <= n; k++) {
        const vector<int> &cur = layer[k];
        dp[k].assign(cur.size(), 0);
        for (int i = 0; i < (int)cur.size(); i++) {
            int p1 = key_first(cur[i]);
            int p2 = key_second(cur[i]);
            if (p1 == p2) { dp[k][i] = 0; continue; }
            if (ch(p1) == ch(p2)) {
                dp[k][i] = get_g(k - 1, p1 - 1, p2 - 1);
            } else {
                ll v = get_g(k - 1, p1 - 1, n);
                v = (v + 1 + get_g(k - 1, n, p2 - 1)) % MOD;
                dp[k][i] = (int)v;
            }
        }
    }

    // ---------- 第三步：沿 A、X 两条链累加 ----------
    int sa = 0, sx = 0;
    pa = n; px = n;
    for (int k = n; k >= 1; k--) {
        if (ch(pa) == 0) {
            pa = pa - 1;                                     // A(k,p)=A(k-1,p-1)
        } else {
            sa = (sa + 1 + get_g(k - 1, pa - 1, n)) % MOD;   // A(k-1,n)+1+G
            pa = n;
        }
        if (ch(px) == 1) {
            px = px - 1;                                     // X(k,p)=X(k-1,p-1)
        } else {
            sx = (sx + (ll)get_g(k - 1, px - 1, n) + 1) % MOD;
            px = n;
        }
    }

    int ans = (sa + 1 + sx) % MOD;
    cout << ans << "\n";
    return 0;
}
