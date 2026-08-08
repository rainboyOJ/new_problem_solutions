#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，使用 01 序列枚举每捆干草吃或不吃。

const int MAXN = 505;

int h, n;
int weight[MAXN];
int choose_hay[MAXN]; // choose_hay[i] = 0/1，表示第 i 捆干草不吃/吃
int answer;

int calc_weight() {
    int total_weight = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_hay[i] == 1) total_weight += weight[i];
    }
    return total_weight;
}

bool check() {
    return calc_weight() <= h;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_weight();
            if (answer < value) answer = value;
        }
        return;
    }

    // 第 dep 捆干草的 01 选择：0 不吃，1 吃。
    for (int i = 0; i <= 1; i++) {
        choose_hay[dep] = i;
        dfs_choose(dep + 1);
    }
}

void read_input() {
    cin >> h >> n;
    for (int i = 1; i <= n; i++) {
        cin >> weight[i];
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
