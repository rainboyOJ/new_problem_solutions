#include <bits/stdc++.h>
using namespace std;

int dfs(vector<int> v) {
    int best = 0;
    for (int x : v) {
        best = max(best, x);
    }

    for (int i = 0; i + 1 < (int)v.size(); ++i) {
        if (v[i] != v[i + 1]) {
            continue;
        }
        vector<int> next = v;
        next[i] = next[i] + 1;
        next.erase(next.begin() + i + 1);
        // 暴力枚举这一步合并哪一对相邻且相等的数字。
        best = max(best, dfs(next));
    }

    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> v(n);
    for (int i = 0; i < n; ++i) {
        cin >> v[i];
    }

    cout << dfs(v) << '\n';
    return 0;
}
