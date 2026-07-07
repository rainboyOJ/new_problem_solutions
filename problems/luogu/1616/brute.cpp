#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。

const int MAXN = 10005;

int t, m;
int cost[MAXN];
int value[MAXN];
int choose_count[MAXN]; // choose_count[i] 表示第 i 种草药取多少次
long long answer;

bool check() {
    int used_time = 0;
    for (int i = 1; i <= m; i++) {
        used_time += choose_count[i] * cost[i];
    }
    return used_time <= t;
}

long long calc_answer() {
    long long total_value = 0;
    for (int i = 1; i <= m; i++) {
        total_value += 1LL * choose_count[i] * value[i];
    }
    return total_value;
}

// 依次枚举每种草药可以取多少次，叶子节点统一检查总时间。
void dfs_choose(int dep) {
    if (dep == m + 1) {
        if (check()) {
            long long current_value = calc_answer();
            if (answer < current_value) answer = current_value;
        }
        return;
    }

    int limit = t / cost[dep];
    for (int cnt = 0; cnt <= limit; cnt++) {
        choose_count[dep] = cnt;
        dfs_choose(dep + 1);
    }
}

void read_input() {
    cin >> t >> m;
    for (int i = 1; i <= m; i++) {
        cin >> cost[i] >> value[i];
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
