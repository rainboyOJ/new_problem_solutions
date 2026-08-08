#include <bits/stdc++.h>
using namespace std;

const int MOD = 100000000;

int n, f;
vector<int> a;
vector<int> choose_cow; // choose_cow[i] = 0/1，表示第 i 头牛不选/选
int answer = 0;

// 计算当前完整选择序列的总和模 F。
int calc_mod() {
    int sum_mod = 0;
    for (int i = 0; i < n; i++) {
        if (choose_cow[i] == 1) {
            sum_mod = (sum_mod + a[i]) % f;
        }
    }
    return sum_mod;
}

bool check() {
    bool chosen = false;
    for (int i = 0; i < n; i++) {
        if (choose_cow[i] == 1) {
            chosen = true;
        }
    }
    return chosen && calc_mod() == 0;
}

// dfs_choose 只负责枚举完整 01 序列，合法性放到叶子节点统一检查。
void dfs_choose(int dep) {
    if (dep == n) {
        if (check()) {
            answer++;
            if (answer >= MOD) {
                answer -= MOD;
            }
        }
        return;
    }

    // 第 dep 头牛的 01 选择：0 不选，1 选。
    for (int i = 0; i <= 1; i++) {
        choose_cow[dep] = i;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> f;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    choose_cow.assign(n, 0);
    dfs_choose(0);
    cout << answer % MOD << '\n';

    return 0;
}
