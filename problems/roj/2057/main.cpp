/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 10:12
 * update_at: 2026-10-06 10:12
 */
// 闭合栅栏：先判简单多边形，再对每条栅栏用"观察者视线切分 + 段中点跨立"判定可见性
#include <bits/stdc++.h>
typedef long long ll;

const int MAXN = 205;

ll px[MAXN], py[MAXN]; // px[i], py[i]：第 i 个顶点坐标（下标 0..n-1）
ll n, ox, oy;          // n：顶点数，(ox, oy)：观察者位置
ll sn[MAXN], sx[MAXN], sy[MAXN], sc[MAXN]; // 待输出栅栏的端点序号与坐标

// oa × ob：>0 左转，<0 右转，=0 三点共线
ll cross(ll oax, ll oay, ll bax, ll bay) {
    return oax * bay - oay * bax;
}

// 最大公约数：把分数约到最简，避免中间量溢出 long long
ll gcd_ll(ll a, ll b) {
    while (b != 0) { ll t = a % b; a = b; b = t; }
    return a < 0 ? -a : a;
}

// 已知三点共线时，q 是否落在线段 ab 上（含端点）
bool on_seg(ll qx, ll qy, ll ax, ll ay, ll bx, ll by) {
    return std::min(ax, bx) <= qx && qx <= std::max(ax, bx)
        && std::min(ay, by) <= qy && qy <= std::max(ay, by);
}

// 两条线段是否有公共点：严格跨立，或端点落在对方线段上（含共线重叠）
bool touches(ll p1x, ll p1y, ll p2x, ll p2y,
             ll q1x, ll q1y, ll q2x, ll q2y) {
    ll d1 = cross(p2x - p1x, p2y - p1y, q1x - p1x, q1y - p1y);
    ll d2 = cross(p2x - p1x, p2y - p1y, q2x - p1x, q2y - p1y);
    ll d3 = cross(q2x - q1x, q2y - q1y, p1x - q1x, p1y - q1y);
    ll d4 = cross(q2x - q1x, q2y - q1y, p2x - q1x, p2y - q1y);
    if (d1 * d2 < 0 && d3 * d4 < 0) return true;
    return (d1 == 0 && on_seg(q1x, q1y, p1x, p1y, p2x, p2y))
        || (d2 == 0 && on_seg(q2x, q2y, p1x, p1y, p2x, p2y))
        || (d3 == 0 && on_seg(p1x, p1y, q1x, q1y, q2x, q2y))
        || (d4 == 0 && on_seg(p2x, p2y, q1x, q1y, q2x, q2y));
}

// 相邻栅栏 i、k 是否"共线且在公共顶点之外还互相覆盖"（这种情况不合法）
bool adjacent_overlap(ll i, ll k) {
    if (k == i + 1) {           // 顺序相邻：公共顶点是 i+1，两边的另一端是 i 和 k+1
        ll shared = i + 1;
        ll pa = i, pb = (k + 1) % n;
        ll cx = cross(px[pa] - px[shared], py[pa] - py[shared],
                      px[pb] - px[shared], py[pb] - py[shared]);
        if (cx != 0) return false;
        return on_seg(px[pb], py[pb], px[shared], py[shared], px[pa], py[pa])
            || on_seg(px[pa], py[pa], px[shared], py[shared], px[pb], py[pb]);
    }
    // 闭合相邻（i=0, k=n-1）：公共顶点是 0，两边的另一端是 1 和 k
    ll shared = 0;
    ll pa = 1, pb = k;
    ll cx = cross(px[pa] - px[shared], py[pa] - py[shared],
                  px[pb] - px[shared], py[pb] - py[shared]);
    if (cx != 0) return false;
    return on_seg(px[pb], py[pb], px[shared], py[shared], px[pa], py[pa])
        || on_seg(px[pa], py[pa], px[shared], py[shared], px[pb], py[pb]);
}

// 检查 n 条栅栏是否构成合法闭合栅栏：任意两条除公共顶点外无其他交点
bool is_simple() {
    for (ll i = 0; i < n; i++) {
        ll j = (i + 1) % n;
        for (ll k = i + 1; k < n; k++) {
            ll l = (k + 1) % n;
            bool adjacent = (k == i + 1) || (i == 0 && k == n - 1);
            if (!adjacent) {
                if (touches(px[i], py[i], px[j], py[j],
                            px[k], py[k], px[l], py[l])) return false;
            } else {
                // 相邻栅栏天然交于公共顶点，只额外检查是否共线重叠
                if (adjacent_overlap(i, k)) return false; // k 是相邻边的编号
            }
        }
    }
    return true;
}

