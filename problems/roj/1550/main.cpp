/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 07:39
 * update_at: 2026-10-05 07:39
 */
#include <cstdio>
#include <cmath>
#include <algorithm>
using namespace std;

typedef long long ll;

// 题目数据规模：n <= 1e5，线段树开 4n 个节点
const int MAXN = 100005;
const int MAXNODE = MAXN << 2;

int n, m;
ll delta[MAXN]; // delta[i] = 第 i 个国家的初始喜欢度

// 线段树每个节点维护三元组 [区间和, 区间最大值, 区间最小值]
ll tsum[MAXNODE];
ll tmax[MAXNODE];
ll tmin[MAXNODE];

// 建树：叶子存单个国家的喜欢度，父节点由两个孩子合并
void build(int node, int lo, int hi) {
    if (lo == hi) {
        tsum[node] = tmax[node] = tmin[node] = delta[lo];
        return;
    }
    int mid = (lo + hi) >> 1;
    build(node << 1, lo, mid);
    build(node << 1 | 1, mid + 1, hi);
    // 用孩子刷新父节点三元组
    tsum[node] = tsum[node << 1] + tsum[node << 1 | 1];
    tmax[node] = max(tmax[node << 1], tmax[node << 1 | 1]);
    tmin[node] = min(tmin[node << 1], tmin[node << 1 | 1]);
}

// 把"整段同值"的状态下推给两个孩子，恢复孩子与父亲的一致。
// 整段开方可能只改写了内部节点，孩子还是开方前的旧值；要下探时必须先补齐。
void push_equal(int node, int lo, int hi) {
    ll v = tmax[node];
    int mid = (lo + hi) >> 1;
    tsum[node << 1] = v * (mid - lo + 1);
    tmax[node << 1] = tmin[node << 1] = v;
    tsum[node << 1 | 1] = v * (hi - mid);
    tmax[node << 1 | 1] = tmin[node << 1 | 1] = v;
}

// 区间 [ql, qr] 每个值开方取整：
// 无交、或 max <= 1 时整棵子树跳过（0/1 开方不变）；
// 整段同值且全盖住时一次改完，否则先下推同值再递归。
void apply_sqrt(int node, int lo, int hi, int ql, int qr) {
    if (hi < ql || lo > qr || tmax[node] <= 1) return;
    if (tmax[node] == tmin[node]) {
        if (ql <= lo && hi <= qr) { // 全盖住：整段同值 v，一次改写为 sqrt(v)
            ll v = (ll)sqrt((double)tmax[node]);
            tsum[node] = v * (hi - lo + 1);
            tmax[node] = tmin[node] = v;
            return;
        }
        push_equal(node, lo, hi); // 部分覆盖：先同步孩子再下探
    }
    int mid = (lo + hi) >> 1;
    if (ql <= mid) apply_sqrt(node << 1, lo, mid, ql, qr);
    if (qr > mid) apply_sqrt(node << 1 | 1, mid + 1, hi, ql, qr);
    // 回溯时用孩子刷新父节点三元组
    tsum[node] = tsum[node << 1] + tsum[node << 1 | 1];
    tmax[node] = max(tmax[node << 1], tmax[node << 1 | 1]);
    tmin[node] = min(tmin[node << 1], tmin[node << 1 | 1]);
}

// 区间 [ql, qr] 求和：完全落入取区间和；同值段按重叠长度直接算，否则递归两侧
ll query(int node, int lo, int hi, int ql, int qr) {
    if (ql <= lo && hi <= qr) return tsum[node];
    if (tmax[node] == tmin[node]) {
        // 部分重叠的同值段：孩子可能没同步，不能下探，直接按重叠长度算
        int overlap = min(hi, qr) - max(lo, ql) + 1;
        return tmax[node] * overlap;
    }
    int mid = (lo + hi) >> 1;
    ll total = 0;
    if (ql <= mid) total = query(node << 1, lo, mid, ql, qr);
    if (qr > mid) total += query(node << 1 | 1, mid + 1, hi, ql, qr);
    return total;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) scanf("%lld", &delta[i]);
    build(1, 1, n);

    scanf("%d", &m);
    for (int i = 1; i <= m; i++) {
        int x, l, r;
        scanf("%d %d %d", &x, &l, &r);
        if (x == 1) {
            // 询问 l..r 的开心值总和
            printf("%lld\n", query(1, 1, n, l, r));
        } else {
            // l..r 每个国家的喜欢度开方取整
            apply_sqrt(1, 1, n, l, r);
        }
    }
    return 0;
}
