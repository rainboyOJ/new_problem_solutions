// brute_01_style.cpp：选择序列风格暴力，对每个结尾 i 枚举前面位置选或不选。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
int a[MAXN];
int target_pos;
vector<int> current_path;
vector<int> best_path;

bool path_less(const vector<int> &x, const vector<int> &y) {
    if (y.empty()) {
        return true;
    }
    return x < y;
}

int path_sum(const vector<int> &path) {
    int sum = 0;
    for (int i = 0; i < (int)path.size(); i++) {
        sum += a[path[i]];
    }
    return sum;
}

void update_answer() {
    if ((int)current_path.size() > (int)best_path.size()) {
        best_path = current_path;
        return;
    }
    if ((int)current_path.size() == (int)best_path.size() && path_less(current_path, best_path)) {
        best_path = current_path;
    }
}

// dfs_choose(pos)：处理到 target_pos 前面的第 pos 个位置，决定选或不选。
void dfs_choose(int pos) {
    if (pos == target_pos) {
        if (!current_path.empty() && a[current_path.back()] > a[target_pos]) {
            return;
        }
        current_path.push_back(target_pos);
        update_answer();
        current_path.pop_back();
        return;
    }

    // 选择 0：不把 pos 放入当前子序列。
    dfs_choose(pos + 1);

    // 选择 1：如果数值不下降，就把 pos 放入当前子序列。
    if (current_path.empty() || a[current_path.back()] <= a[pos]) {
        current_path.push_back(pos);
        dfs_choose(pos + 1);
        current_path.pop_back();
    }
}

int solve_one_position(int pos) {
    target_pos = pos;
    current_path.clear();
    best_path.clear();
    dfs_choose(1);
    return path_sum(best_path);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        if (i > 1) {
            cout << ' ';
        }
        cout << solve_one_position(i);
    }
    cout << '\n';

    return 0;
}
