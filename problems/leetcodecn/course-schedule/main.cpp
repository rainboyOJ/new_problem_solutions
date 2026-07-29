#include <bits/stdc++.h>
using namespace std;

class Solution {
public:
    bool canFinish(int n, vector<vector<int>> &prerequisites) {
        vector<vector<int>> g(n);
        vector<int> indeg(n);
        for (auto &e : prerequisites) {
            // 先修课 e[1] 指向后修课 e[0]，入度表示尚未完成的先修课数量。
            g[e[1]].push_back(e[0]);
            indeg[e[0]]++;
        }
        queue<int> q;
        for (int i = 0; i < n; i++)
            if (indeg[i] == 0)
                q.push(i);
        int finished = 0;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            finished++;
            for (int v : g[u])
                if (--indeg[v] == 0)
                    q.push(v);
        }
        return finished == n;
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int n, m;
    cin >> n >> m;
    vector<vector<int>> pre(m, vector<int>(2));
    for (int i = 0; i < m; i++)
        cin >> pre[i][0] >> pre[i][1];
    cout << Solution().canFinish(n, pre) << '\n';
    return 0;
}
