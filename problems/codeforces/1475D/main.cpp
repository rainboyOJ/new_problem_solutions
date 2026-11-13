/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-13 09:10
 * update_at: 2026-11-13 09:10
 */
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int maxn = 200000 + 50;
const long long INF = 1e18;

// 全局静态数组，避免多测频繁动态内存申请
long long a[maxn];
int b[maxn];

long long one[maxn];       // 代价为 1 的应用空间
long long two[maxn];       // 代价为 2 的应用空间
long long sum_one[maxn];   // 代价为 1 的前缀和
long long sum_two[maxn];   // 代价为 2 的前缀和

void solve() {
    int n;
    long long m;
    if (!(cin >> n >> m)) return;

    for (int i = 1; i <= n; ++i) cin >> a[i];
    for (int i = 1; i <= n; ++i) cin >> b[i];

    int cnt1 = 0, cnt2 = 0;
    for (int i = 1; i <= n; ++i) {
        if (b[i] == 1) {
            one[++cnt1] = a[i];
        } else {
            two[++cnt2] = a[i];
        }
    }

    // 内部贪心：同等代价下优先选择释放空间最大的应用
    sort(one + 1, one + cnt1 + 1, greater<long long>());
    sort(two + 1, two + cnt2 + 1, greater<long long>());

    sum_one[0] = 0;
    for (int i = 1; i <= cnt1; ++i) {
        sum_one[i] = sum_one[i - 1] + one[i];
    }

    sum_two[0] = 0;
    for (int i = 1; i <= cnt2; ++i) {
        sum_two[i] = sum_two[i - 1] + two[i];
    }

    // 全部应用释放后仍达不到目标空间，直接无解
    if (sum_one[cnt1] + sum_two[cnt2] < m) {
        cout << -1 << "\n";
        return;
    }

    // 解法 1：双指针扫描
    // 当 x 递增时，队伍 A 贡献的空间递增，队伍 B 所需的最小数量 y 单调递减
    long long ans = INF;
    int y = cnt2;

    for (int x = 0; x <= cnt1; ++x) {
        // 在总释放空间满足 >= m 的前提下，尽量让 y 向左收缩
        while (y > 0 && sum_one[x] + sum_two[y - 1] >= m) {
            y--;
        }
        if (sum_one[x] + sum_two[y] >= m) {
            ans = min(ans, (long long)x + 2LL * y);
        }
    }

    cout << ans << "\n";
}

int main() {
    // 提升标准输入输出流性能
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
