/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */
// 石子合并：区间 DP，按区间长度从小到大递推。
#include <cstdio>
#include <vector>

typedef long long ll;

const ll MAXN = 1005;

ll n;
ll stone[MAXN];
ll ps[MAXN];  // ps[i] = 前 i 堆的质量和
ll f[MAXN][MAXN]; // f[i][j]：把区间 [i, j] 合并成一堆的最小代价

int main() {
    if (scanf("%lld", &n) != 1) return 0; // 空输入安全返回
    for (ll i = 0; i < n; i++) scanf("%lld", &stone[i]);
    ps[0] = 0;
    for (ll i = 0; i < n; i++) ps[i + 1] = ps[i] + stone[i];

    for (ll length = 2; length <= n; length++) {
        for (ll i = 0; i + length - 1 < n; i++) {
            ll j = i + length - 1;
            ll best = -1; // 只作内层取最小值的初始上界
            for (ll k = i; k < j; k++) {
                ll cost = f[i][k] + f[k + 1][j]; // 左段代价 + 右段代价
                if (best < 0 || cost < best) best = cost;
            }
            f[i][j] = best + ps[j + 1] - ps[i]; // 补上最后一次合并自身的代价
        }
    }
    printf("%lld\n", f[0][n - 1]); // n = 1 时就是 0：只有一堆
    return 0;
}
