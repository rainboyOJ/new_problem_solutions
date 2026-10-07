/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:54
 * update_at: 2026-10-06 13:54
 */
#include <iostream>
using namespace std;

const int MAXN = 100005;

typedef long long ll;

ll n, f;
ll a[MAXN];        // a[i] 表示第 i 块地里的牛的数量
double sum[MAXN];  // sum[i] 表示前 i 项的 (a[i] - mid) 前缀和，随二分基准 mid 变化

// 判断平均值能否达到 mid，即是否存在长度不小于 f 且总和非负的连续子段。
bool check(double mid) {
    sum[0] = 0.0;
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + a[i] - mid;
    }

    // 固定右端点 r，合法左端点前缀下标 p = l - 1 满足 0 <= p <= r - f。
    // min_sum 维护这些 p 中 sum[p] 的最小值，若 sum[r] >= min_sum 则说明存在合法子段。
    double min_sum = 0.0;
    for (int r = f; r <= n; r++) {
        int p = r - f;
        if (sum[p] < min_sum) {
            min_sum = sum[p];
        }
        if (sum[r] >= min_sum) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> f;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    // 二分最大平均值：平均值可达 mid 具有单调性，左侧可行则抬高下界。
    double left = 0.0;
    double right = 2000.0;
    while (right - left > 1e-5) {
        double mid = (left + right) / 2.0;
        if (check(mid)) {
            left = mid;
        } else {
            right = mid;
        }
    }

    // right 始终略大于真实最大值，乘 1000 后向下取整即为答案。
    ll ans = (ll)(right * 1000);
    cout << ans << "\n";

    return 0;
}
