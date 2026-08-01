/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 09:20
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int n, m;
vector<long long> happiness;

long long dfs(int remaining) {
    if (remaining == 0) return 0;

    long long answer = -(1LL << 60);
    for (int today = 1; today <= min(m, remaining); today++) {
        answer = max(answer, happiness[today] + dfs(remaining - today));
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    happiness.assign(m + 1, 0);
    for (int i = 1; i <= m; i++) cin >> happiness[i];
    cout << dfs(n) << '\n';
    return 0;
}
