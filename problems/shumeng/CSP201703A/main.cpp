/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:48
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;

    int current_weight = 0; // 当前这位朋友已拿到的总重量
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        int cake_weight;
        cin >> cake_weight;
        current_weight += cake_weight;
        // 累计达到 k 后结束当前朋友，从下一位朋友重新开始累计
        if (current_weight >= k) {
            answer++;
            current_weight = 0;
        }
    }
    // 蛋糕全部分完时，最后一位朋友即使拿到的重量不足 k，也带走了剩余蛋糕
    if (current_weight > 0) {
        answer++;
    }
    cout << answer << '\n';

    return 0;
}