#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，使用 01 序列枚举每个物品选或不选。

const int MAXN = 3405;

int n, m;
int weight[MAXN];
int value[MAXN];
int choose_item[MAXN]; // choose_item[i] = 0/1，表示第 i 个物品不选/选
int answer;

bool check() {
    int used_weight = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_item[i] == 1) used_weight += weight[i];
    }
    return used_weight <= m;
}

int calc_answer() {
    int total_value = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_item[i] == 1) total_value += value[i];
    }
    return total_value;
}

// dfs_choose 只负责生成完整 01 序列，合法性和答案统计放到叶子节点。
void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int current_value = calc_answer();
            if (answer < current_value) answer = current_value;
        }
        return;
    }

    for (int i = 0; i <= 1; i++) {
        choose_item[dep] = i;
        dfs_choose(dep + 1);
    }
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> weight[i] >> value[i];
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
