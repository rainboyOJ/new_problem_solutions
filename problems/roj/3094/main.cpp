/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:35
 * update_at: 2026-10-06 18:35
 */
#include <cstdio>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 100005; // N 最大 1e5
const int WIDTH = 30;    // a_i < 2^30，逐位拆成 30 列

ll n;
ll a[MAXN]; // 题目给出的信号，下标从 1 开始
ll run_value[MAXN];  // 某一列压缩后的连续段取值（0/1）
ll run_length[MAXN]; // 对应连续段的长度

// 计算第 k 位上的三种「有序区间计数」（未乘位权）：
// 把该位抽成 0/1 串并压缩成同值连续段，由段长得到 and / or 的区间数；
// 再由前缀异或取值次数得到 xor 的区间数，最后用 2S-T 换成有序对口径。
void count_one_bit(int k, ll &cnt_xor, ll &cnt_and, ll &cnt_or) {
    int seg = 0; // 连续段个数
    int i = 1;
    while (i <= n) {
        ll value = (a[i] >> k) & 1;
        int j = i;
        while (j <= n && ((a[j] >> k) & 1) == value) {
            j++;
        }
        seg++;
        run_value[seg] = value;
        run_length[seg] = j - i;
        i = j;
    }

    ll all_one = 0;  // 完整落在 1 段内的区间数，即 and 为 1 的无序区间数
    ll all_zero = 0; // 完整落在 0 段内的区间数
    ll ones = 0;     // 该位上 1 的个数，等于单点区间里结果为 1 的个数
    for (int t = 1; t <= seg; t++) {
        ll len = run_length[t];
        if (run_value[t] == 1) {
            all_one += len * (len + 1) / 2;
            ones += len;
        } else {
            all_zero += len * (len + 1) / 2;
        }
    }
    ll total = n * (n + 1) / 2; // l <= r 的无序区间总数

    // 前缀异或 P_i 只在扫过 1 时翻转：1 段内逐格交替，0 段内保持不变。
    ll seen[2] = {1, 0}; // P_0 = 0，先计入取值 0 的一侧
    int parity = 0;
    for (int t = 1; t <= seg; t++) {
        ll len = run_length[t];
        if (run_value[t] == 1) {
            seen[parity] += len / 2;
            seen[parity ^ 1] += (len + 1) / 2;
            parity ^= len & 1;
        } else {
            seen[parity] += len;
        }
    }

    ll un_xor = seen[0] * seen[1]; // 区间异或为 1 的无序区间数
    ll un_and = all_one;
    ll un_or = total - all_zero; // 全集减掉全 0 区间，即含 1 的区间数
    // 长度大于 1 的区间在有序对里出现两次，单点区间只出现一次
    cnt_xor = 2 * un_xor - ones;
    cnt_and = 2 * un_and - ones;
    cnt_or = 2 * un_or - ones;
}

int main() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    long double sum_xor = 0.0L;
    long double sum_and = 0.0L;
    long double sum_or = 0.0L;
    long double bit_value = 1.0L; // 当前位的位权 2^k
    for (int k = 0; k < WIDTH; k++) {
        ll cnt_xor, cnt_and, cnt_or;
        count_one_bit(k, cnt_xor, cnt_and, cnt_or);
        sum_xor += bit_value * cnt_xor;
        sum_and += bit_value * cnt_and;
        sum_or += bit_value * cnt_or;
        bit_value *= 2.0L;
    }

    long double denom = n;
    denom = denom * n; // 分母是有序对总数 N^2
    printf("%.3Lf %.3Lf %.3Lf\n", sum_xor / denom, sum_and / denom, sum_or / denom);
    return 0;
}
