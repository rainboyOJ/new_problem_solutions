// brute.cpp：小数据暴力解，使用 01 序列枚举每种菜点或不点。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;              // 菜品种类数
int money;          // 需要恰好花掉的钱
int a[MAXN];        // 每种菜的价格
int choose_dish[MAXN]; // choose_dish[i] = 0/1，表示第 i 种菜不点/点
int answer_count;   // 当前方案数

int calc_money() {
    int sum_money = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_dish[i] == 1) sum_money += a[i];
    }
    return sum_money;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (calc_money() == money) {
            answer_count++;
        }
        return;
    }

    // 第 dep 种菜的 01 选择：0 不点，1 点。
    for (int i = 0; i <= 1; i++) {
        choose_dish[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> money;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    answer_count = 0;
    dfs_choose(1);

    cout << answer_count << '\n';
    return 0;
}
