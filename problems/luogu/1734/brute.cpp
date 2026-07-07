// brute.cpp：小数据暴力解，使用 01 序列枚举每个正整数选或不选。
#include <bits/stdc++.h>
using namespace std;

const int MAXS = 1005;

int s;                  // 总和上限
int divisor_sum[MAXS];  // 真约数和
int choose_num[MAXS];   // choose_num[i] = 0/1，表示数字 i 不选/选
int best_answer;        // 当前最大约数和

void build_divisor_sum() {
    memset(divisor_sum, 0, sizeof(divisor_sum));
    for (int d = 1; d <= s / 2; d++) {
        for (int multiple = d + d; multiple <= s; multiple += d) {
            divisor_sum[multiple] += d;
        }
    }
}

bool check() {
    int sum_weight = 0;
    for (int i = 1; i <= s; i++) {
        if (choose_num[i] == 1) sum_weight += i;
    }
    return sum_weight <= s;
}

int calc_answer() {
    int sum_value = 0;
    for (int i = 1; i <= s; i++) {
        if (choose_num[i] == 1) sum_value += divisor_sum[i];
    }
    return sum_value;
}

void dfs_choose(int dep) {
    if (dep == s + 1) {
        if (check()) {
            int value = calc_answer();
            if (best_answer < value) best_answer = value;
        }
        return;
    }

    // 第 dep 个正整数的 01 选择：0 不选，1 选。
    for (int i = 0; i <= 1; i++) {
        choose_num[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    build_divisor_sum();

    best_answer = 0;
    dfs_choose(1);

    cout << best_answer << '\n';
    return 0;
}
