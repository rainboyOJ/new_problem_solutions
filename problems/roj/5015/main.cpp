/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2024-12-08 19:30
 * update_at: 2026-10-08 21:07
 */
// 5015 子集：价值 = 平均数 - 中位数，最大化该价值。
// 最优子集大小必为奇数 2k+1（偶数大小去掉中心两个之一不会更差），
// 故升序排序后枚举中位数 a[i]，以它为中位数时左侧取紧邻的 k 个、右侧取最大的 k 个，
// 价值关于 k 单峰，用三分法求峰；比较全程交叉相乘避免浮点误差。
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;
const int MAXN = 200005;

int n;
ll a[MAXN];    // a[1..n]：升序排序后的数组
ll pref[MAXN]; // pref[i] = a[1..i] 的前缀和

// 以 a[i] 为中位数、左侧取紧邻的 k 个、右侧取最大的 k 个时，子集的元素和
ll subset_sum(int i, int k) {
    return (pref[i] - pref[i - k - 1]) + (pref[n] - pref[n - k]);
}

void solve() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    sort(a + 1, a + n + 1);
    for (int i = 1; i <= n; i++) {
        pref[i] = pref[i - 1] + a[i];
    }

    ll best_num = 0; // 最优价值 = best_num / best_den，初值 0/1（单元素子集价值为 0）
    ll best_den = 1;

    for (int i = 1; i <= n; i++) {
        int l = 0;                      // k 的下界
        int r = min(i - 1, n - i);      // k 的上界：两边都要够取

        // 对 k 三分：平均数 S(k)/(2k+1) 关于 k 单峰，交叉相乘作整数比较
        while (l < r - 2) {
            int m1 = l + (r - l) / 3;
            int m2 = r - (r - l) / 3;

            ll s1 = subset_sum(i, m1);
            ll s2 = subset_sum(i, m2);

            if (s1 * (2 * m2 + 1) < s2 * (2 * m1 + 1)) {
                l = m1;
            } else {
                r = m2;
            }
        }

        // 三分收敛后区间只剩极小一段，逐个 k 比较价值（同样交叉相乘）
        for (int k = l; k <= r; k++) {
            ll s = subset_sum(i, k);
            ll num = s - a[i] * (2 * k + 1); // 价值 = (s - (2k+1)*a[i]) / (2k+1)
            ll den = 2 * k + 1;

            if (best_num * den < num * best_den) {
                best_num = num;
                best_den = den;
            }
        }
    }

    printf("%.5f\n", 1.0 * best_num / best_den);
}

int main() {
    solve();
    return 0;
}
