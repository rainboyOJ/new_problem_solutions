// brute.cpp：小数据暴力解，使用选择序列递归枚举所有拼接顺序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int n;
string a[MAXN];
bool used[MAXN];
int choose_order[MAXN]; // choose_order[i] 表示第 i 个位置放哪个原数
string best_answer;

string calc_answer() {
    string res = "";
    for (int i = 1; i <= n; i++) {
        res += a[choose_order[i]];
    }
    return res;
}

void update_answer() {
    string current = calc_answer();
    if ((int)current.size() > (int)best_answer.size() ||
        ((int)current.size() == (int)best_answer.size() && current > best_answer)) {
        best_answer = current;
    }
}

void dfs_order(int dep) {
    if (dep == n + 1) {
        update_answer();
        return;
    }

    // 这一层只记录第 dep 个拼接位置选择哪个数。
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;
            choose_order[dep] = i;
            dfs_order(dep + 1);
            used[i] = false;
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    best_answer = "";
    dfs_order(1);
    cout << best_answer << '\n';
    return 0;
}
