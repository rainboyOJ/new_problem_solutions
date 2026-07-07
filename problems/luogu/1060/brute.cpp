// brute.cpp：小数据暴力解，使用 01 序列枚举每件物品买或不买。
#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1005;

int budget;             // 总预算
int item_count;         // 物品数量
int price[MAXM];        // 价格
int importance[MAXM];   // 重要度
int choose_item[MAXM];  // choose_item[i] = 0/1，表示第 i 件物品不买/买
int best_answer;        // 当前最大满意度

bool check() {
    int used_money = 0;
    for (int i = 1; i <= item_count; i++) {
        if (choose_item[i] == 1) used_money += price[i];
    }
    return used_money <= budget;
}

int calc_answer() {
    int total_value = 0;
    for (int i = 1; i <= item_count; i++) {
        if (choose_item[i] == 1) total_value += price[i] * importance[i];
    }
    return total_value;
}

void dfs_choose(int dep) {
    if (dep == item_count + 1) {
        if (check()) {
            int value = calc_answer();
            if (best_answer < value) best_answer = value;
        }
        return;
    }

    // 第 dep 件物品的 01 选择：0 不买，1 买。
    for (int i = 0; i <= 1; i++) {
        choose_item[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> budget >> item_count;
    for (int i = 1; i <= item_count; i++) {
        cin >> price[i] >> importance[i];
    }

    best_answer = 0;
    dfs_choose(1);

    cout << best_answer << '\n';
    return 0;
}
