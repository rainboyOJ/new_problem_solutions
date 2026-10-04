/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-02 18:35
 * update_at: 2026-10-04 23:14
 */
// main.cpp：序列长度 2n 且始终有序，询问把区间 [l,r]（长度 2t）分离成两个长度为 t 的子序列，
// 求所有分离方式中「差距」的最大值、最小值与方案数，区间还会整体加 val。
//
// 三条结论（序列有序是关键）：
// 1. 最大差距：让前 t 个整体当小的那半、后 t 个当大的那半，差距 = sum(后 t 个) - sum(前 t 个)。
// 2. 最小差距：相邻两两配对 (l,l+1),(l+2,l+3),... 的差之和；只需知道区间内偶数下标元素之和，
//    就能由区间总和推出它（l 为奇数时 = 2*偶数和 - 总和，否则 = 总和 - 2*偶数和）。
// 3. 方案数只与 t 有关，等于第 t 个卡特兰数 C_t。
//
// 区间加 + 区间求和用双树状数组维护差分：b1 存 d_i，b2 存 d_i*(i-1)，
// 则前 i 项和 = i*sum(b1) - sum(b2)。偶数下标元素之和再按 2j -> j 压缩到一棵同样结构的树里。

#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 1100005; // 2n 最大 1e6（n <= 5e5）
const int MAXH = 550005;  // n 最大 5e5
const ll MOD = 1000000007;

int n, m;
int len; // 序列长度 2n

ll s0[MAXN];   // s0[i]：原序列 1..i 的初始前缀和
ll se0[MAXH];  // se0[j]：偶数下标元素 2,4,...,2j 的初始前缀和
ll bit1[MAXN]; // 全序列区间加：差分量 d_i
ll bit2[MAXN]; // 全序列区间加：d_i*(i-1)，用来还原区间和
ll bite1[MAXH]; // 偶数下标（按 2j -> j 压缩）区间加：差分量
ll bite2[MAXH]; // 偶数下标压缩后区间加：差分量*(j-1)
ll inv[MAXH];   // inv[i]：i 在模 MOD 下的逆元
ll cnt[MAXH];   // cnt[t]：长度为 2t 的区间的分离方案数，即卡特兰数 C_t

// 在双树状数组上把区间 [l,r] 整体加上 delta，size 为这棵树对应的下标上限
void range_add(ll *b1, ll *b2, int size, int l, int r, ll delta) {
    ll add_l = delta * (l - 1); // b2 在 l 处的增量
    ll add_r = delta * r;       // b2 在 r+1 处的增量
    for (int i = l; i <= size; i += i & -i) {
        b1[i] += delta;
        b2[i] += add_l;
    }
    for (int i = r + 1; i <= size; i += i & -i) {
        b1[i] -= delta;
        b2[i] -= add_r;
    }
}

// 区间加之后，下标 1..i 的元素和 = i*sum(b1) - sum(b2)
ll prefix_sum(ll *b1, ll *b2, int i) {
    ll sum1 = 0, sum2 = 0;
    for (int j = i; j > 0; j -= j & -j) {
        sum1 += b1[j];
        sum2 += b2[j];
    }
    return sum1 * i - sum2;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> n >> m;
    len = 2 * n;

    ll total = 0;      // 全序列前缀和
    ll even_total = 0; // 偶数下标元素前缀和
    for (int i = 1; i <= len; i++) {
        ll x;
        cin >> x;
        total += x;
        s0[i] = total;
        if (i % 2 == 0) {
            even_total += x;
            se0[i / 2] = even_total;
        }
    }

    // 线性求逆元后递推卡特兰数：C_t = C_{t-1} * (4t-2) / (t+1)
    inv[1] = 1;
    for (int i = 2; i <= n + 1; i++) {
        inv[i] = MOD - MOD / i * inv[MOD % i] % MOD;
    }
    cnt[1] = 1; // 区间最短为 2，t 从 1 开始
    for (int t = 2; t <= n; t++) {
        cnt[t] = cnt[t - 1] * (4 * t - 2) % MOD * inv[t + 1] % MOD;
    }

    for (int q = 0; q < m; q++) {
        int op, l, r;
        cin >> op >> l >> r;
        if (op == 0) {
            ll val;
            cin >> val;
            range_add(bit1, bit2, len, l, r, val);
            int even_first = l + (l & 1);  // [l,r] 内第一个偶数下标
            int even_last = r - (r & 1);   // [l,r] 内最后一个偶数下标
            if (even_first <= even_last) {
                range_add(bite1, bite2, n, even_first / 2, even_last / 2, val);
            }
        } else {
            int t = (r - l + 1) / 2; // 每个子序列的长度
            int mid = r - t;         // 前后各取一半的分界点
            ll high = s0[r] + prefix_sum(bit1, bit2, r);
            ll near_mid = s0[mid] + prefix_sum(bit1, bit2, mid);
            ll low = s0[l - 1] + prefix_sum(bit1, bit2, l - 1);
            ll gap = high - 2 * near_mid + low; // 最大差距
            ll even = se0[r / 2] + prefix_sum(bite1, bite2, r / 2)
                    - se0[(l - 1) / 2] - prefix_sum(bite1, bite2, (l - 1) / 2);
            ll full = high - low; // 区间总和
            ll near = (l & 1) ? even + even - full : full - even - even; // 最小差距
            cout << (gap % MOD + MOD) % MOD << ' '
                 << (near % MOD + MOD) % MOD << ' '
                 << cnt[t] << '\n';
        }
    }

    return 0;
}
