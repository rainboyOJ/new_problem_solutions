#include <bits/stdc++.h>
using namespace std;

int k, n;
vector<int> a;
set<int> reachable;

// 暴力枚举最多使用 k 枚邮票时能拼出的所有面值。
// 这个做法只适合小数据，但最容易直接对应题意。
void dfs(int used, int sum) {
    if (used > k) {
        return;
    }

    reachable.insert(sum);
    if (used == k) {
        return;
    }

    for (int v : a) {
        dfs(used + 1, sum + v);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> k >> n;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    dfs(0, 0);

    int answer = 0;
    while (reachable.count(answer + 1)) {
        answer++;
    }

    cout << answer << '\n';

    return 0;
}
