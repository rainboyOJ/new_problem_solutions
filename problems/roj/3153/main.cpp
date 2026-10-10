/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 炮兵阵地：逐行推进的状态压缩 DP，键是 (本行列方案 x, 上一行列方案 y)。
#include <cstdio>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

typedef long long ll;

const ll SPREAD = 2; // 一门炮沿行、沿列都攻击左右各 SPREAD 格

ll width;
std::vector<ll> legal; // 一行内部互不攻击的列方案

// 一行内部互不攻击的列方案 x：两炮列距为 1 或 2 时会互相攻击
void build_legal() {
    legal.clear();
    for (ll x = 0; x < (1LL << width); x++) {
        if ((x & (x << 1)) == 0 && (x & (x << 2)) == 0) legal.push_back(x);
    }
}

ll popcount_ll(ll x) {
    ll c = 0;
    while (x) {
        c += (x & 1);
        x >>= 1;
    }
    return c;
}

int main() {
    ll n;
    if (scanf("%lld %lld", &n, &width) != 2) return 0;
    build_legal();

    // 题面每行可能连写，也可能逐字符用空格分隔，统一拼成一串再按行切
    std::string flat;
    std::string tok;
    while (std::cin >> tok) flat += tok;
    std::vector<std::string> rows(n);
    for (ll i = 0; i < n; i++) rows[i] = flat.substr(i * width, width);

    ll S = 1LL << width;
    std::vector<ll> cur(S * S, -1), nxt(S * S, -1); // 值 = 已决策行里最多放了多少炮
    std::vector<int> keys;

    // 每行的平原掩码与真正可选的列方案集合
    std::vector<std::vector<ll> > allowed(n);
    for (ll r = 0; r < n; r++) {
        ll plain = 0;
        for (ll c = 0; c < width; c++) {
            if (rows[r][c] == 'P') plain |= 1LL << c;
        }
        for (size_t t = 0; t < legal.size(); t++) {
            if ((legal[t] & ~plain) == 0) allowed[r].push_back(legal[t]);
        }
    }

    // 第 0 行没有上一行，用 y = 0 代表这一层约束不存在
    for (size_t t = 0; t < allowed[0].size(); t++) {
        ll x = allowed[0][t];
        cur[x * S + 0] = popcount_ll(x);
        keys.push_back((int)(x * S + 0));
    }

    for (ll r = 1; r < n; r++) {
        for (ll t = 0; t < S * S; t++) nxt[t] = -1;
        std::vector<int> nkeys;
        for (size_t a = 0; a < keys.size(); a++) {
            ll x = keys[a] / S, y = keys[a] % S;
            ll total = cur[keys[a]];
            ll blocked = x | y; // 本行、上行的炮位
            for (size_t c = 0; c < allowed[r].size(); c++) {
                ll z = allowed[r][c];
                if (z & blocked) continue; // 同列即纵向距离 ≤ SPREAD，冲突
                ll nk = z * S + x;
                ll cand = total + popcount_ll(z);
                if (cand > nxt[nk]) {
                    if (nxt[nk] < 0) nkeys.push_back((int)nk);
                    nxt[nk] = cand;
                }
            }
        }
        cur.swap(nxt);
        keys.swap(nkeys);
    }

    ll ans = 0;
    for (size_t a = 0; a < keys.size(); a++) {
        if (cur[keys[a]] > ans) ans = cur[keys[a]];
    }
    printf("%lld\n", ans);
    return 0;
}
