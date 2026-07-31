/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 16:22
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int cnt[10005] = {};
    cin >> n;

    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    int answer = 1;
    int best_count = 0;
    // 从小到大扫描，出现次数相同时自然保留较小的数。
    for (int value = 1; value <= 10000; value++) {
        if (cnt[value] > best_count) {
            best_count = cnt[value];
            answer = value;
        }
    }

    cout << answer << '\n';
    return 0;
}
