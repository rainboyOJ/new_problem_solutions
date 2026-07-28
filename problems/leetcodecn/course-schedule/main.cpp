#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    bool canFinish(int n, vector<vector<int>>& prerequisites) {
        vector<vector<int>> g(n);
        vector<int> indeg(n);
        for (auto& e : prerequisites) { g[e[1]].push_back(e[0]); indeg[e[0]]++; }
        queue<int> q;
        for (int i = 0; i < n; i++) if (indeg[i] == 0) q.push(i);
        int cnt = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop(); cnt++;
            for (int v : g[u]) if (--indeg[v] == 0) q.push(v);
        }
        return cnt == n;
    }
};
int main() {
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n, m; cin >> n >> m;
    vector<vector<int>> pre(m, vector<int>(2));
    for (int i = 0; i < m; i++) cin >> pre[i][0] >> pre[i][1];
    cout << Solution().canFinish(n, pre) << '\n';
    return 0;
}
