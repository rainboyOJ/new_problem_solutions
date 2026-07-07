// brute.cpp：小数据暴力解，使用 01 序列枚举每个愿望做或不做。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;                       // 愿望数量
int limit_money, limit_time; // 可用资源上限
int cost_money[MAXN];        // 每个愿望需要的金钱
int cost_time[MAXN];         // 每个愿望需要的时间
int choose_wish[MAXN];       // choose_wish[i] = 0/1，表示第 i 个愿望不做/做
int best_answer;             // 当前找到的最优答案

bool check() {
    int used_money = 0;
    int used_time = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_wish[i] == 1) {
            used_money += cost_money[i];
            used_time += cost_time[i];
        }
    }
    return used_money <= limit_money && used_time <= limit_time;
}

int calc_answer() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_wish[i] == 1) cnt++;
    }
    return cnt;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (best_answer < value) best_answer = value;
        }
        return;
    }

    // 第 dep 个愿望的 01 选择：0 不做，1 做。
    for (int i = 0; i <= 1; i++) {
        choose_wish[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> limit_money >> limit_time;
    for (int i = 1; i <= n; i++) {
        cin >> cost_money[i] >> cost_time[i];
    }

    best_answer = 0;
    dfs_choose(1);

    cout << best_answer << '\n';
    return 0;
}
