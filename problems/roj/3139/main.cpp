/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 油田（Oil Deposits，恰好 k 格）：按行 DP + 四种单调转移的区域最大值 + 回溯方案。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

const ll NEG = -1000000000LL; // 「不可行」哨兵

ll n, m, k;
std::vector<std::vector<ll> > pre; // 行前缀和

// (目标状态层, 可用的上一层状态层, rect_max 的区域种类)
// 状态层 s = fl*2+fr：fl=1 左端点已过谷，fr=1 右端点已过峰
const int COMBOS_DST[4] = {0, 2, 1, 3};
const int COMBOS_KIND[4] = {0, 1, 2, 3};
const int SRC_A[4] = {0, 0, 0, 0};
const int SRC_B[4] = {0, 2, 1, 1};
const int SRC_C[4] = {0, 0, 0, 2};
const int SRC_D[4] = {0, 0, 0, 3};

// 对上一层权值表做区域最大值查询，结果表下标 [l][r]
std::vector<ll> rect_max(std::vector<ll>& a, ll kind) {
    ll mm = m;
    std::vector<ll> res(mm * mm, NEG);
    if (kind == 3) { // 行内右后缀 max（q ≥ r）+ 列向前缀 max（p ≤ l）
        std::vector<ll> t2 = a;
        for (ll p = 0; p < mm; p++) {
            ll b = p * mm, cur = NEG;
            for (ll q = mm - 1; q >= 0; q--) {
                if (t2[b + q] > cur) cur = t2[b + q];
                t2[b + q] = cur;
            }
        }
        for (ll p = 1; p < mm; p++) {
            for (ll q = 0; q < mm; q++) {
                ll u = t2[(p - 1) * mm + q];
                if (u > t2[p * mm + q]) t2[p * mm + q] = u;
            }
        }
        return t2;
    }
    if (kind == 1) { // 先列向并（p ≤ l），再行内从 q=l 起右扫（q ∈ [l, r]）
        std::vector<ll> e = a;
        for (ll p = 1; p < mm; p++) {
            for (ll q = 0; q < mm; q++) {
                ll u = e[(p - 1) * mm + q];
                if (u > e[p * mm + q]) e[p * mm + q] = u;
            }
        }
        for (ll l = 0; l < mm; l++) {
            ll b = l * mm, cur = NEG;
            for (ll q = l; q < mm; q++) {
                if (e[b + q] > cur) cur = e[b + q];
                res[b + q] = cur;
            }
        }
        return res;
    }
    if (kind == 2) { // 先行内右后缀（q ≥ r），再列内从 p=r 往上扫（p ∈ [l, r]）
        std::vector<ll> g = a;
        for (ll p = 0; p < mm; p++) {
            ll b = p * mm, cur = NEG;
            for (ll q = mm - 1; q >= 0; q--) {
                if (g[b + q] > cur) cur = g[b + q];
                g[b + q] = cur;
            }
        }
        for (ll r = 0; r < mm; r++) {
            ll cur = NEG;
            for (ll p = r; p >= 0; p--) {
                if (g[p * mm + r] > cur) cur = g[p * mm + r];
                res[p * mm + r] = cur;
            }
        }
        return res;
    }
    // kind 0：方形 [l, r]×[l, r]，行 max + 列 max 后按边长递推
    std::vector<ll> rp = a;
    for (ll p = 0; p < mm; p++) {
        ll b = p * mm;
        for (ll q = 1; q < mm; q++) {
            if (rp[b + q - 1] > rp[b + q]) rp[b + q] = rp[b + q - 1];
        }
    }
    std::vector<ll> cp(mm * mm, NEG);
    for (ll l = 0; l < mm; l++) {
        ll cur = NEG;
        for (ll p = l; p < mm; p++) {
            if (a[p * mm + l] > cur) cur = a[p * mm + l];
            cp[p * mm + l] = cur;
        }
    }
    for (ll d = 0; d < mm; d++) { // d = r - l，小边长先算
        for (ll l = 0; l + d < mm; l++) {
            ll r = l + d;
            ll v = rp[l * mm + r];
            if (cp[r * mm + l] > v) v = cp[r * mm + l];
            if (d) {
                ll u = res[(l + 1) * mm + r];
                if (u > v) v = u;
            }
            res[l * mm + r] = v;
        }
    }
    return res;
}

struct Pick {
    ll row, l, r;
};

