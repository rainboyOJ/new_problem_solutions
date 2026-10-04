/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 00:06
 * update_at: 2026-10-05 00:06
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

typedef long long ll;

int m, n;
bool conn[MAXN][MAXN]; // conn[u][v] = true 表示 u 可以花 1 次乘车直达 v（同一线路前后站点对）
int dist[MAXN];        // dist[v] 表示从站点 1 到站点 v 的最少乘车次数，-1 表示未访问
int que[MAXN];         // BFS 手写队列，存站点编号

// 读入所有线路，把同一线路里的每对前后站点连成一条权值为 1 的有向"乘车"关系。
void read_input() {
    cin >> m >> n;
    // 注意每条线路一行，站点个数不定，整行读入后拆分
    string line;
    getline(cin, line); // 吃掉第一行末尾换行
    for (int i = 1; i <= m; i++) {
        getline(cin, line);
        istringstream iss(line);
        int cnt = 0;
        int stops[MAXN];
        while (iss >> stops[cnt + 1]) cnt++;
        // 同一线路上任意前面的站点都能直达后面的站点，乘一次车
        for (int a = 1; a <= cnt; a++) {
            for (int b = a + 1; b <= cnt; b++) {
                conn[stops[a]][stops[b]] = true;
            }
        }
    }
}

// BFS 求站点 1 到站点 n 的最少乘车次数（边权全为 1）。
void bfs() {
    for (int v = 1; v <= n; v++) dist[v] = -1;
    int head = 1, tail = 1;
    dist[1] = 0;
    que[tail] = 1;
    tail++;
    while (head < tail) {
        int u = que[head];
        head++;
        for (int v = 1; v <= n; v++) {
            if (conn[u][v] && dist[v] == -1) {
                dist[v] = dist[u] + 1;
                que[tail] = v;
                tail++;
            }
        }
    }
}

void solve() {
    bfs();
    // 乘车次数减 1 就是换车次数；不可达输出 NO
    if (dist[n] == -1)
        cout << "NO" << endl;
    else
        cout << max(0, dist[n] - 1) << endl;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
