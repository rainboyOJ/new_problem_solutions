#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，使用 01 序列枚举每门课程选或不选。

const int MAXN = 25;

int n, m;
int parent_course[MAXN];
int credit[MAXN];
int choose_flag[MAXN]; // choose_flag[i] = 0/1，表示第 i 门课程不选/选
int answer;

int calc_chosen_count() {
    int cnt = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_flag[i] == 1) cnt++;
    }
    return cnt;
}

bool check() {
    if (calc_chosen_count() != m) {
        return false;
    }
    for (int i = 1; i <= n; i++) {
        if (choose_flag[i] == 1 && parent_course[i] != 0 && choose_flag[parent_course[i]] == 0) {
            return false;
        }
    }
    return true;
}

int calc_answer() {
    int sum = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_flag[i] == 1) sum += credit[i];
    }
    return sum;
}

void dfs_choose(int dep) {
    if (dep == n + 1) {
        if (check()) {
            int value = calc_answer();
            if (answer < value) answer = value;
        }
        return;
    }

    // 第 dep 门课程的 01 选择：0 不选，1 选。
    for (int i = 0; i <= 1; i++) {
        choose_flag[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> parent_course[i] >> credit[i];
    }

    answer = 0;
    dfs_choose(1);
    cout << answer << '\n';

    return 0;
}