// 栅栏 i（顶点 i → (i+1)%n）是否可被观察者看到：段上存在一个不被遮挡的点
bool visible(ll i) {
    ll j = (i + 1) % n;
    ll ax = px[i], ay = py[i], bx = px[j], by = py[j];
    if (cross(bx - ax, by - ay, ox - ax, oy - ay) == 0) return false;
    ll ux = bx - ax, uy = by - ay; // 栅栏方向向量

    // 分段断点：参数 t ∈ [0,1]，0/1 是端点，其余是观察者到各顶点的视线与 AB 的交点
    ll cut_t[2 * MAXN], cut_a[MAXN], cut_b[MAXN]; // 交点表示成 num/den，数对存下
    ll m = 0;
    cut_t[m++] = 0; cut_a[m - 1] = 0; cut_b[m - 1] = 1;
    cut_t[m++] = 1; cut_a[m - 1] = 1; cut_b[m - 1] = 1;
    for (ll k = 0; k < n; k++) {
        ll ex = px[k] - ox, ey = py[k] - oy;
        ll den = ex * uy - ey * ux;               // 交点参数分母，=0 即视线与 AB 平行
        if (den == 0) continue;
        ll num = ey * (ax - ox) - ex * (ay - oy); // 分子 -cross(e, A-obs)
        if (den < 0) { num = -num; den = -den; }
        if (num > 0 && num < den) {               // 交点确实落在线段 AB 内部
            ll g = gcd_ll(num, den);              // 约分，防止后续放大时溢出
            cut_t[m] = num / g; cut_a[m] = num / g; cut_b[m] = den / g;
            m++;
        }
    }
    // 按 t 值（分数）从小到大排序断点：冒泡即可，m ≤ 2n
    for (ll p = 0; p < m - 1; p++)
        for (ll q = 0; q + 1 < m - p; q++)
            if (cut_a[q] * cut_b[q + 1] > cut_a[q + 1] * cut_b[q]) {
                std::swap(cut_t[q], cut_t[q + 1]);
                std::swap(cut_a[q], cut_a[q + 1]);
                std::swap(cut_b[q], cut_b[q + 1]);
            }

    // 其余栅栏的跨立判据预计算：相对观察者的端点位移、方向 c、观察者所在侧
    ll r1x[MAXN], r1y[MAXN], r2x[MAXN], r2y[MAXN], ccx[MAXN], ccy[MAXN], cside[MAXN];
    ll cnt = 0;
    for (ll k = 0; k < n; k++) {
        if (k == i) continue;
        ll q1x = px[k], q1y = py[k], q2x = px[(k + 1) % n], q2y = py[(k + 1) % n];
        r1x[cnt] = q1x - ox; r1y[cnt] = q1y - oy;
        r2x[cnt] = q2x - ox; r2y[cnt] = q2y - oy;
        ccx[cnt] = q2x - q1x; ccy[cnt] = q2y - q1y;
        cside[cnt] = ccx[cnt] * (oy - q1y) - ccy[cnt] * (ox - q1x); // cross(c, obs-q1)
        cnt++;
    }

    // 相邻开段取中点测试：段内每一点可见性完全相同
    for (ll p = 0; p + 1 < m; p++) {
        // 中点分数 (p1n + p2n)/(2·b1·b2)：等价于 (lo+hi)/2 化成同一分母
        ll p1n = cut_a[p] * cut_b[p + 1], p2n = cut_a[p + 1] * cut_b[p];
        ll dden = 2 * cut_b[p] * cut_b[p + 1];
        ll g = gcd_ll(p1n + p2n, dden);           // 中点同样约分
        ll mn = (p1n + p2n) / g, md = dden / g;
        // 中点方向向量 (P-obs)·md：P = A + t·U，全程整数运算不丢精度
        ll vx = (ax - ox) * md + mn * ux;
        ll vy = (ay - oy) * md + mn * uy;
        bool blocked = false;
        for (ll k = 0; k < cnt; k++) {
            ll t1 = vx * r1y[k] - vy * r1x[k]; // cross(P-obs, q1-obs)
            ll t2 = vx * r2y[k] - vy * r2x[k]; // cross(P-obs, q2-obs)
            if (t1 == 0 || t2 == 0) continue;  // 擦过端点不算穿过
            if ((t1 < 0) == (t2 < 0)) continue; // 观察者方向两端不在对方直线两侧
            // cross(c, P-q1) 的符号 = cross(c, P-obs) + md·side 的符号
            ll u = ccx[k] * vy - ccy[k] * vx + md * cside[k];
            if (cside[k] != 0 && u != 0 && (cside[k] < 0) != (u < 0)) {
                blocked = true; // 视线严格穿过该栅栏，被它挡住
                break;
            }
        }
        if (!blocked) return true; // 存在不被遮挡的中点，栅栏可见
    }
    return false;
}

int main() {
    std::cin >> n >> ox >> oy;
    for (ll i = 0; i < n; i++) std::cin >> px[i] >> py[i];

    if (!is_simple()) {
        std::cout << "NOFENCE" << std::endl;
        return 0;
    }

    // 收集所有可见栅栏：边 i 连接顶点 i 与 (i+1)%n
    ll total = 0;
    for (ll i = 0; i < n; i++) {
        if (!visible(i)) continue;
        ll j = (i + 1) % n;
        ll first, last; // "最后一个点"= 输入序号大者
        if (i < j) { first = i; last = j; }
        else       { first = j; last = i; }
        sn[total] = first; sx[total] = px[first]; sy[total] = py[first];
        sc[total] = last;  // 只再存 last 的下标，坐标输出时再取
        total++;
    }
    // 按"最后一个点"的输入序号排序，相同时按"第一个点"排序
    for (ll p = 0; p < total - 1; p++)
        for (ll q = 0; q + 1 < total - p; q++) {
            bool need = sc[q] > sc[q + 1]
                || (sc[q] == sc[q + 1] && sn[q] > sn[q + 1]);
            if (need) {
                std::swap(sn[q], sn[q + 1]);
                std::swap(sx[q], sx[q + 1]);
                std::swap(sy[q], sy[q + 1]);
                std::swap(sc[q], sc[q + 1]);
            }
        }
    std::cout << total << "\n";
    for (ll k = 0; k < total; k++) {
        std::cout << sx[k] << " " << sy[k] << " "
                  << px[sc[k]] << " " << py[sc[k]] << "\n";
    }
    return 0;
}
