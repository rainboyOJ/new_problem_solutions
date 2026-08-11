/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-11 10:05
 */
// brute.cpp：小数据暴力解，直接枚举所有区间并计算 mex 与补区间最小值。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 305;
const int INF = 1000000000;

int n;
int a[MAXN];
int used[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) cin >> a[i];

    long long ans = 0;
    for (int l = 1; l <= n; l++) {
        for (int r = l; r <= n; r++) {
            for (int i = 0; i <= n + 1; i++) used[i] = 0;
            for (int i = l; i <= r; i++) {
                if (a[i] <= n + 1) used[a[i]] = 1;
            }

            int mex_value = 0;
            while (used[mex_value]) mex_value++;

            int cmin = INF;
            for (int i = 1; i < l; i++) cmin = min(cmin, a[i]);
            for (int i = r + 1; i <= n; i++) cmin = min(cmin, a[i]);

            if (mex_value == cmin) ans++;
        }
    }

    cout << ans << '\n';
    return 0;
}
