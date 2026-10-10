/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 13:00
 * update_at: 2026-10-10 13:00
 */

// 邮局：DP + 分治优化（代价满足四边形不等式，最优分割点单调）
#include <cstdio>
#include <vector>
#include <algorithm>
using namespace std;

typedef long long ll;

const ll INF = 1000000000000000000LL;

int n, p;
vector<ll> xs;  // 排好序的村庄坐标
vector<ll> pre; // pre[i] = 前 i 个村庄的坐标和
vector<ll> dp, ndp;

// 把村庄 l..r（下标闭区间）全交给一个邮局时的最小距离和，建在中位数上最优
ll segment_cost(int l, int r) {
    if (l > r) {
        return 0;
    }
    int mid = (l + r) / 2;
    ll c = xs[mid];
    ll left = c * (mid - l + 1) - (pre[mid + 1] - pre[l]);
    ll right = (pre[r + 1] - pre[mid + 1]) - c * (r - mid);
    return left + right;
}

// 算 ndp[lo..hi]，已知这些位置的最优分割点都落在 [opt_lo, opt_hi]
void fill_range(int lo, int hi, int opt_lo, int opt_hi) {
    if (lo > hi) {
        return;
    }
    int mid = (lo + hi) / 2;
    ll best = INF;
    int best_j = opt_lo;
    int lim = min(mid - 1, opt_hi);
    for (int j = opt_lo; j <= lim; j++) {
        ll v = dp[j] + segment_cost(j, mid - 1);
        if (v < best) {
            best = v;
            best_j = j;
        }
    }
    ndp[mid] = best;
    fill_range(lo, mid - 1, opt_lo, best_j); // 左半边的最优分割点不超过 mid 的
    fill_range(mid + 1, hi, best_j, opt_hi); // 右半边的最优分割点不小于 mid 的
}

int main() {
    if (scanf("%d %d", &n, &p) != 2) {
        return 0;
    }
    xs.assign(n, 0);
    for (int i = 0; i < n; i++) {
        scanf("%lld", &xs[i]);
    }
    sort(xs.begin(), xs.end()); // 邮局只关心相对顺序
    pre.assign(n + 1, 0);
    for (int i = 0; i < n; i++) {
        pre[i + 1] = pre[i] + xs[i];
    }

    if (p >= n) { // 邮局够多，每个村庄都建一个
        printf("0\n");
        return 0;
    }

    dp.assign(n + 1, INF);
    dp[0] = 0; // 0 个邮局：只有“前 0 个村庄”代价为 0
    for (int k = 1; k <= p; k++) {
        ndp.assign(n + 1, INF);
        fill_range(k, n, k - 1, n - 1);
        dp = ndp;
    }
    printf("%lld\n", dp[n]);
    return 0;
}
