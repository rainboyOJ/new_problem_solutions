/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-05 09:50
 * update_at: 2026-08-05 09:50
 */
// brute.cpp：小数据暴力解，直接生成所有 N² 个和并排序取前 N 个。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<long long> a(n), b(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    for (int i = 0; i < n; i++) cin >> b[i];

    // 生成所有 N² 个和
    vector<long long> sums;
    sums.reserve(n * n);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            sums.push_back(a[i] + b[j]);

    sort(sums.begin(), sums.end());

    // 输出前 N 个最小的和
    for (int i = 0; i < n; i++) {
        if (i) cout << " ";
        cout << sums[i];
    }
    cout << "\n";

    return 0;
}
