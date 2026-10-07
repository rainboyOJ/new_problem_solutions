/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:11
 * update_at: 2026-10-06 18:11
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

ll p;                      // 目标次幂数 P
map<pair<ll, ll>, ll> widest; // 单层记忆化：widest[(a,b)] = 该状态下已搜过的最大剩余步数

// 判断在 rest 步预算内，能否从指数对 (x, y)（保证 x >= y >= 0）到达 P 次幂。
// used 是已用步数，limit 是本轮迭代的步数上限。
bool can_finish(ll x, ll y, ll used, ll limit) {
    if (x == p || y == p) return true;
    ll rest = limit - used; // 还剩多少步可走
    if (rest == 0) return false;

    // 上界剪枝：一步至多让较大的指数翻倍，rest 步内最大指数是 x * 2^rest，
    // 若仍小于 P 则这棵子树永远到不了 P，剪掉。
    if (x << rest < p) return false;

    // 整除剪枝：四个结果 x+y, x-y, x+x, y+y 都是 gcd(x,y) 的倍数，
    // 子树里所有指数恒为 g 的倍数，P 不整除 g 就到不了。
    // 初始 y=0 时 gcd(x,0)=x，x=1 恒整除，特判可省。
    ll g = __gcd(x, y);
    if (p % g != 0) return false;

    // 单层记忆化：同一状态若曾以更大（或相等）的剩余预算搜过且失败，
    // 这次更小的预算必然也失败，直接剪。
    pair<ll, ll> st = make_pair(x, y);
    map<pair<ll, ll>, ll>::iterator it = widest.find(st);
    if (it != widest.end() && it->second >= rest) return false;
    widest[st] = rest;

    // 一步操作 = 从 {x+y, x-y, x+x, y+y} 取一个结果写回任一工作变量，
    // 写回后按指数大小归一化成 hi >= lo（交换两个变量是同一局面）。
    ll nxt = used + 1;
    ll cand[4];
    cand[0] = x + y;
    cand[1] = x - y;
    cand[2] = x + x;
    cand[3] = y + y;
    for (int i = 0; i < 4; i++) {
        ll value = cand[i];
        ll a = value, b = y; // 写回第一个变量
        if (a < b) swap(a, b);
        if (can_finish(a, b, nxt, limit)) return true;
        a = x; b = value;    // 写回第二个变量
        if (a < b) swap(a, b);
        if (can_finish(a, b, nxt, limit)) return true;
    }
    return false;
}

// 迭代加深：limit 从 0 开始逐层增大，第一次成功的 limit 就是最少操作数。
ll min_ops() {
    for (ll limit = 0;; limit++) {
        widest.clear(); // 每一层记忆化只对本轮有效，必须清空
        if (can_finish(1, 0, 0, limit)) return limit;
    }
}

int main() {
    cin >> p;
    cout << min_ops() << endl;
    return 0;
}
