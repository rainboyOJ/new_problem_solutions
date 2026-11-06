/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-04 18:43
 * update_at: 2026-11-06 23:10
 */
// main-optimize.cpp：与 main-optimize.py 是同一套写法。
// 算法骨架和 main.cpp 完全一样：枚举半长 q，算出「s[i] 与 s[i+q] 相容」的数组，
// 再判断其中是否存在长度 q 的连续相容。
// 这里把整条数组压进 std::bitset，用移位和按位与一次算完整排，
// 再用倍增法 m &= m >> L 判断连续 1，单次 q 只需 O(log q) 次移位。
// 时间约 O(n^2 log n / 64)，空间 O(n) 位。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 5005;

ll t;
string s;
ll n;

bitset<MAXN> mask_of_char[26]; // mask_of_char[c] 的第 i 位为 1 <=> s[i] == 'a' + c
bitset<MAXN> mask_of_question; // mask_of_question 的第 i 位为 1 <=> s[i] == '?'
bitset<MAXN> cur;              // 当前 q 下「s[i] 与 s[i+q] 相容」的位图

// 判断 cur 中是否存在长度 q 的连续 1。
// 第 k 轮执行 cur &= cur >> L（L = 1,2,4,...）后，
// 第 i 位为 1 当且仅当原 cur 的 [i-2^k+1, i] 全为 1。
bool has_run(ll q) {
    bitset<MAXN> m = cur;
    ll L = 1;
    while (L * 2 <= q) {
        m &= (m >> L);
        if (m.none()) {
            return false;
        }
        L *= 2;
    }
    ll rest = q - L; // 还差 rest 位，再对齐一次
    if (rest > 0) {
        m &= (m >> rest);
    }
    return m.any();
}

// 判断半长 q 是否存在串联重复
bool check(ll q) {
    // 三种相容情况：两边都是 '?'、某一边是 '?'、两边同字母
    cur = mask_of_question | (mask_of_question >> q);
    for (int c = 0; c < 26; c++) {
        cur |= (mask_of_char[c] & (mask_of_char[c] >> q));
    }
    // 各 mask 只含下标 < n 的位，右移 q 位后自然落在 [0, n-q)，无需截断
    if (cur.none()) {
        return false;
    }
    return has_run(q);
}

void solve() {
    n = s.size();

    // 长度为 0 或 1 的串不可能有串联重复
    if (n < 2) {
        cout << 0 << '\n';
        return;
    }

    for (int c = 0; c < 26; c++) {
        mask_of_char[c].reset();
    }
    mask_of_question.reset();
    for (ll i = 0; i < n; i++) {
        if (s[i] == '?') {
            mask_of_question.set(i);
        } else {
            mask_of_char[s[i] - 'a'].set(i);
        }
    }

    ll ans = 0;
    // q 从大到小枚举，命中即停；2q 已不超过答案时无需再试
    for (ll q = n / 2; q >= 1; q--) {
        if (2 * q <= ans) {
            break;
        }
        if (check(q)) {
            ans = 2 * q;
            break;
        }
    }
    cout << ans << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> t;
    while (t--) {
        cin >> s;
        solve();
    }

    return 0;
}
