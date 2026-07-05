// brute_01_style.cpp：另一种小数据暴力写法，按每个 2 的幂决定选或不选。
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> power_list;
vector<int> path;
vector<int> answer;
bool found;

void dfs_choose(int idx, int sum) {
    if (found) {
        return;
    }
    if (sum == n) {
        answer = path;
        found = true;
        return;
    }
    if (idx < 0 || sum > n) {
        return;
    }

    // 这一位选 1：把当前 2 的幂加入答案。
    if (sum + power_list[idx] <= n) {
        path.push_back(power_list[idx]);
        dfs_choose(idx - 1, sum + power_list[idx]);
        path.pop_back();
    }

    // 这一位选 0：跳过当前 2 的幂。
    dfs_choose(idx - 1, sum);
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
    dfs_choose((int)power_list.size() - 1, 0);

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
