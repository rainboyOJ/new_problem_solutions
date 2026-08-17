/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:43
 */
// brute.cpp：小数据暴力解，逐个统计每个数在整个数组中出现了几次。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    int a[1005];
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    int answer = 1000000000;
    int best_count = 0;
    // 枚举候选数 a[i]，再扫描整个数组求它的出现次数。
    for (int i = 1; i <= n; i++) {
        int current_count = 0;
        for (int j = 1; j <= n; j++) {
            if (a[j] == a[i]) {
                current_count++;
            }
        }
        if (current_count > best_count ||
            (current_count == best_count && a[i] < answer)) {
            best_count = current_count;
            answer = a[i];
        }
    }

    cout << answer << '\n';
    return 0;
}
