/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:43
 * update_at: 2026-10-06 18:43
 */

// 期望 DP 逆推：f(a,b,c,d,x,y) = 处于该局面时还需翻开的牌数的期望。
// a,b,c,d 是四堆里普通牌的张数（0..13）；
// x,y ∈ 0..4，0 表示该王还没翻到，1..4 表示它已被指定成黑桃/红桃/梅花/方块。
// 王必须在翻开的瞬间定花色，所以指派必须是状态的一部分，转移时对四种指派取 min。

#include <cstdio>
#include <algorithm>

typedef long long ll;

const int SUIT = 13;        // 每种花色 13 张
const int CARDS = 54;       // 一副牌 54 张，含大小王
const int DIM = SUIT + 2;   // 计数维取 0..14：多留一格放"王补进来的那一张"
const int SLOTS = 25;       // (x,y) 两个王的状态数 5*5
const int SPAN = DIM * DIM * DIM * DIM * SLOTS; // 状态总数

double f[SPAN];             // f[o] = 从状态 o 出发还需翻开的期望张数
double inv[CARDS + 1];      // inv[t] = 1/t，隐式概率只在这里出现

ll A, B, C, D;              // 四门的目标张数

// 已落位王数 p 对应的 (x,y) 枚举顺序：p 从 2 到 0，保证王维后继先算好。
// pairs 按 p 降序排列，pairs[i] = x * 5 + y
int pairs[SLOTS] = {
    4*5+4, 4*5+3, 3*5+4, 4*5+2, 2*5+4, 3*5+3, 4*5+1, 1*5+4,
    2*5+3, 3*5+2, 4*5+0, 0*5+4, 1*5+3, 2*5+2, 3*5+1, 0*5+3,
    1*5+2, 2*5+1, 3*5+0, 0*5+2, 1*5+1, 2*5+0, 0*5+1, 1*5+0, 0*5+0
};

// 王记在 x/y 上、不顶替计数维，所以判断某门够不够要看 a + [x 是这门] + [y 是这门]
bool done(ll a, ll b, ll c, ll d, ll x, ll y) {
    return a + (x == 1) + (y == 1) >= A
        && b + (x == 2) + (y == 2) >= B
        && c + (x == 3) + (y == 3) >= C
        && d + (x == 4) + (y == 4) >= D;
}

// 目标是否超出牌库：每门普通牌只有 13 张，缺口超过 2 张（两张王）就凑不齐
bool impossible() {
    ll lack = std::max(0LL, A - SUIT) + std::max(0LL, B - SUIT)
            + std::max(0LL, C - SUIT) + std::max(0LL, D - SUIT);
    return lack > 2;
}

void solve() {
    std::scanf("%lld %lld %lld %lld", &A, &B, &C, &D);
    if (impossible()) {
        printf("-1.000\n");
        return;
    }
    for (int t = 1; t <= CARDS; ++t) inv[t] = 1.0 / t;

    // 枚举顺序：a,b,c,d 从 13 递减（计数后继已算过）；王按已落位张数从 2 降到 0
    for (int a = SUIT; a >= 0; --a)
        for (int b = SUIT; b >= 0; --b)
            for (int c = SUIT; c >= 0; --c)
                for (int d = SUIT; d >= 0; --d) {
                    ll base = (((ll)a * DIM + b) * DIM + c) * DIM + d;
                    base *= SLOTS;
                    for (int i = 0; i < SLOTS; ++i) {
                        ll x = pairs[i] / 5, y = pairs[i] % 5;
                        ll o = base + pairs[i];
                        if (done(a, b, c, d, x, y)) { f[o] = 0.0; continue; } // 已达标，停手
                        // 没翻开的牌数：剩余普通牌 + 还没落位的王
                        ll left = CARDS - a - b - c - d - (x > 0) - (y > 0);
                        if (left <= 0) { f[o] = 1e30; continue; } // 牌翻光仍差，哨兵
                        double v = 1.0 + inv[left] * (
                            (SUIT - a) * f[o + DIM * DIM * DIM * SLOTS]  // 翻出黑桃
                          + (SUIT - b) * f[o + DIM * DIM * SLOTS]        // 翻出红桃
                          + (SUIT - c) * f[o + DIM * SLOTS]              // 翻出梅花
                          + (SUIT - d) * f[o + SLOTS]);                  // 翻出方块
                        if (x == 0) { // 翻到第一张王：当场选一门，取期望最小的指派
                            // o 已含 y 分量，o + 5u 即状态 (a,b,c,d,u,y)
                            double best = 1e30;
                            for (int u = 1; u <= 4; ++u)
                                best = std::min(best, f[o + 5 * u]);
                            v += inv[left] * best;
                        }
                        if (y == 0) { // 翻到第二张王，同样当场选；o + u 即状态 (a,b,c,d,x,u)
                            double best = 1e30;
                            for (int u = 1; u <= 4; ++u)
                                best = std::min(best, f[o + u]);
                            v += inv[left] * best;
                        }
                        f[o] = v;
                    }
                }
    printf("%.3f\n", f[0]);
}

int main() {
    solve();
    return 0;
}
