// brute_01_style.cpp：01 序列风格暴力，按小木棍下标依次决定选或不选。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int MOD = 998244353;

int n;
int a[MAXN];
long long answer;

void dfs(int dep, int chosen_count, long long sum, int max_len) {
    if (dep == n + 1) {
        if (chosen_count >= 3 && sum > 2LL * max_len) {
            answer++;
        }
        return;
    }

    // 第 dep 根小木棍不选，对应 01 序列中的 0。
    dfs(dep + 1, chosen_count, sum, max_len);

    // 第 dep 根小木棍选入集合，对应 01 序列中的 1。
    dfs(dep + 1, chosen_count + 1, sum + a[dep], max(max_len, a[dep]));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    answer = 0;
    dfs(1, 0, 0, 0);

    cout << answer % MOD << '\n';
    return 0;
}
