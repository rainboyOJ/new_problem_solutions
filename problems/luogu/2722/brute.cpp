#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，把每种题目选多少道看成计数选择序列。

const int MAXN = 10005;

int t, n;
int cost[MAXN];
int points[MAXN];
int choose_count[MAXN]; // choose_count[i] 表示第 i 种题目选多少道
int answer;

bool check() {
    int used_time = 0;
    for (int i = 1; i <= n; i++) {
        used_time += choose_count[i] * cost[i];
    }
    return used_time <= t;
}

int calc_answer() {
    int total_score = 0;
    for (int i = 1; i <= n; i++) {
        total_score += choose_count[i] * points[i];
    }
    return total_score;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (answer < value) answer = value;
        }
        return;
    }

    // 第 dep 种题目可以选 0..t/cost[dep] 道。
    int limit = t / cost[dep];
    for (int cnt = 0; cnt <= limit; cnt++) {
        choose_count[dep] = cnt;
        dfs_choose(dep + 1);
    }
}

void read_input() {
    cin >> t >> n;
    for (int i = 1; i <= n; i++) {
        cin >> points[i] >> cost[i];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    dfs_choose(1);
    cout << answer << '\n';

    return 0;
}
