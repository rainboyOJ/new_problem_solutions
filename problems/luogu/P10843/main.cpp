/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:01
 * update_at: 2026-08-14 16:40
 */
// P10843 【MX-J2-T4】Turtle and Cycles
// 操作 a[i] <- a[i-1]+a[i+1]-a[i] 等价于交换环上相邻差分 b[i-1] 与 b[i]。
// "好位置" = 差分符号序列中正差分段数 = 峰数；目标是恰好 1 个峰，
// 即把正差分在环上聚成一段，求最小相邻交换次数。
// 展开正差分位置 pos（升序、复制一份加 n），枚举聚段起点 i：
// 代价 = Σ|(pos[k]-k) - 中位数|，用前缀和 O(1) 求，取所有 i 的最小值。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;

int n;
int a[MAXN];  // 环形排列

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        // 差分数组 b[i] = a[i+1] - a[i]（环形），正差分的位置
        vector<int> pos;
        for (int i = 0; i < n; i++) {
            if (a[(i + 1) % n] > a[i]) pos.push_back(i);
        }
        int p = (int)pos.size();
        if (p <= 1) {
            cout << 0 << '\n'; // 没有正差分段需要合并
            continue;
        }

        // 复制一份 pos + n，并把 x[j] = pos[j] - j 弄成单调不减
        vector<int> pos2(2 * p);
        for (int i = 0; i < p; i++) {
            pos2[i] = pos[i];
            pos2[i + p] = pos[i] + n;
        }
        vector<long long> x(2 * p), pref(2 * p + 1, 0);
        for (int i = 0; i < 2 * p; i++) {
            x[i] = pos2[i] - i;
            pref[i + 1] = pref[i] + x[i];
        }

        // 枚举聚段起点：正差分 pos[i..i+p-1] 聚成连续 p 个位置
        long long ans = LLONG_MAX;
        int mid_off = (p - 1) / 2; // 子序列中的中位数偏移
        for (int i = 0; i < p; i++) {
            int m = i + mid_off;      // 中位数的绝对下标
            long long med = x[m];     // 中位数
            // Σ_{k=i}^{i+p-1} |x[k] - med|：前缀和拆成左右两半
            long long left = (long long)(m - i + 1) * med - (pref[m + 1] - pref[i]);
            long long right = (pref[i + p] - pref[m + 1]) - (long long)(p - 1 - (m - i)) * med;
            ans = min(ans, left + right);
        }

        cout << ans << '\n';
    }

    return 0;
}
