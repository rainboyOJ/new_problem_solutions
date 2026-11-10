/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-11 00:38
 * update_at: 2026-11-11 00:38
 */
// brute.cpp：小规模系数下，直接使用普通整数求值判断
#include <iostream>
#include <vector>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    if (!(cin >> n >> m)) return 0;

    vector<long long> a(n + 1);
    for (int i = 0; i <= n; ++i) {
        cin >> a[i];
    }

    vector<int> ans;
    for (int x = 1; x <= m; ++x) {
        long long val = 0;
        long long xp = 1;
        for (int i = 0; i <= n; ++i) {
            val += a[i] * xp;
            xp *= x;
        }
        if (val == 0) {
            ans.push_back(x);
        }
    }

    cout << ans.size() << "\n";
    for (int x : ans) {
        cout << x << "\n";
    }

    return 0;
}
