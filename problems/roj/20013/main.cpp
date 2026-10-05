// main.cpp：区间 DP 求最小生气总量（对应 main.py 的 Python 解法的 C++ 版本）
// 状态 (l, r, end)：已送完排序后连续区间 [l, r]，无人机停在左/右端点。
// 每次向外扩展一位，代价 = 扩展前未送客户 d 之和 × 飞行距离 / v。

/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:12
 * update_at: 2026-10-06 02:12
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long ll;

const int MAXN = 1005;
const ll INF = (ll)4e18;

ll n, v, sx;              // 客户数、无人机速度、起始位置
ll x[MAXN];               // 排序后各点的位置（含虚拟起点）
ll dd[MAXN];              // 排序后各点的 d 值（虚拟起点为 0）
ll pref[MAXN];            // pref[i] = 前 i 个点的 d 之和
ll si;                    // 虚拟起点在排序数组中的下标
ll f[MAXN][2];            // f[l][0/1]：当前层，区间 [l, l+w] 送完、停在左/右端点的最小整数分子
ll g[MAXN][2];            // 上一层（区间宽度 w-1）的 DP 值

int main() {
    scanf("%lld %lld %lld", &n, &v, &sx);
    ll sum_a = 0; // A 部分与路线无关，直接累加
    for (ll i = 1; i <= n; i++) {
        ll p, a, d;
        scanf("%lld %lld %lld", &p, &a, &d);
        x[i] = p;
        dd[i] = d;
        sum_a += a;
    }
    // 把起点当作 d=A=0 的虚拟客户（下标 0），一起按位置排序
    x[0] = sx;
    dd[0] = 0;
    ll m = n + 1; // 总点数（含虚拟起点）
    // 点数 <=1001，用插入排序按位置排好，避免与 DP 下标耦合
    for (ll i = 1; i < m; i++) { // 插入排序
        ll px = x[i], dv = dd[i];
        ll j = i - 1;
        while (j >= 0 && x[j] > px) {
            x[j + 1] = x[j];
            dd[j + 1] = dd[j];
            j--;
        }
        x[j + 1] = px;
        dd[j + 1] = dv;
    }
    // 找虚拟起点下标：最后一个位置 <= s 的点（s 为其中一点）
    si = 0;
    for (ll i = 0; i < m; i++)
        if (x[i] == sx) si = i;

    pref[0] = 0;
    for (ll i = 0; i < m; i++)
        pref[i + 1] = pref[i] + dd[i];
    ll total_d = pref[m]; // 全部客户的 d 之和

    // 滚动数组：g 是宽度 w-1 层，f 是宽度 w 层
    for (ll l = 0; l < m; l++) {
        g[l][0] = INF;
        g[l][1] = INF;
    }
    g[si][0] = 0; // 初始区间 [si, si]，无人机还没动，代价 0
    g[si][1] = 0;

    for (ll w = 1; w < m; w++) {
        ll lo = std::max(0LL, si - w);
        ll hi = std::min(si, m - 1 - w); // 区间 [l, l+w] 必须包含起点 si
        for (ll l = 0; l < m; l++) {
            f[l][0] = INF;
            f[l][1] = INF;
        }
        for (ll l = lo; l <= hi; l++) {
            ll r = l + w;
            // 向左扩展送第 l 个客户：先飞 x[端点] -> x[l]，飞行期间所有未送客户 d 同时增长
            if (l < si) {
                ll seg = total_d - (pref[r + 1] - pref[l + 1]); // 扩展前未送客户的 d 和
                ll c1 = (g[l + 1][0] >= INF) ? INF : g[l + 1][0] + seg * (x[l + 1] - x[l]); // 原停左端
                ll c2 = (g[l + 1][1] >= INF) ? INF : g[l + 1][1] + seg * (x[r] - x[l]);     // 原停右端，横穿区间
                f[l][0] = std::min(c1, c2);
            }
            // 向右扩展送第 r 个客户
            if (r > si) {
                ll seg = total_d - (pref[r] - pref[l]); // 扩展前未送客户的 d 和
                ll c1 = (g[l][0] >= INF) ? INF : g[l][0] + seg * (x[r] - x[l]); // 原停左端，横穿区间
                ll c2 = (g[l][1] >= INF) ? INF : g[l][1] + seg * (x[r] - x[r - 1]); // 原停右端
                f[l][1] = std::min(c1, c2);
            }
        }
        std::swap(f, g); // 滚动：当前层变为下一轮的上一层
    }

    // 全部送完 = 区间 [0, m-1]；分子 ÷ v 后向下取整，再加常数 A
    printf("%lld\n", sum_a + std::min(g[0][0], g[0][1]) / v);
    return 0;
}
