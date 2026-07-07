// brute.cpp：小数据暴力解，使用 01 序列枚举每株草药选或不选。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1005;

int total_time;         // 总可用时间
int herb_count;         // 草药数量
int need_time[MAXM];    // 每株草药需要的时间
int herb_value[MAXM];   // 每株草药的价值
int choose_herb[MAXM];  // choose_herb[i] = 0/1，表示第 i 株草药不采/采
int best_answer;        // 当前找到的最大总价值

bool check() {
    int used_time = 0;
    for (int i = 1; i <= herb_count; i++) {
        if (choose_herb[i] == 1) used_time += need_time[i];
    }
    return used_time <= total_time;
}

int calc_answer() {
    int total_value = 0;
    for (int i = 1; i <= herb_count; i++) {
        if (choose_herb[i] == 1) total_value += herb_value[i];
    }
    return total_value;
}

void dfs_choose(int dep) {
    if (dep == herb_count + 1) {
        if (check()) {
            int value = calc_answer();
            if (best_answer < value) best_answer = value;
        }
        return;
    }

    // 第 dep 株草药的 01 选择：0 不采，1 采。
    for (int i = 0; i <= 1; i++) {
        choose_herb[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> total_time >> herb_count;
    for (int i = 1; i <= herb_count; i++) {
        cin >> need_time[i] >> herb_value[i];
    }

    best_answer = 0;
    dfs_choose(1);

    cout << best_answer << '\n';
    return 0;
}
