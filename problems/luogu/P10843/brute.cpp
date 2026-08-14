/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-14 15:01
 * update_at: 2026-08-14 16:40
 */
// brute.cpp：小数据暴力解，BFS 按题意直接模拟操作：
// 每次枚举位置 i 执行 a[i] <- a[i-1]+a[i+1]-a[i]，求到达
// "恰好一个好位置"状态的最少操作数。用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int n;
vector<int> a;

// 检查序列是否恰好存在一个"好位置"（峰）。
bool is_good(const vector<int>& v) {
    int cnt = 0;
    for (int i = 0; i < n; i++) {
        if (v[(i - 1 + n) % n] < v[i] && v[(i + 1) % n] < v[i]) {
            cnt++;
            if (cnt > 1) return false;
        }
    }
    return cnt == 1;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; i++) {
            cin >> a[i];
        }

        if (is_good(a)) {
            cout << 0 << '\n';
            continue;
        }

        // BFS：状态是完整序列，操作是任一位置执行一次赋值
        map<vector<int>, int> dist;
        queue<vector<int>> q;
        dist[a] = 0;
        q.push(a);

        int ans = -1;
        while (!q.empty()) {
            vector<int> u = q.front();
            q.pop();
            int d = dist[u];
            for (int i = 0; i < n; i++) {
                vector<int> v = u;
                v[i] = v[(i - 1 + n) % n] + v[(i + 1) % n] - v[i];
                if (dist.count(v)) continue;
                if (is_good(v)) {
                    ans = d + 1;
                    break;
                }
                dist[v] = d + 1;
                q.push(v);
            }
            if (ans != -1) break;
        }
        cout << ans << '\n';
    }

    return 0;
}
