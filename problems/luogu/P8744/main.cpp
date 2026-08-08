#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n;
vector<int> children[MAXN];
int parent_arr[MAXN];
int dp[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        children[i].clear();
        parent_arr[i] = 0;
        dp[i] = 0;
    }

    for (int i = 2; i <= n; i++) {
        int p;
        cin >> p;
        parent_arr[i] = p;
        children[p].push_back(i);
    }

    // 由于保证父亲编号小于儿子编号，可以直接倒序做树形 DP。
    for (int u = n; u >= 1; u--) {
        int best_child = 0;
        for (size_t i = 0; i < children[u].size(); i++) {
            int v = children[u][i];
            best_child = max(best_child, dp[v]);
        }

        if (children[u].empty()) {
            dp[u] = 0;
        } else {
            // 把“收益最大”的儿子放到兄弟链的最后面，能多吃到最多的右兄弟边。
            dp[u] = (int)children[u].size() + best_child;
        }
    }

    cout << dp[1] << '\n';
    return 0;
}
