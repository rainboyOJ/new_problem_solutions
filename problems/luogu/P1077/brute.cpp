#include <bits/stdc++.h>
using namespace std;

const int MOD = 1000007;

int n, m;
vector<int> a;
vector<int> choose_flower; // choose_flower[i] 表示第 i 种花取多少盆
int answer = 0;

int calc_total() {
    int total = 0;
    for (int i = 0; i < n; i++) {
        total += choose_flower[i];
    }
    return total;
}

// dfs_choose 只负责枚举每种花取多少盆，最后统一检查总数。
void dfs_choose(int dep) {
    if (dep == n) {
        if (calc_total() == m) {
            answer++;
            if (answer >= MOD) answer -= MOD;
        }
        return;
    }

    // 第 dep 种花可以取 0..a[dep] 盆。
    for (int cnt = 0; cnt <= a[dep]; cnt++) {
        choose_flower[dep] = cnt;
        dfs_choose(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    choose_flower.assign(n, 0);
    dfs_choose(0);
    cout << answer << '\n';

    return 0;
}
