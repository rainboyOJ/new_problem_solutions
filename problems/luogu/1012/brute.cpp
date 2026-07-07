// brute.cpp：小数据暴力解，使用选择序列递归枚举所有拼接顺序。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int n;
string a[MAXN];
bool used[MAXN];
string best_answer;

void dfs_order(int depth, string current) {
    if (depth == n) {
        if ((int)current.size() > (int)best_answer.size() ||
            ((int)current.size() == (int)best_answer.size() && current > best_answer)) {
            best_answer = current;
        }
        return;
    }

    // 这一层选择下一个放到答案里的数。
    for (int i = 1; i <= n; i++) {
        if (!used[i]) {
            used[i] = true;
            dfs_order(depth + 1, current + a[i]);
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
    dfs_order(0, "");
    cout << best_answer << '\n';
    return 0;
}
