/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 11:40
 * update_at: 2026-10-06 11:40
 */

#include <iostream>
#include <queue>
using namespace std;

typedef long long ll;

const int MAXX = 105;
const int MAXY = 105;

// 八个方向：水平、垂直以及四条对角线
const int DX[8] = {-1, -1, -1, 0, 0, 1, 1, 1};
const int DY[8] = {-1, 0, 1, -1, 1, -1, 0, 1};

ll X, Y, Mx, My;

char grid[MAXY][MAXX]; // grid[y][x] 存第 y 行第 x 列的字符，'.' 为草地，'*' 为石头
ll dist[MAXY][MAXX];   // dist[y][x] 为格子 (x, y) 被占领的星期数，-1 表示未访问

// 队列节点：格子坐标，对应数组下标
struct Node {
    ll x;
    ll y;
};

queue<Node> q;

int main() {
    cin >> X >> Y >> Mx >> My;
    for (ll y = 1; y <= Y; y++) {
        for (ll x = 1; x <= X; x++) {
            cin >> grid[y][x];
            dist[y][x] = -1;
        }
    }

    // 起点在第 0 周就被占领，从它开始逐层 BFS 扩散
    dist[My][Mx] = 0;
    Node start;
    start.x = Mx;
    start.y = My;
    q.push(start);

    while (!q.empty()) {
        Node now = q.front();
        q.pop();
        for (int d = 0; d < 8; d++) {
            ll nx = now.x + DX[d];
            ll ny = now.y + DY[d];
            if (nx < 1 || nx > X || ny < 1 || ny > Y) {
                continue;
            }
            if (grid[ny][nx] == '*' || dist[ny][nx] != -1) {
                continue;
            }
            dist[ny][nx] = dist[now.y][now.x] + 1;
            Node nxt;
            nxt.x = nx;
            nxt.y = ny;
            q.push(nxt);
        }
    }

    // 答案是最晚被占领格子的星期数，石头的 -1 不影响取最大值
    ll answer = 0;
    for (ll y = 1; y <= Y; y++) {
        for (ll x = 1; x <= X; x++) {
            if (dist[y][x] > answer) {
                answer = dist[y][x];
            }
        }
    }
    cout << answer << endl;
    return 0;
}
