// brute_01_style.cpp：01 序列风格暴力，对每个结尾 i 枚举前面位置选或不选。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

int n;
int a[MAXN];
int target_pos;
int choose_pos[MAXN]; // choose_pos[i] = 0/1，表示位置 i 不选/选
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
    vector<int> path;
    for (int i = 1; i < target_pos; i++) {
        if (choose_pos[i] == 1) path.push_back(i);
    }
    path.push_back(target_pos);

    for (int i = 1; i < (int)path.size(); i++) {
        if (a[path[i - 1]] > a[path[i]]) {
            return;
        }
    }

    if ((int)path.size() > (int)best_path.size()) {
        best_path = path;
        return;
    }
    if ((int)path.size() == (int)best_path.size() && path_less(path, best_path)) {
        best_path = path;
    }
}

void dfs_choose(int dep) {
    if (dep == target_pos) {
        update_answer();
        return;
    }

    for (int i = 0; i <= 1; i++) {
        choose_pos[dep] = i;
        dfs_choose(dep + 1);
    }
}

int solve_one_position(int pos) {
    target_pos = pos;
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
