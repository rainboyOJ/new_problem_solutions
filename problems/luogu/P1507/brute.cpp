#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，使用 01 序列枚举每个食品选或不选。

int H, T, n;
int h[55], t[55], k[55];
int choose_food[55]; // choose_food[i] = 0/1，表示第 i 个食品不选/选
int ans;

bool check() {
    int total_h = 0;
    int total_t = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_food[i] == 1) {
            total_h += h[i];
            total_t += t[i];
        }
    }
    return total_h <= H && total_t <= T;
}

int calc_answer() {
    int total_cal = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_food[i] == 1) total_cal += k[i];
    }
    return total_cal;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (ans < value) ans = value;
        }
        return;
    }

    // 第 dep 个食品的 01 选择：0 不选，1 选。
    for (int i = 0; i <= 1; i++) {
        choose_food[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> H >> T;
    cin >> n;

    for (int i = 1; i <= n; i++) {
        cin >> h[i] >> t[i] >> k[i];
    }

    ans = 0;
    dfs_choose(1);

    cout << ans << '\n';
    return 0;
}
