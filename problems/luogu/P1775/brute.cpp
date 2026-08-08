#include <bits/stdc++.h>
using namespace std;

int dfs(vector<int> stones) {
    if (stones.size() == 1) {
        return 0;
    }

    int best = INT_MAX;
    for (int i = 0; i + 1 < (int)stones.size(); ++i) {
        vector<int> next = stones;
        int merged = next[i] + next[i + 1];
        next[i] = merged;
        next.erase(next.begin() + i + 1);
        // 暴力枚举这一步选择哪一对相邻石子合并
        best = min(best, merged + dfs(next));
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<int> stones(n);
    for (int i = 0; i < n; ++i) {
        cin >> stones[i];
    }

    cout << dfs(stones) << '\n';
    return 0;
}
