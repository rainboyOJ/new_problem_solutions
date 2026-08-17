/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，用 01 选择序列枚举每件货物卖或不卖，只适合 m 很小的数据。
#include <bits/stdc++.h>
using namespace std;

int n, m, target;
vector<int> basic_cost, piece_cost, value, warehouse;
vector<int> choose_item; // choose_item[i] 表示第 i 件货物：0 不卖，1 卖
int answer;

// 检查当前完整的 01 选择序列对应的方案是否满足目标
void check_choice() {
    vector<int> count(n, 0);
    vector<int> total_value(n, 0);
    for (int i = 0; i < m; i++) {
        if (choose_item[i] == 0) continue;
        count[warehouse[i]]++;
        total_value[warehouse[i]] += value[i];
    }
    int profit = 0;
    int cost = 0;
    for (int i = 0; i < n; i++) {
        if (count[i] == 0) continue;
        cost += basic_cost[i] + count[i] * piece_cost[i];
        profit += total_value[i] - basic_cost[i] - count[i] * piece_cost[i];
    }
    if (profit >= target) answer = min(answer, cost);
}

// 第 index 件货物只有卖/不卖两种选择
void enumerate_choice(int index) {
    if (index == m) {
        check_choice();
        return;
    }
    choose_item[index] = 0;
    enumerate_choice(index + 1);
    choose_item[index] = 1;
    enumerate_choice(index + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> target;
    basic_cost.resize(n);
    piece_cost.resize(n);
    for (int i = 0; i < n; i++) cin >> basic_cost[i] >> piece_cost[i];
    value.resize(m);
    warehouse.resize(m);
    for (int i = 0; i < m; i++) cin >> value[i] >> warehouse[i];

    choose_item.assign(m, 0);
    answer = 1000000000;
    enumerate_choice(0);
    cout << answer << '\n';
    return 0;
}
