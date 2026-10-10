/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 能量项链：环拆链 + 区间 DP
#include <cstdio>
using namespace std;

typedef long long ll;

const int MAXS = 1024; // 2N 的上界

ll a[MAXS];           // 环复制一倍后的标记序列
// f[i][j]：把 a[i..j] 这串连续珠子聚成一颗时释放的最大能量
ll f[MAXS][MAXS];

int main() {
    int n;
    if (scanf("%d", &n) != 1) {
        return 0;
    }
    for (int i = 0; i < n; i++) {
        scanf("%lld", &a[i]);
        a[i + n] = a[i];
    }
    int size = 2 * n;

    for (int length = 2; length <= n; length++) { // 长度超过 n 的区间不是环上的连续段
        for (int i = 0; i + length - 1 < size - 1; i++) { // 右端留一个 a[j+1] 当尾标记
            int j = i + length - 1;
            ll head = a[i], tail = a[j + 1];
            ll best = 0;
            for (int k = i; k < j; k++) { // 最后一步：[i,k] 与 [k+1,j] 各自的珠子再聚合
                ll energy = f[i][k] + f[k + 1][j] + head * a[k + 1] * tail;
                if (energy > best) {
                    best = energy;
                }
            }
            f[i][j] = best;
        }
    }

    ll ans = 0; // 环上每种起点都对应一个长度为 n 的区间
    for (int i = 0; i < n; i++) {
        if (f[i][i + n - 1] > ans) {
            ans = f[i][i + n - 1];
        }
    }
    printf("%lld\n", ans);
    return 0;
}
