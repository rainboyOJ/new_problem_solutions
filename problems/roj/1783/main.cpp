/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 02:22
 * update_at: 2026-10-08 02:22
 */
// main.cpp：矩阵填数。每个格子填 1..m，n 个子矩形要求「内部最大值恰好等于 v」。
// 做法：先用容斥把每个子集的交集 / 并集面积算出来，再按 v 从小到大分层，
// 对每一层做「每个矩形都至少有一个格子取到 v」的子集容斥，各层答案相乘。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MOD = 1000000007LL; // 题面要求的取模数
const int MAXN = 10;         // n ≤ 10，掩码规模固定
const int MAXMASK = 1 << MAXN;

struct Rect {
    ll x1, y1, x2, y2, v; // 左上角、右下角、以及"最大值恰好为 v"
};

Rect rects[MAXN];       // 所有限制子矩形，按 v 升序排序后使用
ll inter_area[MAXMASK]; // inter_area[mask]：mask 里所有子矩形的交集面积
ll union_area[MAXMASK]; // union_area[mask]：mask 里所有子矩形的并集面积
int popcnt_arr[MAXMASK]; // 掩码的 1 的个数

ll h, w;  // 矩阵大小
int m, n; // 值的上界、限制条数

// 快速幂：0^0 约定为 1（容斥里 (v-1)^0 需要它），指数最大 h*w ≤ 1e8
ll power(ll base, ll exp) {
    ll res = 1;
    base %= MOD;
    if (base < 0) base += MOD;
    while (exp > 0) {
        if (exp & 1) res = res * base % MOD;
        base = base * base % MOD;
        exp >>= 1;
    }
    return res;
}

// 按 v 升序排，让"更小的层"一定排在前面
bool cmp_by_v(const Rect &a, const Rect &b) {
    return a.v < b.v;
}

// 枚举 mask 里所有子矩形的交集面积（空交集算 0）
ll intersect_area(int mask) {
    ll x1 = 1, y1 = 1, x2 = h, y2 = w;
    for (int i = 0; i < n; i++) {
        if (!((mask >> i) & 1)) continue;
        x1 = max(x1, rects[i].x1);
        y1 = max(y1, rects[i].y1);
        x2 = min(x2, rects[i].x2);
        y2 = min(y2, rects[i].y2);
        if (x1 > x2 || y1 > y2) return 0;
    }
    return (x2 - x1 + 1) * (y2 - y1 + 1);
}

void solve() {
    cin >> h >> w >> m >> n;
    for (int i = 0; i < n; i++)
        cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2 >> rects[i].v;
    sort(rects, rects + n, cmp_by_v);

    int full = (1 << n) - 1;

    // 交集面积：直接对每个子集取边界交
    for (int mask = 1; mask <= full; mask++) inter_area[mask] = intersect_area(mask);

    // 并集面积：容斥 Σ(-1)^(|sub|+1) |∩_{j∈sub} S_j|
    union_area[0] = 0;
    for (int mask = 1; mask <= full; mask++) {
        ll sum = 0;
        for (int sub = mask; sub > 0; sub = (sub - 1) & mask) {
            if (popcnt_arr[sub] & 1) sum += inter_area[sub];
            else                     sum -= inter_area[sub];
        }
        union_area[mask] = sum;
    }

    // 未被任何限制覆盖的格子：上界为 m，可任取 1..m
    ll ans = power(m, h * w - union_area[full]);

    int lower = 0; // 已经处理过的、v 更小的那些限制的掩码
    for (int i = 0; i < n; ) {
        int j = i, same = 0; // same：本层（v 相同）的限制掩码
        while (j < n && rects[j].v == rects[i].v) {
            same |= 1 << j;
            j++;
        }
        ll v = rects[i].v;

        // 本层的格子 A_v =「被本层矩形覆盖」减去「被更小 v 覆盖」，
        // 这些格子上界恰好是 v，是唯一可能取到 v 的格子。
        ll layer = union_area[same | lower] - union_area[lower];
        ll layer_ways = power(v, layer); // 容斥里 T = 空集的那一项

        // 子集容斥：T 里的矩形被强制"没有格子取到 v"，即 T 覆盖到的格子只能填 1..v-1
        for (int t = same; t > 0; t = (t - 1) & same) {
            ll forced = union_area[t | lower] - union_area[lower];
            ll one = power(v - 1, forced) * power(v, layer - forced) % MOD;
            if (popcnt_arr[t] & 1) layer_ways = (layer_ways - one + MOD) % MOD;
            else                   layer_ways = (layer_ways + one) % MOD;
        }

        ans = ans * layer_ways % MOD;
        if (ans == 0) break; // 这一层已经无法满足，后面再乘也还是 0
        lower |= same;
        i = j;
    }

    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    for (int i = 1; i < MAXMASK; i++) popcnt_arr[i] = popcnt_arr[i >> 1] + (i & 1);

    int T;
    cin >> T;
    while (T--) solve();

    return 0;
}
