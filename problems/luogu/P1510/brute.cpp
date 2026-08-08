// brute.cpp：小数据暴力解，使用 01 序列枚举每块木石选或不选。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10005;

int need_volume;          // 至少需要填平的体积
int n;                    // 木石数量
int stamina_limit;        // 剩余体力
int volume_gain[MAXN];    // 木石体积
int stamina_cost[MAXN];   // 木石体力消耗
int choose_stone[MAXN];   // choose_stone[i] = 0/1，表示第 i 块木石不选/选
int best_cost;            // 达到目标体积时的最小体力消耗

bool check() {
    int sum_volume = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_stone[i] == 1) sum_volume += volume_gain[i];
    }
    return sum_volume >= need_volume;
}

int calc_cost() {
    int sum_cost = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_stone[i] == 1) sum_cost += stamina_cost[i];
    }
    return sum_cost;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_cost();
            if (best_cost > value) best_cost = value;
        }
        return;
    }

    // 第 dep 块木石的 01 选择：0 不选，1 选。
    for (int i = 0; i <= 1; i++) {
        choose_stone[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> need_volume >> n >> stamina_limit;
    for (int i = 1; i <= n; i++) {
        cin >> volume_gain[i] >> stamina_cost[i];
    }

    best_cost = 0x3f3f3f3f;
    dfs_choose(1);

    if (best_cost > stamina_limit) {
        cout << "Impossible\n";
    } else {
        cout << stamina_limit - best_cost << '\n';
    }

    return 0;
}
