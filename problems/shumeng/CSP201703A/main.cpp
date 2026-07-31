/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:40
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    int current_weight = 0;
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        int cake_weight;
        cin >> cake_weight;
        current_weight += cake_weight;
        if (current_weight >= k) {
            answer++;
            current_weight = 0;
        }
    }
    // 最后一个朋友即使没有拿到 k 重量，也会拿走全部剩余蛋糕。
    if (current_weight > 0) {
        answer++;
    }
    cout << answer << '\n';

    return 0;
}
