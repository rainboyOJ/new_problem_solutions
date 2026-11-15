/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-11-15 13:40
 * update_at: 2026-11-15 13:40
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 做法：枚举起点，把"当前整行颜色"当成状态做 BFS，
// 每步把包含起点的连通块染成任意一种出现过的颜色，找到全行同色的最少步数。
// 注意：这里允许染成任意颜色（包括内部颜色），不预设任何结论，
// 因此可以用来独立检验正解的转移是否成立。
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> a;

// 判断整行是否已经同色
bool uniform(const vector<int> &cur) {
    for (int i = 1; i < n; ++i) {
        if (cur[i] != cur[0]) return false;
    }
    return true;
}

// 以 s 为起点，返回把整行染成同色的最少操作数
int solve(int s) {
    map<vector<int>, int> dist;  // 状态 -> 步数
    queue<vector<int>> q;
    dist[a] = 0;
    q.push(a);

    int best = INT_MAX;
    while (!q.empty()) {
        vector<int> cur = q.front();
        q.pop();
        int d = dist[cur];

        if (uniform(cur)) {          // 全行同色，记录答案（BFS 保证首次到达即最短）
            best = min(best, d);
            continue;
        }

        // 找包含起点 s 的同色连通块 [L, R]
        int L = s, R = s;
        while (L - 1 >= 0 && cur[L - 1] == cur[s]) --L;
        while (R + 1 < n && cur[R + 1] == cur[s]) ++R;

        // 本轮可以把这个连通块染成任意别的颜色，不预设只能染邻块颜色
        vector<int> colors = cur;
        sort(colors.begin(), colors.end());
        colors.erase(unique(colors.begin(), colors.end()), colors.end());

        for (int col : colors) {
            if (col == cur[s]) continue;  // 染成自己等于没动
            vector<int> nxt = cur;
            for (int i = L; i <= R; ++i) nxt[i] = col;
            if (dist.find(nxt) == dist.end()) {
                dist[nxt] = d + 1;
                q.push(nxt);
            }
        }
    }
    return best;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    a.resize(n);
    for (int i = 0; i < n; ++i) cin >> a[i];

    int ans = INT_MAX;
    for (int s = 0; s < n; ++s) ans = min(ans, solve(s));
    cout << ans << '\n';
    return 0;
}
