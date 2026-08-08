#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，使用 01 序列枚举每道题做或不做。

const int MAXN = 105;
const int MAXM = 105;

int wky_skill, wang_skill;
int m, n, limit_time;
int topic_time[MAXN]; // 老王做知识点 i 的题需要的时间
int cost[MAXM];       // WKY 做第 i 道题需要的时间
int reward_value[MAXM];
int choose_problem[MAXM]; // choose_problem[i] = 0/1，表示第 i 道题不做/做
int answer;

bool check() {
    int used_time = 0;
    for (int i = 1; i <= m; i++) {
        if (choose_problem[i] == 1) used_time += cost[i];
    }
    return used_time <= limit_time;
}

int calc_answer() {
    int total_reward = 0;
    for (int i = 1; i <= m; i++) {
        if (choose_problem[i] == 1) total_reward += reward_value[i];
    }
    return total_reward;
}

void dfs_choose(int dep) {
    if (dep == m + 1) {
        if (check()) {
            int value = calc_answer();
            if (answer < value) answer = value;
        }
        return;
    }

    // 第 dep 道题的 01 选择：0 不做，1 做。
    for (int i = 0; i <= 1; i++) {
        choose_problem[dep] = i;
        dfs_choose(dep + 1);
    }
}

void read_input() {
    cin >> wky_skill >> wang_skill;
    cin >> m >> n;
    for (int i = 1; i <= n; i++) {
        cin >> topic_time[i];
    }

    int ratio = wang_skill / wky_skill;
    for (int i = 1; i <= m; i++) {
        int p, q;
        cin >> p >> q;
        cost[i] = topic_time[p] * ratio;
        reward_value[i] = q;
    }
    cin >> limit_time;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    dfs_choose(1);
    cout << answer << '\n';

    return 0;
}
