/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:26
 * update_at: 2026-10-06 14:26
 */

// 国王游戏：邻项交换法证明按 a*b 升序排序最优，
// 高精度维护前面所有人左手数的乘积，逐个算 floor(P / b) 取最大值。

#include <cstdio>
#include <iostream>
#include <algorithm>

typedef long long ll;

const int MAXN = 1005;      // 大臣人数上限
const int LEN  = 4500;      // 高精度数的最大位数（1000 个 a 相乘，每个 < 10^4，最多约 4000 位）

// 高精度非负整数，低位在前，存十进制位
struct Big {
    int len;
    int d[LEN];
    Big() : len(1) {
        for (int i = 0; i < LEN; i++) d[i] = 0;
    }
};

// 高精度乘以普通整数（a < 10^4，进位用 ll 防溢出）
Big mul_small(const Big &x, ll a) {
    Big y;
    ll carry = 0;
    for (int i = 0; i < x.len; i++) {
        ll cur = (ll)x.d[i] * a + carry;
        y.d[i] = cur % 10;
        carry = cur / 10;
    }
    y.len = x.len;
    while (carry > 0) { // 补齐剩余进位
        y.d[y.len] = carry % 10;
        carry /= 10;
        y.len++;
    }
    return y;
}

// 高精度除以普通整数，返回商（向下取整）
Big div_small(const Big &x, ll b) {
    Big q;
    ll rem = 0;
    for (int i = x.len - 1; i >= 0; i--) { // 从高位往低位做除法
        rem = rem * 10 + x.d[i];
        q.d[i] = rem / b;
        rem %= b;
    }
    q.len = x.len;
    while (q.len > 1 && q.d[q.len - 1] == 0) q.len--; // 去掉前导零
    return q;
}

// 比较：返回 true 表示 a > b
bool is_greater(const Big &a, const Big &b) {
    if (a.len != b.len) return a.len > b.len;
    for (int i = a.len - 1; i >= 0; i--)
        if (a.d[i] != b.d[i]) return a.d[i] > b.d[i];
    return false;
}

struct Minister {
    ll a, b;
    ll key() const { return a * b; } // 排序关键字 a * b
};

Minister ms[MAXN]; // ms[i] 表示第 i 位大臣的左右手数字
int n;             // 大臣人数（n ≤ 1000，int 足够，可直接做数组下标）

// 按左右手乘积 a*b 从小到大排序（邻项交换法推出的贪心序）
bool cmp_minister(const Minister &x, const Minister &y) {
    return x.key() < y.key();
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);

    std::cin >> n;
    ll a0, b0;
    std::cin >> a0 >> b0; // 国王的左右手，右手 b0 不参与计算
    for (int i = 1; i <= n; i++)
        std::cin >> ms[i].a >> ms[i].b;

    std::sort(ms + 1, ms + 1 + n, cmp_minister);

    Big prefix;      // 前缀乘积：排在当前大臣前面所有人（含国王）左手数的乘积
    prefix.d[0] = 1; // 初始为 1，先乘上国王左手数 a0
    prefix = mul_small(prefix, a0);

    Big ans; // 所有大臣中获得金币数的最大值
    for (int i = 1; i <= n; i++) {
        Big reward = div_small(prefix, ms[i].b); // 该大臣获得的金币：floor(P / b)
        if (is_greater(reward, ans)) ans = reward;
        prefix = mul_small(prefix, ms[i].a);
    }

    for (int i = ans.len - 1; i >= 0; i--)
        std::cout << ans.d[i];
    std::cout << std::endl;

    return 0;
}
