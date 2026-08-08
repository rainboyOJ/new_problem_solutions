#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int INF = 1e9;

int n;
int t1[MAXN], t2[MAXN], t3[MAXN];
int answer;

void dfs(int idx, int sum_a, int sum_b) {
    if (idx > n) {
        answer = min(answer, max(sum_a, sum_b));
        return;
    }

    if (t1[idx] > 0) {
        dfs(idx + 1, sum_a + t1[idx], sum_b);
    }
    if (t2[idx] > 0) {
        dfs(idx + 1, sum_a, sum_b + t2[idx]);
    }
    if (t3[idx] > 0) {
        dfs(idx + 1, sum_a + t3[idx], sum_b + t3[idx]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
    // 每个任务枚举三种可用加工方式：
    // 只给 A、只给 B、或者 A/B 同时做。
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> t1[i] >> t2[i] >> t3[i];
    }

    answer = INF;
    dfs(1, 0, 0);
    cout << answer << '\n';
    return 0;
}
