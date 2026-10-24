#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 直接按题意在环上枚举"合并哪一对相邻石子"，递归 + 记忆化。

const int INF = 0x3f3f3f3f;

int n;
map<vector<int>, pair<int, int> > memo;

// 把 vector 旋转到以最小元素（第一个出现处）开头，使同一个环只有一种表示。
static vector<int> canonical(const vector<int> &v) {
    int m = (int) v.size();
    int pos = 0;
    for (int i = 1; i < m; i++) {
        if (v[i] < v[pos]) pos = i;
    }
    vector<int> r;
    for (int i = 0; i < m; i++) r.push_back(v[(pos + i) % m]);
    return r;
}

// 暴力递归：当前 cur 表示环上剩余的石子堆（按环上顺序）。
pair<int, int> dfs(const vector<int> &cur) {
    int m = (int) cur.size();
    if (m == 1) return make_pair(0, 0);

    vector<int> key = canonical(cur);
    map<vector<int>, pair<int, int> >::iterator it = memo.find(key);
    if (it != memo.end()) return it->second;

    int best_min = INF;
    int best_max = -INF;

    for (int i = 0; i < m; i++) {
        int j = (i + 1) % m;
        int merged = cur[i] + cur[j];

        // 合并掉 i 和 j 后，从 j 的下一个位置开始，把剩下的 m-2 个元素
        // 接在 merged 后面，保持环上的相对顺序。
        vector<int> nxt;
        nxt.push_back(merged);
        for (int step = 1; step <= m - 2; step++) {
            nxt.push_back(cur[(j + step) % m]);
        }

        pair<int, int> sub = dfs(nxt);
        best_min = min(best_min, sub.first + merged);
        best_max = max(best_max, sub.second + merged);
    }

    pair<int, int> ans = make_pair(best_min, best_max);
    memo[key] = ans;
    return ans;
}

int main() {
    cin >> n;
    vector<int> stones(n);
    for (int i = 0; i < n; i++) cin >> stones[i];

    memo.clear();
    pair<int, int> ans = dfs(stones);
    cout << ans.first << '\n';
    cout << ans.second << '\n';
    return 0;
}