int main() {
    if (scanf("%lld %lld %lld", &n, &m, &k) != 3) return 0; // 空输入安全返回
    std::vector<std::vector<ll> > w(n, std::vector<ll>(m, 0));
    for (ll i = 0; i < n; i++) {
        for (ll j = 0; j < m; j++) {
            scanf("%lld", &w[i][j]);
        }
    }

    if (k == 0) { // 空连通块
        printf("Oil : 0\n");
        return 0;
    }

    pre.assign(n, std::vector<ll>(m + 1, 0));
    for (ll i = 0; i < n; i++) {
        for (ll c = 0; c < m; c++) {
            pre[i][c + 1] = pre[i][c] + w[i][c];
        }
    }

    ll W = m * m;
    ll k1 = k + 1;
    std::vector<ll> slots, sizes;
    for (ll l = 0; l < m; l++) {
        for (ll r = l; r < m; r++) {
            slots.push_back(l * m + r);
            sizes.push_back(r - l + 1);
        }
    }
    ll S = (ll)slots.size();

    // 四层 DP 表，下标 [s][j*W + slot]
    std::vector<std::vector<ll> > F(4, std::vector<ll>(k1 * W, NEG));
    // 每行结束后冻结一张表，供最后回溯方案
    std::vector<ll> hist((size_t)n * 4 * k1 * W, 0);
    ll best = NEG;
    ll best_row = 0, best_state = 0, best_slot = 0;

    std::vector<ll> A(W, 0), R;
    std::vector<ll> seg_row(S, 0);

    for (ll i = 0; i < n; i++) {
        std::vector<std::vector<ll> > newF(4, std::vector<ll>(k1 * W, NEG));
        for (ll t = 0; t < S; t++) {
            ll l = slots[t] / m, r = slots[t] % m;
            seg_row[t] = pre[i][r + 1] - pre[i][l];
        }
        ll jtop = i * m;
        if (jtop > k - 1) jtop = k - 1;

        for (ll ci = 0; ci < 4; ci++) {
            ll dst_s = COMBOS_DST[ci], kind = COMBOS_KIND[ci];
            std::vector<ll> dst = newF[dst_s];
            for (ll jp = 1; jp <= jtop; jp++) {
                ll base = jp * W;
                for (ll t = 0; t < W; t++) A[t] = F[SRC_A[ci]][base + t];
                if (ci == 1) { // (1,0) ← (0,0)/(1,0)
                    for (ll t = 0; t < W; t++) {
                        ll x = F[SRC_B[ci]][base + t];
                        if (x > A[t]) A[t] = x;
                    }
                } else if (ci == 2) { // (0,1) ← (0,0)/(0,1)
                    for (ll t = 0; t < W; t++) {
                        ll x = F[SRC_B[ci]][base + t];
                        if (x > A[t]) A[t] = x;
                    }
                } else if (ci == 3) { // (1,1) ← 任意
                    for (ll s = 1; s < 4; s++) {
                        for (ll t = 0; t < W; t++) {
                            ll x = F[s][base + t];
                            if (x > A[t]) A[t] = x;
                        }
                    }
                }
                ll mx = A[0];
                for (ll t = 1; t < W; t++) {
                    if (A[t] > mx) mx = A[t];
                }
                if (mx <= NEG / 2) continue; // 该层源状态全不可达
                R = rect_max(A, kind);
                for (ll t = 0; t < S; t++) {
                    ll jn = jp + sizes[t];
                    if (jn > k) continue;
                    ll v = R[slots[t]] + seg_row[t];
                    if (v <= NEG / 2) continue;
                    if (v > newF[dst_s][jn * W + slots[t]]) {
                        newF[dst_s][jn * W + slots[t]] = v;
                    }
                }
            }
        }
        // 本行作为连通块首行：单调状态回到 (0,0)
        for (ll t = 0; t < S; t++) {
            if (sizes[t] <= k) {
                ll slot = sizes[t] * W + slots[t];
                if (seg_row[t] > newF[0][slot]) newF[0][slot] = seg_row[t];
            }
        }
        // 连通块可以在任意一行结束：记录恰 k 格的历史最优
        ll base_k = k * W;
        for (ll s = 0; s < 4; s++) {
            for (ll t = 0; t < S; t++) {
                ll v = newF[s][base_k + slots[t]];
                if (v > best) {
                    best = v;
                    best_row = i;
                    best_state = s;
                    best_slot = slots[t];
                }
            }
        }
        for (ll s = 0; s < 4; s++) {
            for (ll t = 0; t < k1 * W; t++) {
                hist[((size_t)i * 4 + s) * k1 * W + t] = newF[s][t];
            }
        }
        F.swap(newF);
    }

    std::vector<Pick> picked;
    ll end_row = best_row, s = best_state, slot = best_slot;
    ll l = slot / m, r = slot % m;
    ll j = k;
    while (true) {
        Pick pk;
        pk.row = end_row;
        pk.l = l;
        pk.r = r;
        picked.push_back(pk);
        ll sz = r - l + 1;
        ll jp = j - sz;
        ll fl = s >> 1, fr = s & 1;
        ll want = hist[((size_t)end_row * 4 + s) * k1 * W + j * W + slot]
                  - (pre[end_row][r + 1] - pre[end_row][l]);
        bool found = false;
        ll ns = 0, nl = 0, nr = 0;
        if (end_row > 0) {
            for (ll s0 = 0; s0 < 4; s0++) {
                if ((s0 >> 1) > fl || (s0 & 1) > fr) continue; // 拐过的弯不能回退
                for (ll p = m - 1; p >= 0; p--) {
                    if (fl == 0 && p < l) continue;
                    if (fl == 1 && p > l) continue;
                    for (ll q = m - 1; q >= 0; q--) {
                        if (fr == 0 && q > r) continue;
                        if (fr == 1 && q < r) continue;
                        if (q < l || p > r || p > q) continue;
                        ll hv = hist[((size_t)(end_row - 1) * 4 + s0) * k1 * W + jp * W + p * m + q];
                        if (hv == want) {
                            found = true;
                            ns = s0;
                            nl = p;
                            nr = q;
                            break;
                        }
                    }
                    // 与 Python 的 `if nxt: break` 一致：可能由更早的 s0 置位
                    if (found) break;
                }
            }
        }
        if (!found) break; // 没有前驱行：本行即连通块首行
        s = ns;
        l = nl;
        r = nr;
        slot = l * m + r;
        j = jp;
        end_row = end_row - 1;
    }

    std::reverse(picked.begin(), picked.end());
    printf("Oil : %lld\n", best);
    for (size_t t = 0; t < picked.size(); t++) {
        for (ll c = picked[t].l; c <= picked[t].r; c++) {
            printf("%lld %lld\n", picked[t].row + 1, c + 1);
        }
    }
    return 0;
}
