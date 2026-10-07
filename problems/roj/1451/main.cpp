/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 23:56
 * update_at: 2026-10-05 23:56
 */
#include <cstdio>
#include <cstring>
#include <iostream>
#include <queue>
#include <string>
using namespace std;

typedef long long ll;

int dist[1 << 16]; // 每个 16 位掩码状态到起点的最短步数，-1 表示未访问
int pair_mask[24]; // 24 对相邻格子的掩码
int pm_cnt;        // 相邻对数量

// 读取一个 4 位 01 串，cin >> s 会自动跳过空行和空白字符
int read_row() {
    string s;
    cin >> s;
    return stoi(s, nullptr, 2);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 预生成 24 对相邻格子的掩码：横向 12 对 + 纵向 12 对
    pm_cnt = 0;
    for (int r = 0; r < 4; ++r) {
        for (int c = 0; c < 3; ++c) {
            pair_mask[pm_cnt++] = (1 << (r * 4 + c)) | (1 << (r * 4 + c + 1));
        }
    }
    for (int r = 0; r < 3; ++r) {
        for (int c = 0; c < 4; ++c) {
            pair_mask[pm_cnt++] = (1 << (r * 4 + c)) | (1 << ((r + 1) * 4 + c));
        }
    }

    // 读入 8 个 4 位 01 串，前四个拼成初始状态，后四个拼成目标状态
    int start = 0, target = 0;
    for (int i = 0; i < 4; ++i) {
        int row = read_row();
        start = (start << 4) | row;
    }
    for (int i = 0; i < 4; ++i) {
        int row = read_row();
        target = (target << 4) | row;
    }

    // BFS：每条边代价为 1，第一次到达目标即为最少步数
    memset(dist, -1, sizeof(dist));
    queue<int> q;
    dist[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        if (u == target) break;
        int d = dist[u];
        for (int i = 0; i < pm_cnt; ++i) {
            int p = pair_mask[i];
            int sub = u & p;
            if (sub == 0 || sub == p) continue; // 同色，交换不改变局面
            int v = u ^ p;                       // 异色，交换等价于两格同时翻转
            if (dist[v] == -1) {
                dist[v] = d + 1;
                q.push(v);
            }
        }
    }

    cout << dist[target] << "\n";
    return 0;
}
