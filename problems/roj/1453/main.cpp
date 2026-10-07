/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:55
 * update_at: 2026-10-05 23:55
 */

#include <iostream>
#include <string>
#include <queue>
#include <cstring>
using namespace std;

typedef long long ll;

// 4x4 网格的 24 对相邻格子（位编号 0..15）
// 横向相邻：每行 3 对，共 4 行
// 纵向相邻：每列 3 对，共 4 列
const int MOVE_CNT = 24;
int mv_u[MOVE_CNT], mv_v[MOVE_CNT];

// dist[state] 表示从起点到该状态的最少步数，-1 表示未访问
int dist[1 << 16];

// 将 4 行 01 字符串压缩为 16 位整数，第 r 行第 c 列对应位 r*4+c
int parse_board() {
    int state = 0;
    for (int r = 0; r < 4; ++r) {
        string s;
        cin >> s;
        for (int c = 0; c < 4; ++c) {
            if (s[c] == '1') {
                state |= 1 << (r * 4 + c);
            }
        }
    }
    return state;
}

// BFS 求从 start 到 target 的最少移动步数
int bfs(int start, int target) {
    if (start == target) return 0;
    memset(dist, -1, sizeof(dist));
    queue<int> q;
    dist[start] = 0;
    q.push(start);
    while (!q.empty()) {
        int cur = q.front();
        q.pop();
        int step = dist[cur];
        for (int i = 0; i < MOVE_CNT; ++i) {
            int u = mv_u[i];
            int v = mv_v[i];
            int bu = (cur >> u) & 1;
            int bv = (cur >> v) & 1;
            if (bu == bv) continue; // 相同则交换无意义
            int nxt = cur ^ (1 << u) ^ (1 << v);
            if (nxt == target) return step + 1;
            if (dist[nxt] == -1) {
                dist[nxt] = step + 1;
                q.push(nxt);
            }
        }
    }
    return -1; // 题目保证可达
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 预处理 24 对相邻格子
    int idx = 0;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 3; ++c) {
            mv_u[idx] = r * 4 + c;
            mv_v[idx] = r * 4 + c + 1;
            ++idx;
        }
    }
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 4; ++c) {
            mv_u[idx] = r * 4 + c;
            mv_v[idx] = (r + 1) * 4 + c;
            ++idx;
        }
    }

    int start = parse_board();
    int target = parse_board();
    cout << bfs(start, target) << "\n";
    return 0;
}
