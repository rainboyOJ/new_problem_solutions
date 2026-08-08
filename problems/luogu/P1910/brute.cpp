// brute.cpp：小数据暴力解，使用 01 序列枚举每个间谍派或不派。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
int limit_detect;          // 总探查风险上限
int limit_money;           // 总工资上限
int info_value[MAXN];      // 资料量
int detect_cost[MAXN];     // 探查风险
int money_cost[MAXN];      // 工资
int choose_spy[MAXN];      // choose_spy[i] = 0/1，表示第 i 个间谍不派/派
int best_answer;           // 当前找到的最大资料量

bool check() {
    int used_detect = 0;
    int used_money = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_spy[i] == 1) {
            used_detect += detect_cost[i];
            used_money += money_cost[i];
        }
    }
    return used_detect <= limit_detect && used_money <= limit_money;
}

int calc_answer() {
    int total_info = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_spy[i] == 1) total_info += info_value[i];
    }
    return total_info;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (best_answer < value) best_answer = value;
        }
        return;
    }

    // 第 dep 个间谍的 01 选择：0 不派，1 派。
    for (int i = 0; i <= 1; i++) {
        choose_spy[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> limit_detect >> limit_money;
    for (int i = 1; i <= n; i++) {
        cin >> info_value[i] >> detect_cost[i] >> money_cost[i];
    }

    best_answer = 0;
    dfs_choose(1);

    cout << best_answer << '\n';
    return 0;
}
