// brute.cpp：小数据暴力解，递归枚举每个候选数使用 0、1、2……次。
#include <bits/stdc++.h>
using namespace std;

int n, target;
int c[15];
int cnt[15]; // cnt[i] 表示候选 c[i] 被选了几次
vector<vector<int>> ans;

void dfs(int i, int sum) {
    if (sum > target)
        return;
    if (i == n) {
        if (sum == target) {
            vector<int> cur;
            for (int j = 0; j < n; j++)
                for (int k = 0; k < cnt[j]; k++)
                    cur.push_back(c[j]);
            ans.push_back(cur);
        }
        return;
    }
    // 枚举 c[i] 选 0, 1, 2, ... 次，直到超出 target
    for (cnt[i] = 0; sum + cnt[i] * c[i] <= target; cnt[i]++) {
        dfs(i + 1, sum + cnt[i] * c[i]);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n >> target;
    for (int i = 0; i < n; i++)
        cin >> c[i];
    dfs(0, 0);
    for (auto &v : ans) {
        for (int x : v)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
