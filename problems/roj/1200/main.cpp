/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 05:19
 * update_at: 2026-10-05 05:19
 */

#include <cstdio>

const int MAXA = 32768; // a 的取值范围上界（题面：1 < a < 32768）
const int MAXLO = 182;  // 因子下界 lo 不超过 sqrt(32767) = 181，留一点余量

typedef long long ll;

// memo[n][lo] = 把 n 拆成若干个不小于 lo 的因子之积的方案数；0 表示还没算过。
// 答案最大只有 1713（a = 30240 时），用 int 足够，可省一半内存。
int memo[MAXA][MAXLO];

// 求把 n 拆成若干不小于 lo 的因子之积（因子非降序、可重复）的方案数。
// 非降序写法让每个无序分解只被数一次，因此不需要 set 去重。
int count_ways(int n, int lo) {
    if (memo[n][lo] != 0) return memo[n][lo]; // 记忆化：同一状态只算一次
    int res = 1; // 初值 1 表示不再往下拆，正好对应题面的 a = a 这一种分解
    // 非降序要求首因子 d 满足 d <= n/d，即 d*d <= n；d <= 181，int 乘法不会溢出
    for (int d = lo; d * d <= n; ++d) {
        if (n % d == 0) res += count_ways(n / d, d); // 选 d 后，剩下 n/d 的因子下界收紧到 d
    }
    memo[n][lo] = res;
    return res;
}

int main() {
    int t;
    scanf("%d", &t);
    for (int i = 1; i <= t; ++i) {
        int a;
        scanf("%d", &a);
        printf("%d\n", count_ways(a, 2)); // 合法因子最小是 2
    }
    return 0;
}
