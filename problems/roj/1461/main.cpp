/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:40
 * update_at: 2026-10-05 02:40
 */
#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 200005;

// 正反两向滚动哈希，2^64 自然溢出等价于模 2^64，底数取奇数保证可逆
typedef unsigned long long ull;

const ull BASE = 1000003ULL; // 奇数底数，B^k 在模 2^64 下可逆

ll n;                          // 珠子个数
ll a[MAXN];                    // a[i] 为第 i 个珠子的颜色（下标从 1 开始）
ull pw[MAXN];                  // pw[i] = BASE^i
ull pre[MAXN];                 // pre[i] = a[1..i] 的正向哈希
ull suf[MAXN];                 // suf[i] = a[i..n] 的反向哈希（越靠左权重越高）
ull block_code[MAXN];          // 当前 k 下每个完整块的编码（正读、倒读哈希取小）

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (ll i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 三张预处理表都是 O(n)
    pw[0] = 1ULL;
    for (ll i = 1; i <= n; i++) {
        pw[i] = pw[i - 1] * BASE;
    }
    pre[0] = 0ULL;
    for (ll i = 1; i <= n; i++) {
        pre[i] = pre[i - 1] * BASE + a[i];
    }
    suf[n + 1] = 0ULL;
    for (ll i = n; i >= 1; i--) {
        suf[i] = suf[i + 1] * BASE + a[i];
    }

    ll best = -1;        // 目前找到的最大不同块数
    vector<ll> ks;       // 取得最大值的所有 k（升序）

    for (ll k = 1; k <= n; k++) {
        ll m = n / k;    // 完整块个数，末尾不足 k 的珠子丢弃

        // 每个块用正读哈希 fwd 与倒读哈希 bwd 的较小者作为编码；
        // 块与其反转的编码相同，于是同一个编码只算一个不同块
        for (ll idx = 0; idx < m; idx++) {
            ll p = idx * k + 1;                          // 块起点（1-based）
            ull fwd = pre[p + k - 1] - pre[p - 1] * pw[k];
            ull bwd = suf[p] - suf[p + k] * pw[k];
            block_code[idx] = fwd < bwd ? fwd : bwd;
        }

        // 排序后统计不同编码个数，即为 cnt(k)
        sort(block_code, block_code + m);
        ll cnt = 0;
        for (ll idx = 0; idx < m; idx++) {
            if (idx == 0 || block_code[idx] != block_code[idx - 1]) {
                cnt++;
            }
        }

        if (cnt > best) {
            best = cnt;
            ks.clear();
            ks.push_back(k);
        } else if (cnt == best) {
            ks.push_back(k);
        }
    }

    cout << best << ' ' << ks.size() << '\n';
    for (size_t i = 0; i < ks.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << ks[i];
    }
    cout << '\n';

    return 0;
}
