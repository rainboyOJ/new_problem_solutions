/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:12
 * update_at: 2026-10-05 09:12
 */
// 凸多边形三角剖分的最小乘积和：区间 DP + 高精度。
// f[i][j] = 子多边形 [i..j] 的最小乘积和，枚举与边界边 (i,j) 组成
// 三角形的顶点 k，劈成 [i..k] 与 [k..j] 两段：
//   f[i][j] = min{ f[i][k] + f[k][j] + w_i * w_k * w_j }
// 权值 < 1e9 时单个乘积可达 ~1e27，总和 ~1e29，超出 64 位整数，必须高精度。
#include <cstdio>

typedef long long ll;

const int MAXN = 55;         // 顶点数上限
const ll BASE = 1000000000;  // 高精度压 9 位十进制
const int MAXD = 6;          // 每个大数最多 6 段，可存 ~1e54，足够

// 压位高精度整数：低位在前，每段存 9 位十进制
struct Big {
    int len;      // 有效段数，len = 0 表示数值 0
    ll d[MAXD];   // d[i] 是第 i 段，0 <= d[i] < BASE
};

ll n;                        // 顶点数
ll w[MAXN];                  // w[i] 为顶点 i 的权值
Big f[MAXN][MAXN];           // f[i][j]：子多边形 [i..j] 的最小乘积和（高精度）

// 大数清零
void big_zero(Big &a) {
    a.len = 0;
}

// 大数加法：c = a + b
Big big_add(Big a, Big b) {
    Big c;
    int len = a.len > b.len ? a.len : b.len;
    ll carry = 0;
    for (int i = 0; i < len; i++) {
        ll cur = carry;
        if (i < a.len) cur += a.d[i];
        if (i < b.len) cur += b.d[i];
        c.d[i] = cur % BASE;
        carry = cur / BASE;
    }
    c.len = len;
    while (carry > 0) {          // 进位可能多出一段
        c.d[c.len] = carry % BASE;
        carry /= BASE;
        c.len++;
    }
    return c;
}

// 大数乘小整数：c = a * b（b < 1e9，保证中间结果不溢出）
Big big_mul_ll(Big a, ll b) {
    Big c;
    if (b == 0 || a.len == 0) {  // 乘 0 直接得 0
        c.len = 0;
        return c;
    }
    ll carry = 0;
    for (int i = 0; i < a.len; i++) {
        ll cur = a.d[i] * b + carry;
        c.d[i] = cur % BASE;
        carry = cur / BASE;
    }
    c.len = a.len;
    while (carry > 0) {
        c.d[c.len] = carry % BASE;
        carry /= BASE;
        c.len++;
    }
    return c;
}

// 比较大小：a < b 返回 -1，相等返回 0，a > b 返回 1
int big_cmp(Big a, Big b) {
    if (a.len != b.len) {        // 段数少（无前导零段）的数一定小
        return a.len < b.len ? -1 : 1;
    }
    for (int i = a.len - 1; i >= 0; i--) {  // 从最高段往低位比
        if (a.d[i] != b.d[i]) return a.d[i] < b.d[i] ? -1 : 1;
    }
    return 0;
}

// 输出大数：最高段不带前导零，其余段补满 9 位
void big_print(Big a) {
    if (a.len == 0) {            // len = 0 表示 0
        printf("0\n");
        return;
    }
    printf("%lld", a.d[a.len - 1]);
    for (int i = a.len - 2; i >= 0; i--) {
        printf("%09lld", a.d[i]);
    }
    printf("\n");
}

int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) scanf("%lld", &w[i]);

    // 边界：不足 3 个顶点没有三角形，f = 0
    for (int i = 1; i <= (int)n; i++) {
        big_zero(f[i][i]);
        if (i < (int)n) big_zero(f[i][i + 1]);
    }

    // len = 区间长度 - 1（即 j - i），从小到大保证子状态已算出
    for (int len = 2; len < (int)n; len++) {
        for (int i = 1; i + len <= (int)n; i++) {
            int j = i + len;
            bool first = true;   // 是否第一次赋值（用于初始化最小值）
            for (int k = i + 1; k < j; k++) {
                // 三顶点乘积：从 w[i] 的大数形式逐步乘 w[k]、w[j]
                Big wi;
                wi.len = 0;
                ll t = w[i];
                while (t > 0) {  // 权值转成大数（压 9 位）
                    wi.d[wi.len] = t % BASE;
                    t /= BASE;
                    wi.len++;
                }
                Big product = big_mul_ll(wi, w[k]);
                product = big_mul_ll(product, w[j]);
                Big cand = big_add(big_add(f[i][k], f[k][j]), product);
                if (first || big_cmp(cand, f[i][j]) < 0) {
                    f[i][j] = cand;
                    first = false;
                }
            }
        }
    }

    big_print(f[1][n]);
    return 0;
}
