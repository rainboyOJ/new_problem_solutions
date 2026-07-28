/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-28 15:52
 * update_at: 2026-07-28 15:52
 */

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n, s, t;          // n: 楼层数, s: 起点, t: 终点
int k[MAXN];           // k[i] 表示第 i 层可以向上/下移动的层数
int dista[MAXN];       // dista[i] 表示起点到第 i 层的最少按键次数，-1 表示未访问

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s >> t;
    for (int i = 1; i <= n; i++) {
        cin >> k[i];
    }

    // BFS：无权图最短路，每层第一次被访问时就是最短距离
    memset(dista, -1, sizeof(dista));
    queue<int> q;
    dista[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == t) {  // 到达终点，直接输出
            cout << dista[u] << '\n';
            return 0;
        }

        // 从当前层 u 可以向上或向下移动
        int v1 = u + k[u];
        int v2 = u - k[u];

        // 向上移动，在合法范围内且未被访问过
        if (v1 >= 1 && v1 <= n && dista[v1] == -1) {
            dista[v1] = dista[u] + 1;
            q.push(v1);
        }
        // 向下移动，在合法范围内且未被访问过
        if (v2 >= 1 && v2 <= n && dista[v2] == -1) {
            dista[v2] = dista[u] + 1;
            q.push(v2);
        }
    }

    // 所有可达楼层都搜索完仍没到终点，输出 -1
    cout << -1 << '\n';
    return 0;
}
