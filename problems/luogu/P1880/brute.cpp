#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。

const int INF = 0x3f3f3f3f;

int n;
vector<int> stones;
map<vector<int>, pair<int, int> > memo;

// 暴力递归：当前 stones 表示环上剩余的石子堆。
pair<int, int> dfs(vector<int> cur) {
    int m = (int) cur.size();
    if (m == 1) {
        return make_pair(0, 0);
    }

    map<vector<int>, pair<int, int> >::iterator it = memo.find(cur);
    if (it != memo.end()) {
        return it->second;
    }

    int best_min = INF;
    int best_max = -INF;

    for (int i = 0; i < m; i++) {
        int j = (i + 1) % m;
        int merged = cur[i] + cur[j];

        vector<int> nxt;
        nxt.push_back(merged);
        // 合并掉 i 和 j 后，剩余元素按环上的相对顺序接在 merged 后面。
        for (int step = 1; step <= m - 2; step++) {
            int idx = (j + step) % m;
            nxt.push_back(cur[idx]);
        }

        pair<int, int> sub = dfs(nxt);
        best_min = min(best_min, sub.first + merged);
        best_max = max(best_max, sub.second + merged);
    }

    pair<int, int> ans = make_pair(best_min, best_max);
    memo[cur] = ans;
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    stones.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> stones[i];
    }

    memo.clear();
    pair<int, int> ans = dfs(stones);
    cout << ans.first << '\n';
    cout << ans.second << '\n';
    return 0;
}
