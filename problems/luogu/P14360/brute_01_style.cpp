// brute_01_style.cpp：01 序列风格暴力，按小木棍下标依次决定选或不选。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int MOD = 998244353;

int n;
int a[MAXN];
int choose_stick[MAXN]; // choose_stick[i] = 0/1，表示第 i 根木棍不选/选
long long answer;

bool check() {
    int chosen_count = 0;
    long long sum = 0;
    int max_len = 0;
    for (int i = 1; i <= n; i++) {
        if (choose_stick[i] == 1) {
            chosen_count++;
            sum += a[i];
            max_len = max(max_len, a[i]);
        }
    }
    return chosen_count >= 3 && sum > 2LL * max_len;
}

void dfs(int dep) {
    if (dep == n + 1) {
        if (check()) {
            answer++;
        }
        return;
    }

    // 第 dep 根木棍的 01 选择：0 不选，1 选。
    for (int i = 0; i <= 1; i++) {
        choose_stick[dep] = i;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    answer = 0;
    dfs(1);

    cout << answer % MOD << '\n';
    return 0;
}
