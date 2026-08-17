/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:43
 */
#include <bits/stdc++.h>
using namespace std;

const int MAX_VALUE = 10000;

int n;
int cnt[MAX_VALUE + 1]; // cnt[x] 表示数字 x 出现的次数

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x;
        cin >> x;
        cnt[x]++;
    }

    int answer = 0;
    int best_count = 0;
    // 从小到大扫描，出现次数相同时较小的数先被记录，保证答案最小。
    for (int value = 1; value <= MAX_VALUE; value++) {
        if (cnt[value] > best_count) {
            best_count = cnt[value];
            answer = value;
        }
    }

    cout << answer << '\n';
    return 0;
}
