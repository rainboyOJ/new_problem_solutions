// brute_01_style.cpp：01 序列风格暴力，按每个 2 的幂决定选或不选。
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> power_list;
vector<int> choose_power; // choose_power[i] = 0/1，表示第 i 个 2 的幂不选/选
vector<int> answer;
bool found;

int calc_sum() {
    int sum = 0;
    for (int i = 0; i < (int)power_list.size(); i++) {
        if (choose_power[i] == 1) sum += power_list[i];
    }
    return sum;
}

void save_answer() {
    answer.clear();
    for (int i = (int)power_list.size() - 1; i >= 0; i--) {
        if (choose_power[i] == 1) {
            answer.push_back(power_list[i]);
        }
    }
}

void dfs_choose(int dep) {
    if (dep == (int)power_list.size()) {
        if (!found && calc_sum() == n) {
            save_answer();
            found = true;
        }
        return;
    }

    // 第 dep 个 2 的幂的 01 选择：0 不选，1 选。
    for (int i = 0; i <= 1; i++) {
        choose_power[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    if (n % 2 == 1) {
        cout << -1 << '\n';
        return 0;
    }

    for (int x = 2; x <= n; x <<= 1) {
        power_list.push_back(x);
    }

    found = false;
    choose_power.assign(power_list.size(), 0);
    dfs_choose(0);

    if (!found) {
        cout << -1 << '\n';
        return 0;
    }

    for (int i = 0; i < (int)answer.size(); i++) {
        if (i > 0) {
            cout << ' ';
        }
        cout << answer[i];
    }
    cout << '\n';

    return 0;
}
