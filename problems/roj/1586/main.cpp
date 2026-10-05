/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 10:39
 * update_at: 2026-10-05 10:39
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int LEAD = 10; // 哨兵：上一位"还不存在"（更高位全是前导零），避免和合法数位 0~9 混淆

ll w[15][15];  // w[r][low] = 长度为 r、每位取自 [low, 9] 且非降的串数 = C(r + 9 - low, r)
ll digits[15]; // n 的十进制数位，digits[1] 是最高位
ll len;        // n 的位数

// 预处理自由段的组合数：把 r 个取值和 9 - low 块隔板排成一列，选 r 个位置当取值。
// 递推 w[r][low] = w[r-1][low] * (r + 9 - low) / r，整数整除恒成立，无精度问题。
void init_ways() {
    for (int low = 0; low <= LEAD; low++) {
        w[0][low] = 1;
        for (int r = 1; r <= 11; r++) {
            w[r][low] = w[r - 1][low] * (r + 9 - low) / r;
        }
    }
}

// 统计 [0, n] 内有多少个不降数（0 也算一位数，count_upto(0) = 1）。
// 把 [0, n] 按"第 i 位首次小于上界"分类：该位取 v ∈ [low, cur-1] 压到 n 以下后，
// 剩余 rest 位彻底自由，只需非降且每位 >= v，用 w[rest][v] 一次算完。
ll count_upto(ll n) {
    if (n < 0) return 0;

    // 拆数位，digits[1] 为最高位
    len = 0;
    ll t = n;
    while (t > 0) {
        len++;
        digits[len] = t % 10;
        t /= 10;
    }
    for (ll i = 1; i <= len / 2; i++) {
        swap(digits[i], digits[len + 1 - i]);
    }

    ll total = 0;
    ll high = LEAD; // 上一位的数字；LEAD 表示数还没开始（前面全是前导零）
    for (ll i = 1; i <= len; i++) {
        ll cur = digits[i];
        ll low = 0; // 本位的下界：数还没开始时前导零不参与不降判定，可取 0
        if (high != LEAD) low = high;
        ll rest = len - i; // 这一位固定后，低位还剩多少位

        // 枚举本位首次小于上界的取值 v，低位自由填不降串
        for (ll v = low; v < cur; v++) {
            total += w[rest][v];
        }
        if (cur < low) return total; // n 自身在这一位断裂，更深的链全部不合法，立即返回
        high = cur;
    }
    return total + 1; // 每一位都贴着 n，n 本身也是不降数
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_ways();

    ll a, b;
    // 多组数据，EOF 结束；答案 = F(b) - F(a-1)
    while (cin >> a >> b) {
        cout << count_upto(b) - count_upto(a - 1) << "\n";
    }

    return 0;
}
