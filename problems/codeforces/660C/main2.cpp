/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-09 20:36
 * update_at: 2026-11-09 21:42
 */
// main2.cpp：二分答案解法，按 rbook1《二分查找》的模板（bs_find 找第一个 check 成立的位置）来写。
// 单调性：若存在长度为 L 的合法窗口（0 的个数 <= k），则它任意长度 L-1 的子窗口也合法，
// 所以「长度 L 可行」关于 L 单调：小的 L 一定可行，大的 L 未必可行。
// 于是 check(L) 表示「长度 L 可行」，序列形如 true...true,false...false。
// bs_find 找的是第一个「不可行」的长度（即第一个 !check 成立的位置），减 1 就是最后一个可行长度。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int maxn = 300005;

ll n;               // 元素个数
ll k;               // 最多可以改的 0 的个数
int a[maxn];        // 原数组，元素只有 0/1，用 int 足够
int b[maxn];        // 答案数组（原数组修改后的结果）
ll zero_pref[maxn]; // zero_pref[i]：前 i 个元素里 0 的个数，即 zero_pref[i]-zero_pref[i-1] = (a[i]==0)

// mid：区间的中点，用移位写法
ll mid(ll l, ll r) {
    return (l + r) >> 1;
}

// check：长度 len 是否「可行」，即存在长度恰为 len 且 0 的个数 <= k 的窗口。
// 长度 len 越小越容易满足，所以 check 关于 len 是 true...true,false...false。
bool check(ll len) {
    if (len == 0) {
        return true; // 空窗口永远合法，长度为 0 一定可行
    }
    for (ll i = 0; i + len <= n; i++) {
        if (zero_pref[i + len] - zero_pref[i] <= k) {
            return true; // 找到一个合法窗口，长度 len 可行
        }
    }
    return false; // 没有任何合法窗口，长度 len 不可行
}

// bs_find：在区间 [l, r] 上找第一个「不可行」的位置（即第一个 !check 成立的位置）。
// 条件：保证区间 [l, r] 上必然存在一个不可行的位置（这里 r = n+1 一定不可行）。
ll bs_find(ll l, ll r) {
    while (l < r) {
        ll m = mid(l, r);
        if (!check(m)) { // 不可行，成立：第一个不可行在 m 或更左
            r = m;
        } else { // 可行，不成立：第一个不可行在 m 右侧
            l = m + 1;
        }
    }
    return l;
}

void read_input() {
    cin >> n >> k;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
        b[i] = a[i];
        zero_pref[i] = zero_pref[i - 1] + (a[i] == 0 ? 1 : 0);
    }
}

void solve() {
    // bs_find 返回第一个不可行的长度，它左边那个就是最后一个可行长度，即答案。
    // 上界取 n+1：长度 n+1 超过数组长度，一定不可行，作为 check 必然不成立的哨兵。
    ll best_len = bs_find(0, n + 1) - 1;

    // 找到任意一个长度恰为 best_len 且 0 的个数 <= k 的窗口，翻转其中的 0
    ll best_left = 1;
    if (best_len > 0) {
        for (ll i = 0; i + best_len <= n; i++) {
            if (zero_pref[i + best_len] - zero_pref[i] <= k) {
                best_left = i + 1;
                break;
            }
        }
        for (ll i = best_left; i <= best_left + best_len - 1; i++) {
            b[i] = 1;
        }
    }

    cout << best_len << "\n";
    for (ll i = 1; i <= n; i++) {
        cout << b[i] << " \n"[i == n];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
