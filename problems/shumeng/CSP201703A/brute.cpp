/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:40
 */
// brute.cpp：按题意逐个朋友、逐块蛋糕模拟分配过程。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, k;
    cin >> n >> k;
    vector<int> cake(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> cake[i];
    }

    int position = 1;
    int answer = 0;
    while (position <= n) {
        int current_weight = 0;
        answer++;
        while (position <= n && current_weight < k) {
            current_weight += cake[position];
            position++;
        }
    }
    cout << answer << '\n';

    return 0;
}
