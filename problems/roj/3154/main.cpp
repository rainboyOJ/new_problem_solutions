/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 开车旅行：海拔有序链表确定「最近 / 次近」，再倍增求任意起点出发的里程。
#include <cstdio>
#include <vector>
#include <algorithm>

typedef long long ll;

struct Cand {
    ll id;
    ll dist;
    ll h;
};

bool cand_less(const Cand& a, const Cand& b) {
    if (a.dist != b.dist) return a.dist < b.dist;
    return a.h < b.h; // 距离相同时海拔低者算更近
}

ll n;
std::vector<ll> h;
std::vector<ll> na, nb; // na[i] / nb[i]：小A / 小B 从 i 向东要去的城市
std::vector<ll> west, east;

struct Tab {
    int nxt; // 走 2^k 步后到达的城市
    ll da;   // 这 2^k 步里小A 的里程
    ll db;   // 小B 的里程
};

std::vector<Tab> up; // up[(k*2+w)*(n+1)+i]

int main() {
    if (scanf("%lld", &n) != 1) return 0; // 空输入安全返回
    h.assign(n + 1, 0);
    for (ll i = 1; i <= n; i++) scanf("%lld", &h[i]);

    std::vector<ll> ord(n);
    for (ll i = 0; i < n; i++) ord[i] = i + 1;
    for (ll i = 0; i < n; i++) { // 按海拔升序
        for (ll j = i + 1; j < n; j++) {
            if (h[ord[j]] < h[ord[i]]) {
                ll t = ord[i]; ord[i] = ord[j]; ord[j] = t;
            }
        }
    }
    west.assign(n + 1, 0);
    east.assign(n + 1, 0);
    for (ll i = 0; i + 1 < n; i++) {
        east[ord[i]] = ord[i + 1];
        west[ord[i + 1]] = ord[i];
    }

    na.assign(n + 1, 0);
    nb.assign(n + 1, 0);
    Cand cand[4];
    for (ll i = 1; i <= n; i++) {
        ll cnt = 0;
        ll j = west[i];
        for (ll t = 0; t < 2; t++) { // 海拔方向两侧各取 2 个候选
            if (j) {
                cand[cnt].id = j;
                cand[cnt].dist = h[i] - h[j] > 0 ? h[i] - h[j] : h[j] - h[i];
                cand[cnt].h = h[j];
                cnt++;
                j = west[j];
            }
        }
        j = east[i];
        for (ll t = 0; t < 2; t++) {
            if (j) {
                cand[cnt].id = j;
                cand[cnt].dist = h[i] - h[j] > 0 ? h[i] - h[j] : h[j] - h[i];
                cand[cnt].h = h[j];
                cnt++;
                j = east[j];
            }
        }
        for (ll a = 0; a < cnt; a++) { // 手写插入排序，按 (距离, 海拔) 升序
            for (ll b = a + 1; b < cnt; b++) {
                if (cand_less(cand[b], cand[a])) {
                    Cand t = cand[a]; cand[a] = cand[b]; cand[b] = t;
                }
            }
        }
        nb[i] = (cnt > 0) ? cand[0].id : 0;
        na[i] = (cnt > 1) ? cand[1].id : 0;
        east[west[i]] = east[i]; // 删掉 i，链表里剩下的全是东边城市
        west[east[i]] = west[i];
    }

    ll log = 1;
    while ((1LL << log) < n) log++;
    if (log < 1) log = 1;

    up.assign((size_t)log * 2 * (n + 1), Tab());
    for (ll i = 1; i <= n; i++) {
        if (na[i]) {
            up[0 * 2 * (n + 1) + 0 * (n + 1) + i].nxt = (int)na[i];
            ll d = h[i] - h[na[i]];
            up[0 * 2 * (n + 1) + 0 * (n + 1) + i].da = d > 0 ? d : -d;
        }
        if (nb[i]) {
            up[0 * 2 * (n + 1) + 1 * (n + 1) + i].nxt = (int)nb[i];
            ll d = h[i] - h[nb[i]];
            up[0 * 2 * (n + 1) + 1 * (n + 1) + i].db = d > 0 ? d : -d;
        }
    }

    for (ll k = 1; k < log; k++) {
        ll pre = k - 1;
        for (ll w = 0; w < 2; w++) {
            ll w2 = (k == 1) ? (w ^ 1) : w; // 后一段的先开者只与 k 有关
            for (ll i = 1; i <= n; i++) {
                ll mid = up[(pre * 2 + w) * (n + 1) + i].nxt;
                if (mid) {
                    Tab& cur = up[(k * 2 + w) * (n + 1) + i];
                    Tab& a = up[(pre * 2 + w) * (n + 1) + i];
                    Tab& b = up[(pre * 2 + w2) * (n + 1) + mid];
                    cur.nxt = b.nxt;
                    cur.da = a.da + b.da;
                    cur.db = a.db + b.db;
                }
            }
        }
    }

    ll x0, m;
    scanf("%lld %lld", &x0, &m);
    std::vector<ll> qs(m), qx(m);
    for (ll i = 0; i < m; i++) scanf("%lld %lld", &qs[i], &qx[i]);

    // 问题 1：枚举起点找 a/b 最小的出发城市
    ll best_s = 1, best_a = 0, best_b = 0;
    for (ll s = 1; s <= n; s++) {
        ll a = 0, b = 0, cur = s, w = 0;
        for (ll k = log - 1; k >= 0; k--) {
            Tab& t = up[(k * 2 + w) * (n + 1) + cur];
            if (t.nxt && a + b + t.da + t.db <= x0) {
                a += t.da;
                b += t.db;
                cur = t.nxt;
                if (k == 0) w ^= 1; // 只有 2^0 = 1 步是奇数步，才换司机
            }
        }
        if (s == 1) {
            best_s = 1; best_a = a; best_b = b;
            continue;
        }
        bool take;
        if (b == 0) {
            take = (best_b == 0 && h[s] > h[best_s]); // 两个无穷大之间比海拔
        } else if (best_b == 0) {
            take = true; // 有限比值优于无穷大
        } else {
            ll lhs = a * best_b, rhs = best_a * b; // 交叉相乘比较 a/b
            take = (lhs < rhs) || (lhs == rhs && h[s] > h[best_s]);
        }
        if (take) {
            best_s = s; best_a = a; best_b = b;
        }
    }

    printf("%lld\n", best_s);
    for (ll i = 0; i < m; i++) { // 问题 2：逐个询问模拟
        ll s = qs[i], x = qx[i];
        ll a = 0, b = 0, cur = s, w = 0;
        for (ll k = log - 1; k >= 0; k--) {
            Tab& t = up[(k * 2 + w) * (n + 1) + cur];
            if (t.nxt && a + b + t.da + t.db <= x) {
                a += t.da;
                b += t.db;
                cur = t.nxt;
                if (k == 0) w ^= 1;
            }
        }
        printf("%lld %lld\n", a, b);
    }
    return 0;
}
