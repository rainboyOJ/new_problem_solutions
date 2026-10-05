/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 00:12
 * update_at: 2026-10-06 00:12
 */
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

const int MAXN = 2000005;
const ll BASE = 131;
const ll MOD = 1000000000000000003LL; // 64 位大质数

char s[MAXN];
ll pw[MAXN];      // BASE 的幂次
ll pre[MAXN];     // 前缀哈希

// 获取子串 [l, r) 的哈希值，下标从 0 开始
ll get_hash(int l, int r) {
    ll res = pre[r] - pre[l] * pw[r - l] % MOD;
    if (res < 0) res += MOD;
    return res;
}

// 获取区间 [l, r) 删除位置 p（l <= p < r）后的哈希值
ll hash_without(int l, int r, int p) {
    ll left = get_hash(l, p);
    ll right = get_hash(p + 1, r);
    return (left * pw[r - p - 1] % MOD + right) % MOD;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    if (!(cin >> n)) return 0;
    cin >> (s + 1); // 让 s[1..n] 有效，但逻辑里转 0 基更方便，这里读入后统一用 0 基数组 s[0..n-1]
    // 重新处理：把 s[1..n] 移到 s[0..n-1]
    for (int i = 1; i <= n; ++i) s[i - 1] = s[i];

    if (n % 2 == 0) {
        cout << "NOT POSSIBLE\n";
        return 0;
    }

    int L = n / 2; // 原串长度

    pw[0] = 1;
    for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * BASE % MOD;

    pre[0] = 0;
    for (int i = 0; i < n; ++i) {
        pre[i + 1] = (pre[i] * BASE + (s[i] - 'A' + 1)) % MOD;
    }

    // 候选原串集合，最多只有 2 种
    string ans = "";
    bool has_ans = false;
    bool not_unique = false;

    for (int p = 0; p < n; ++p) {
        bool ok = false;
        string cand = "";
        if (p < L) {
            // 前半段 [0, L+1) 删除 p，与后半段 [L+1, n) 比较
            ll h1 = hash_without(0, L + 1, p);
            ll h2 = get_hash(L + 1, n);
            if (h1 == h2) {
                ok = true;
                cand.assign(s + L + 1, s + n); // 后半段就是原串
            }
        } else if (p == L) {
            ll h1 = get_hash(0, L);
            ll h2 = get_hash(L + 1, n);
            if (h1 == h2) {
                ok = true;
                cand.assign(s, s + L); // 前半段就是原串
            }
        } else {
            // 后半段 [L, n) 删除 p，与前半段 [0, L) 比较
            ll h1 = get_hash(0, L);
            ll h2 = hash_without(L, n, p);
            if (h1 == h2) {
                ok = true;
                cand.assign(s, s + L); // 前半段就是原串
            }
        }

        if (ok) {
            if (!has_ans) {
                has_ans = true;
                ans = cand;
            } else if (ans != cand) {
                not_unique = true;
                break;
            }
        }
    }

    if (not_unique) {
        cout << "NOT UNIQUE\n";
    } else if (!has_ans) {
        cout << "NOT POSSIBLE\n";
    } else {
        cout << ans << "\n";
    }

    return 0;
}
