/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:54
 */
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

    vector<int> next_price(n);
    next_price[0] = (price[0] + price[1]) / 2;
    for (int i = 1; i + 1 < n; i++) {
        next_price[i] = (price[i - 1] + price[i] + price[i + 1]) / 3;
    }
    next_price[n - 1] = (price[n - 2] + price[n - 1]) / 2;

    for (int i = 0; i < n; i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << next_price[i];
    }
    cout << '\n';

    return 0;
}
