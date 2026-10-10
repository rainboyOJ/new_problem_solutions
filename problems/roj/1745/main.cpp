/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 21:03
 * update_at: 2026-10-07 21:03
 */
// 一本通 1745《分组》
// 小组合法性只由队长决定：队长的 r 是全组最大（可并列），且全组每个人的年龄都落在
// [a_队长 - K, a_队长 + K] 内。于是分两步解决：
//   1) 预处理 cnt[i] = 以 i 当队长时小组的最大人数；
//   2) 询问 (x, y) 的队长必须满足 r >= max(r_x, r_y) 且年龄同时靠近两人，
//      把询问按"r 阈值"降序离线，用下标为年龄坐标的最大值线段树回答区间最大值。
// 复杂度 O((n + Q) log n)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 200005;  // n 上限 1e5，按 2 倍安全系数开
const int MAXQ = 200005;  // 询问数上限 1e5，同样按 2 倍开

int n, Q;  // n = 居民数，Q = 询问数
ll K;      // 组内成员与队长的年龄差距上限

// 一个居民：地位 r、年龄 a、年龄离散化坐标 agePos、当队长时的最大组队人数 cnt
struct Person {
    ll r;
    ll a;
    int agePos;
    int cnt;
};
Person p[MAXN];  // 按 r 升序排序后的居民序列，下标从 1 开始

// 原始编号 -> (地位, 年龄)，离线处理询问时按编号查
struct Info {
    ll r;
    ll a;
};
Info info[MAXN];  // info[i] 就是第 i 号居民的原始数据

ll ageVal[MAXN];  // 年龄离散化后的取值表（升序去重），下标 1..m
int m;            // 年龄的种数

int fen[MAXN];    // 树状数组：统计年龄坐标落在某个区间内的已插入人数
int seg[4 * MAXN];// 最大值线段树：下标是年龄坐标，存 cnt 的最大值
int ans[MAXQ];    // 每个询问的答案，最后按原顺序输出

// 在 ageVal[1..m] 里找第一个 >= v 的坐标（不存在返回 m+1）
int lower_idx(ll v) {
    int lo = 1, hi = m, res = m + 1;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (ageVal[mid] >= v) {
            res = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return res;
}

// 在 ageVal[1..m] 里找最后一个 <= v 的坐标（不存在返回 0）
int upper_idx(ll v) {
    int lo = 1, hi = m, res = 0;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (ageVal[mid] <= v) {
            res = mid;
            lo = mid + 1;
        } else {
            hi = mid - 1;
        }
    }
    return res;
}

// 找第一个满足 p[i].r >= need 的排名（不存在返回 n+1）：
// 排名 >= 该值的人地位足够高，才有资格当队长
int first_rank(ll need) {
    int lo = 1, hi = n, res = n + 1;
    while (lo <= hi) {
        int mid = (lo + hi) >> 1;
        if (p[mid].r >= need) {
            res = mid;
            hi = mid - 1;
        } else {
            lo = mid + 1;
        }
    }
    return res;
}

// 树状数组单点加
void fen_add(int i, int v) {
    for (; i <= m; i += i & -i) fen[i] += v;
}

// 树状数组前缀和
int fen_sum(int i) {
    int s = 0;
    for (; i > 0; i -= i & -i) s += fen[i];
    return s;
}

// 线段树单点取最大值
void seg_update(int o, int l, int r, int pos, int val) {
    if (l == r) {
        if (val > seg[o]) seg[o] = val;
        return;
    }
    int mid = (l + r) >> 1;
    if (pos <= mid) {
        seg_update(o << 1, l, mid, pos, val);
    } else {
        seg_update(o << 1 | 1, mid + 1, r, pos, val);
    }
    seg[o] = max(seg[o << 1], seg[o << 1 | 1]);
}

// 线段树区间最大值查询，区间为空时返回 0
int seg_query(int o, int l, int r, int ql, int qr) {
    if (ql > r || qr < l) return 0;
    if (ql <= l && r <= qr) return seg[o];
    int mid = (l + r) >> 1;
    return max(seg_query(o << 1, l, mid, ql, qr), seg_query(o << 1 | 1, mid + 1, r, ql, qr));
}

// 居民按地位升序，便于用"排名 >= start"表达"地位不低于 need"
bool cmpPerson(const Person &x, const Person &y) {
    return x.r < y.r;
}

// 询问按队长最小排名降序，好让线段树里的元素只增不减
struct Query {
    int start;  // 队长最小排名
    int ql;     // 队长年龄区间左端（离散化坐标）
    int qr;     // 队长年龄区间右端（离散化坐标）
    int id;     // 原询问编号
};
Query qs[MAXQ];

bool cmpQuery(const Query &x, const Query &y) {
    return x.start > y.start;
}

int main() {
    if (scanf("%d%lld", &n, &K) != 2) return 0;
    for (int i = 1; i <= n; ++i) scanf("%lld", &p[i].r);
    for (int i = 1; i <= n; ++i) scanf("%lld", &p[i].a);
    for (int i = 1; i <= n; ++i) {
        info[i].r = p[i].r;
        info[i].a = p[i].a;
    }

    // 年龄离散化：值域 1e9 但只有 n 个不同取值
    sort(p + 1, p + n + 1, cmpPerson);
    for (int i = 1; i <= n; ++i) ageVal[i] = p[i].a;
    sort(ageVal + 1, ageVal + n + 1);
    m = 1;
    for (int i = 2; i <= n; ++i) {
        if (ageVal[i] != ageVal[m]) ageVal[++m] = ageVal[i];
    }
    for (int i = 1; i <= n; ++i) p[i].agePos = lower_idx(p[i].a);

    // 预处理 cnt[i]：先按 r 分块，同 r 的人整块插入后再统一查询，
    // 这样 r 并列的人也能互相计入（并列第一同样可以当队长）
    for (int i = 1; i <= n;) {
        int j = i;
        while (j <= n && p[j].r == p[i].r) {
            fen_add(p[j].agePos, 1);
            ++j;
        }
        for (int t = i; t < j; ++t) {
            int lo = lower_idx(p[t].a - K);
            int hi = upper_idx(p[t].a + K);
            p[t].cnt = (lo > hi) ? 0 : fen_sum(hi) - fen_sum(lo - 1);
        }
        i = j;
    }

    scanf("%d", &Q);
    for (int i = 1; i <= Q; ++i) {
        int x, y;
        scanf("%d%d", &x, &y);
        // 队长的年龄必须同时满足 |a_队长 - a_x| <= K 和 |a_队长 - a_y| <= K，
        // 两个区间的交集就是下面这段
        qs[i].start = first_rank(max(info[x].r, info[y].r));
        qs[i].ql = lower_idx(max(info[x].a, info[y].a) - K);
        qs[i].qr = upper_idx(min(info[x].a, info[y].a) + K);
        qs[i].id = i;
    }

    sort(qs + 1, qs + Q + 1, cmpQuery);
    int k = n;  // 排名 (k, n] 的人已经进入线段树
    for (int i = 1; i <= Q; ++i) {
        while (k >= qs[i].start) {
            seg_update(1, 1, m, p[k].agePos, p[k].cnt);
            --k;
        }
        int lo = max(qs[i].ql, 1);
        int hi = min(qs[i].qr, m);
        int best = (lo <= hi) ? seg_query(1, 1, m, lo, hi) : 0;
        // x、y 自己一定被合法队长计入，所以小于 2 就是无解
        ans[qs[i].id] = (best < 2) ? -1 : best;
    }

    for (int i = 1; i <= Q; ++i) printf("%d\n", ans[i]);
    return 0;
}
