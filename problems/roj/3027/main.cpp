/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:54
 * update_at: 2026-10-06 14:54
 */

#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 10005;

ll xs[MAXN]; // 士兵的 x 坐标，排序后按第 i 小的人领第 i 个格子错位
ll ys[MAXN]; // 士兵的 y 坐标

// 把这些数平移到同一个点，最小的总距离 = 各点到中位数的绝对距离之和。
// 数组按 a[1..n] 存储，调用时会被就地排序。
ll median_cost(ll a[], int n) {
    sort(a + 1, a + n + 1);
    ll median = a[n / 2 + 1]; // 下标从 1 开始的中位数位置
    ll total = 0;
    for (int i = 1; i <= n; i++) {
        ll diff = a[i] - median;
        if (diff < 0) {
            diff = -diff;
        }
        total += diff;
    }
    return total;
}

int main() {
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld %lld", &xs[i], &ys[i]);
    }

    // x 轴：目标是 n 个相邻格子 X, X+1, ..., X+n-1。
    // 排序后第 i 小的人领第 i 个格子，于是把偏移 i-1 提前扣掉，再对 X 取中位数。
    sort(xs + 1, xs + n + 1);
    for (int i = 1; i <= n; i++) {
        xs[i] -= (i - 1);
    }
    ll x_cost = median_cost(xs, n);

    // y 轴：全部站到同一行 Y，取 y 的中位数即可。
    ll y_cost = median_cost(ys, n);

    printf("%lld\n", x_cost + y_cost);
    return 0;
}
