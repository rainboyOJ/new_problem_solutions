// brute.cpp：小数据暴力解，使用 01 序列枚举每个物品放或不放。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 35;

int capacity;          // 箱子容量
int n;                 // 物品数量
int a[MAXN];           // 每个物品的体积
int choose_item[MAXN]; // choose_item[i] = 0/1，表示第 i 个物品不放/放
int best_fill;         // 当前能装下的最大总体积

int calc_volume() {
    int sum_volume = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_item[i] == 1) sum_volume += a[i];
    }
    return sum_volume;
}

bool check() {
    return calc_volume() <= capacity;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_volume();
            if (best_fill < value) best_fill = value;
        }
        return;
    }

    // 第 dep 个物品的 01 选择：0 不放，1 放。
    for (int i = 0; i <= 1; i++) {
        choose_item[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> capacity;
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    best_fill = 0;
    dfs_choose(1);

    cout << capacity - best_fill << '\n';
    return 0;
}
