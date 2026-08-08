#include <bits/stdc++.h>
using namespace std;

// brute.cpp：每个询问直接统计颜色次数并计算概率，只适合小数据。

const int MAXN = 505;

int n, m;
int color[MAXN];
long long cnt[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        for (int c = 0; c <= n; c++) {
            cnt[c] = 0;
        }
        for (int j = l; j <= r; j++) {
            cnt[color[j]]++;
        }
        long long same = 0;
        long long len = r - l + 1;
        for (int c = 1; c <= n; c++) {
            same += cnt[c] * (cnt[c] - 1) / 2;
        }
        if (len == 1) {
            cout << "0/1\n";
        } else {
            long long total = len * (len - 1) / 2;
            long long g = gcd(same, total);
            cout << same / g << '/' << total / g << '\n';
        }
    }

    return 0;
}
