#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> iq, eq;
vector<int> choose_cow; // choose_cow[i] = 0/1，表示第 i 头奶牛不选/选
int answer = 0;

void calc_sum(int &sum_iq, int &sum_eq) {
    sum_iq = 0;
    sum_eq = 0;
    for (int i = 0; i < n; i++) {
        if (choose_cow[i] == 1) {
            sum_iq += iq[i];
            sum_eq += eq[i];
        }
    }
}

bool check() {
    int sum_iq, sum_eq;
    calc_sum(sum_iq, sum_eq);
    return sum_iq >= 0 && sum_eq >= 0;
}

int calc_answer() {
    int sum_iq, sum_eq;
    calc_sum(sum_iq, sum_eq);
    return sum_iq + sum_eq;
}

// dfs_choose 只负责枚举完整 01 序列。
void dfs_choose(int dep) {
    if (dep == n) {
        if (check()) {
            int value = calc_answer();
            if (answer < value) answer = value;
        }
        return;
    }

    // 第 dep 头奶牛的 01 选择：0 不选，1 选。
    for (int i = 0; i <= 1; i++) {
        choose_cow[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    iq.resize(n);
    eq.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> iq[i] >> eq[i];
    }

    choose_cow.assign(n, 0);
    dfs_choose(0);
    cout << answer << '\n';

    return 0;
}
