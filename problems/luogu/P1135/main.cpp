/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-28 15:52
 * update_at: 2026-08-13 13:19
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n, s, t;        // n: 楼层数, s: 起点楼层, t: 终点楼层
int k[MAXN];        // k[i] 表示第 i 层能向上/向下移动的层数
int dista[MAXN];    // dista[i] 表示起点到第 i 层的最少按键次数，-1 表示未访问

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s >> t;
    for (int i = 1; i <= n; i++) {
        cin >> k[i];
    }

    // BFS：无权图最短路。楼层第一次被访问到时，距离一定是最短的。
    memset(dista, -1, sizeof(dista));
    queue<int> q;
    dista[s] = 0;
    q.push(s);

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (u == t) {   // 到达终点，直接输出最少按键次数
            cout << dista[u] << '\n';
            return 0;
        }

        // 从当前楼层 u 只能尝试两个方向：向上跳或向下跳 k[u] 层。
        int v1 = u + k[u];   // 向上
        int v2 = u - k[u];   // 向下

        // 越界的按钮失灵；已经访问过的楼层不需要再入队。
        if (v1 >= 1 && v1 <= n && dista[v1] == -1) {
            dista[v1] = dista[u] + 1;
            q.push(v1);
        }
        if (v2 >= 1 && v2 <= n && dista[v2] == -1) {
            dista[v2] = dista[u] + 1;
            q.push(v2);
        }
    }

    // 所有可达楼层都搜索完仍没到终点，说明 B 不可达。
    cout << -1 << '\n';
    return 0;
}
