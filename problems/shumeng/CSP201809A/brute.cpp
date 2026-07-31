/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:54
 */
// brute.cpp：按每家店可见的相邻范围逐项求平均值。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> price(n);
    for (int i = 0; i < n; i++) {
        cin >> price[i];
    }

    for (int i = 0; i < n; i++) {
        int sum = 0;
        int count = 0;
        for (int j = max(0, i - 1); j <= min(n - 1, i + 1); j++) {
            sum += price[j];
            count++;
        }
        if (i > 0) {
            cout << ' ';
        }
        cout << sum / count;
    }
    cout << '\n';

    return 0;
}
