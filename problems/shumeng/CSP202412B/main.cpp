/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long a[MAXN], b[MAXN];
long long base[MAXN];
long long prefix_maximum[MAXN];
long long suffix_maximum[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> b[i];

    // base[j] 是正常补给下，为了通过第 j 段移动所需的初始能量下界。
    long long total_a = 0;
    long long total_b = 0;
    for (int j = 0; j <= n; j++) {
        total_a += a[j];
        if (j >= 1) total_b += b[j];
        base[j] = total_a - total_b;
    }

    prefix_maximum[0] = base[0];
    for (int j = 1; j <= n; j++) {
        prefix_maximum[j] = max(prefix_maximum[j - 1], base[j]);
    }

    suffix_maximum[n] = base[n];
    for (int j = n - 1; j >= 0; j--) {
        suffix_maximum[j] = max(suffix_maximum[j + 1], base[j]);
    }

    for (int i = 1; i <= n; i++) {
        // 失效补给只会影响第 i 段及之后的约束，之前的约束保持不变。
        long long before_failure = prefix_maximum[i - 1];
        long long after_failure = b[i] + suffix_maximum[i];
        if (i > 1) cout << ' ';
        cout << max(before_failure, after_failure);
    }
    cout << '\n';

    return 0;
}
