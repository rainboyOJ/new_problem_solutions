/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 18:44
 * update_at: 2026-10-06 18:44
 */

// main.cpp：把每条工人记录看成一条模 7 的线性同余方程，用高斯消元判定
// 无解 / 多解 / 唯一解，并把唯一解的余数还原成 3..9 天。
//
// 关键建模：
//   - 设型号 j 在一条记录里出现 c 次，则工人在岗天数 d = sum c[j] * x[j]（同型号做几次加几次）；
//   - 记录只给星期，首尾都算，所以 d ≡ e - s + 1 (mod 7)，得到一条模 7 方程；
//   - 合法天数 3..9 共 7 个，模 7 后恰好覆盖 7 个剩余类（0/1/2 对应 7/8/9），
//     因此「模 7 有多组解」等价于「天数有多组解」，余数可唯一还原成天数；
//   - 7 是素数，Z_7 是域，除法换成乘逆元即可照搬高斯消元。

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>

typedef long long ll;

const int MAXN = 305;   // 型号数 n <= 300
const int MAXM = 305;   // 记录数 m <= 300
const int MOD = 7;      // 一周 7 天，方程都在模 7 意义下

// 模 7 的乘法逆元：1->1, 2->4, 3->5, 4->2, 5->3, 6->6（2*4、3*5、6*6 都 ≡ 1）
const int INV[MOD] = {0, 1, 4, 5, 2, 3, 6};

// 星期字符串转 0..6：day_num("MON") = 0, ..., day_num("SUN") = 6
int day_num(const char *s) {
    const char *DAYS[MOD] = {"MON", "TUE", "WED", "THU", "FRI", "SAT", "SUN"};
    for (int i = 0; i < MOD; ++i)
        if (strcmp(s, DAYS[i]) == 0)
            return i;
    return -1; // 题面保证输入合法，不会走到这里
}

// 系数矩阵与右端向量：a[i][j] 是第 i 条方程里 x_j 的系数（已对 7 取余）
ll a[MAXM][MAXN];
ll b[MAXM];  // b[i] = 第 i 条方程的右端 d_i mod 7
ll x[MAXN];  // 唯一解时每个型号的耗时（余数形式，0..6）
ll cnt[MAXN]; // 读记录时的临时计数：cnt[j] = 型号 j 在本条记录出现的次数

int n, m;

// 读入一条记录并转成一条方程：sum_j c[j] * x_j ≡ e - s + 1 (mod 7)
bool read_record(int i) {
    ll k;
    char s1[10], s2[10];
    if (scanf("%lld %9s %9s", &k, s1, s2) != 3)
        return false;
    for (int j = 1; j <= n; ++j) cnt[j] = 0; // 只清这题会用到的下标范围
    for (ll t = 0; t < k; ++t) {
        int v;
        scanf("%d", &v);
        cnt[v]++; // 同型号出现 c 次，耗时累加 c 次，系数就是 c
    }
    for (int j = 1; j <= n; ++j)
        a[i][j] = cnt[j] % MOD;
    // 在岗天数首尾都算，右端是 (收工 - 开工 + 1) mod 7
    b[i] = ((day_num(s2) - day_num(s1) + 1) % MOD + MOD) % MOD;
    return true;
}

// 模 7 高斯消元（7 是素数，非零系数都有逆元）
// 返回值：0 = 唯一解，1 = 多解，2 = 无解；唯一解时结果存入 x[]
int gauss() {
    int r = 0; // 已处理的主元行数（也是当前的秩）
    for (int col = 1; col <= n && r < m; ++col) {
        int p = -1; // 在 r..m-1 行里找这一列系数非 0 的主元行
        for (int i = r; i < m; ++i)
            if (a[i][col] != 0) { p = i; break; }
        if (p == -1)
            continue; // 这一列全是 0，x[col] 是自由元
        // 把主元行换上来
        for (int j = col; j <= n; ++j) {
            ll t = a[r][j]; a[r][j] = a[p][j]; a[p][j] = t;
        }
        ll tb = b[r]; b[r] = b[p]; b[p] = tb;
        // 主元归一化成 1：整行乘主元的逆元
        ll inv = INV[a[r][col]];
        for (int j = col; j <= n; ++j)
            a[r][j] = a[r][j] * inv % MOD;
        b[r] = b[r] * inv % MOD;
        // 用主元行把它下方各行消成 0（只往下消，回代时再算具体值）
        for (int i = r + 1; i < m; ++i) {
            ll f = a[i][col];
            if (f == 0) continue;
            for (int j = col; j <= n; ++j)
                a[i][j] = (a[i][j] - f * a[r][j] % MOD + MOD) % MOD;
            b[i] = (b[i] - f * b[r] % MOD + MOD) % MOD;
        }
        r++; // 主元个数增加
    }
    // 消元后第 r..m-1 行的系数已全为 0，检查有没有 0 ≡ c (c ≠ 0) 的矛盾行
    for (int i = r; i < m; ++i)
        if (b[i] != 0)
            return 2; // Inconsistent data.
    if (r < n)
        return 1;     // 有自由元，自由元取 0 就是一组解，故天数不唯一
    // 满秩，逆序回代求出每个 x[j]
    for (int i = r - 1; i >= 0; --i) {
        // 找到这一行的主元列
        int col = 1;
        while (col <= n && a[i][col] == 0) col++;
        x[col] = b[i];
        for (int j = col + 1; j <= n; ++j)
            x[col] = (x[col] - a[i][j] * x[j] % MOD + MOD) % MOD;
    }
    return 0;
}

// 处理一组测试用例，返回 false 表示读到 n = m = 0 的结束标记
bool solve_case() {
    if (scanf("%d %d", &n, &m) != 2)
        return false;
    if (n == 0 && m == 0)
        return false;
    for (int i = 0; i < m; ++i)
        read_record(i);
    int st = gauss();
    if (st == 2) {
        printf("Inconsistent data.\n");
    } else if (st == 1) {
        printf("Multiple solutions.\n");
    } else {
        // 余数 0/1/2 对应 7/8/9 天，其余直接就是天数
        for (int j = 1; j <= n; ++j) {
            ll d = x[j] < 3 ? x[j] + MOD : x[j];
            printf("%lld%c", d, j == n ? '\n' : ' ');
        }
    }
    return true;
}

int main() {
    while (solve_case())
        ;
    return 0;
}
