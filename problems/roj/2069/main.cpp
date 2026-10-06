/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:13
 * update_at: 2026-10-06 11:13
 */

#include <cstdio>
#include <set>
#include <vector>

using namespace std;

typedef long long ll;

const int MAXN = 5005;       // N 最大 5000，再加末尾哨兵
const int BASE = 1000000000; // 大整数压 9 位十进制，方案数可能超过 64 位

// 非负大整数，digits 低位在前，digits[0] 存放最低 9 位
struct BigInt {
    vector<int> digits;
};

ll a[MAXN];     // a[i] 为第 i 天股价，a[n+1] 是补上的哨兵 0
ll f[MAXN];     // f[i] 为以第 i 天结尾的最长严格下降子序列长度
BigInt g[MAXN]; // g[i] 为以第 i 天结尾且长度取到 f[i] 的去重方案数

// 大整数加法：x += y
void big_add(BigInt &x, const BigInt &y) {
    int carry = 0;
    for (int i = 0; i < (int)y.digits.size() || carry > 0; i++) {
        if (i == (int)x.digits.size()) {
            x.digits.push_back(0);
        }
        ll cur = x.digits[i] + carry;
        if (i < (int)y.digits.size()) {
            cur += y.digits[i];
        }
        x.digits[i] = cur % BASE;
        carry = cur / BASE;
    }
}

// 输出大整数，最高位不带前导零，其余每组补足 9 位
void big_print(const BigInt &x) {
    if (x.digits.empty()) {
        printf("0");
        return;
    }
    printf("%d", x.digits.back());
    for (int i = (int)x.digits.size() - 2; i >= 0; i--) {
        printf("%09d", x.digits[i]);
    }
}

int main() {
    ll n;
    if (scanf("%lld", &n) != 1) {
        return 0;
    }
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }
    a[n + 1] = 0; // 哨兵：0 比所有正整数股价都小，汇聚全部最长下降子序列
    int total = n + 1;

    for (int i = 1; i <= total; i++) {
        f[i] = 1;
        for (int j = 1; j < i; j++) {
            if (a[j] > a[i] && f[j] + 1 > f[i]) {
                f[i] = f[j] + 1;
            }
        }

        if (f[i] == 1) {
            g[i].digits.clear();
            g[i].digits.push_back(1);
            continue;
        }

        // 从后往前找长度恰为 f[i]-1 的前驱；同数值只取最靠后的位置，避免数值序列重复
        g[i].digits.clear();
        set<ll> seen;
        for (int j = i - 1; j >= 1; j--) {
            if (a[j] > a[i] && f[j] == f[i] - 1 && seen.find(a[j]) == seen.end()) {
                seen.insert(a[j]);
                big_add(g[i], g[j]);
            }
        }
    }

    printf("%lld ", f[total] - 1);
    big_print(g[total]);
    printf("\n");
    return 0;
}
