#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，每个木块三种选择，先生成完整选择序列再检查。

int n;
int h[25];
int choose_block[25]; // 0 不用，1 放左塔，2 放右塔
int ans;

void calc_height(int &left_sum, int &right_sum) {
    left_sum = 0;
    right_sum = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_block[i] == 1) {
            left_sum += h[i];
        } else if (choose_block[i] == 2) {
            right_sum += h[i];
        }
    }
}

bool check() {
    int left_sum, right_sum;
    calc_height(left_sum, right_sum);
    return left_sum == right_sum && left_sum > 0;
}

int calc_answer() {
    int left_sum, right_sum;
    calc_height(left_sum, right_sum);
    return left_sum;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (ans < value) ans = value;
        }
        return;
    }

    // 第 dep 个木块的选择：0 不用，1 放左塔，2 放右塔。
    for (int i = 0; i <= 2; i++) {
        choose_block[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    ans = 0;
    dfs_choose(1);

    cout << ans << '\n';
    return 0;
}
