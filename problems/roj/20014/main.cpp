/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:18
 * update_at: 2026-10-06 02:18
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 105; // n <= 100，passed 最多取到 n

pair<ll, ll> customer[MAXN]; // customer[i] = (客户位置, 外卖价格)，读入后按位置升序

ll pos[MAXN];  // pos[i] 第 i 个客户的位置（升序，可负）
ll earn[MAXN]; // earn[i] 第 i 个客户的外卖价格 e

// memo[l][r][side][passed] 存对应状态的最大净赚；vis 标记该状态是否已算过
ll memo[MAXN][MAXN][2][MAXN];
char vis[MAXN][MAXN][2][MAXN];

// 取绝对值，避免使用强制转换
ll abs_ll(ll v) {
    if (v < 0) return -v;
    return v;
}

// best(l, r, side, passed)：
//   还没决定去留的客户恰为区间 [l, r]（pos 升序），无人机停在区间端点；
//   side = 0 表示停在左端 l，side = 1 表示停在右端 r；
//   passed = 已经送过外卖的客户数，作为移动成本的乘数。
// 返回从该状态继续决策能得到的最大净赚。
ll best(ll l, ll r, ll side, ll passed) {
    if (vis[l][r][side][passed]) return memo[l][r][side][passed];
    vis[l][r][side][passed] = 1;
    ll res;
    if (l == r) {
        // 只剩最后一个未决定客户：要么现在送，要么永远放弃
        ll d = abs_ll(pos[l]);
        ll send = earn[l] - d * (passed + 1); // 送：得到 e_i，付出时间成本
        ll giveup = -d * passed;              // 放弃：只付移动成本
        res = send > giveup ? send : giveup;
    } else if (side == 0) {
        // 在左端，决定最左客户 l 的去留，之后停在 l+1 或掉头到右端 r
        ll x = pos[l], nxt = pos[l + 1], far = pos[r];
        ll go_left = nxt - x; // 继续向左走的距离
        ll go_far = far - x;  // 掉头走到右端的距离
        ll best_val;
        // 送 l，继续向左
        best_val = earn[l] + best(l + 1, r, 0, passed + 1) - go_left * (passed + 1);
        // 送 l，掉头向右
        ll cand = earn[l] + best(l + 1, r, 1, passed + 1) - go_far * (passed + 1);
        if (cand > best_val) best_val = cand;
        // 放弃 l，继续向左
        cand = best(l + 1, r, 0, passed) - go_left * passed;
        if (cand > best_val) best_val = cand;
        // 放弃 l，掉头向右
        cand = best(l + 1, r, 1, passed) - go_far * passed;
        if (cand > best_val) best_val = cand;
        res = best_val;
    } else {
        // 在右端，决定最右客户 r 的去留，之后停在 r-1 或掉头到左端 l
        ll x = pos[r], prv = pos[r - 1], far = pos[l];
        ll go_right = x - prv; // 继续向右走的距离
        ll go_far = x - far;   // 掉头走到左端的距离
        ll best_val;
        // 送 r，继续向右
        best_val = earn[r] + best(l, r - 1, 1, passed + 1) - go_right * (passed + 1);
        // 送 r，掉头向左
        ll cand = earn[r] + best(l, r - 1, 0, passed + 1) - go_far * (passed + 1);
        if (cand > best_val) best_val = cand;
        // 放弃 r，继续向右
        cand = best(l, r - 1, 1, passed) - go_right * passed;
        if (cand > best_val) best_val = cand;
        // 放弃 r，掉头向左
        cand = best(l, r - 1, 0, passed) - go_far * passed;
        if (cand > best_val) best_val = cand;
        res = best_val;
    }
    memo[l][r][side][passed] = res;
    return res;
}

int main() {
    ll n;
    scanf("%lld", &n);
    for (int i = 0; i < n; i++) scanf("%lld", &customer[i].first);
    for (int i = 0; i < n; i++) scanf("%lld", &customer[i].second);
    // 按位置排序，区间 DP 才能从两端逐个决定客户的去留
    sort(customer, customer + n);
    for (int i = 0; i < n; i++) {
        pos[i] = customer[i].first;
        earn[i] = customer[i].second;
    }
    ll ans_left = best(0, n - 1, 0, 0);
    ll ans_right = best(0, n - 1, 1, 0);
    printf("%lld\n", ans_left > ans_right ? ans_left : ans_right);
    return 0;
}
