/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-27 00:00
 * update_at: 2026-07-27 00:00
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20005;

int n, target;
int h[MAXN]; // 奶牛身高

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> target;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }

    // 从高到低排序
    sort(h, h + n, greater<int>());

    int sum = 0;
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        sum += h[i];
        cnt++;
        if (sum >= target) break;
    }

    cout << cnt << "\n";

    return 0;
}
