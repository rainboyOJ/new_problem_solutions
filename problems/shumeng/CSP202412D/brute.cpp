/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 02:19
 */
// brute.cpp：小数据暴力解，BFS 中直接枚举当前状态能跳到的所有落点。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> a(n + 1);
    vector<long long> k(n + 1);
    for (int i = 1; i <= n; i++) cin >> a[i];
    for (int i = 1; i <= n; i++) cin >> k[i];

    vector<int> distance_to(n + 1, -1);
    queue<int> states;
    distance_to[1] = 0;
    states.push(1);

    while (!states.empty()) {
        int current = states.front();
        states.pop();
        long long right = min((long long)n, current + k[current]);
        for (int landing = current + 1; landing <= right; landing++) {
            int next_state = landing - a[landing];
            if (distance_to[next_state] == -1) {
                distance_to[next_state] = distance_to[current] + 1;
                states.push(next_state);
            }
        }
    }

    cout << distance_to[n] << '\n';
    return 0;
}
