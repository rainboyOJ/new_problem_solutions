/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-03 10:35
 * update_at: 2026-10-03 10:35
 */
// P1514 [NOIP 2010 提高组] 引水入城
// 思路：
//   1. 水只能从高处流向低处，把一个城市有水的效果看成“从第 1 行某座城市出发，
//      沿着只往低处走的有向边能到达哪些城市”。
//   2. 所以第 1 行每座城市都当作一次 BFS 的源，算出它能灌溉的干旱区城市。
//      干旱区里任何一座都没被覆盖，方案就不存在，直接输出 0 和不可能通水的城市数。
//   3. 若所有干旱区城市都能被覆盖，则每个蓄水厂能覆盖的干旱区城市恰好是
//      连续的一段（关键性质，见题解证明），于是问题变成“用最少的区间覆盖 [1, m]”，
//      按左端点排序后贪心即可。
#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>
using namespace std;

const int MAXN = 505;
const int MAXC = MAXN * MAXN;

int n, m;
int h[MAXN][MAXN];     // h[i][j]：第 i 行第 j 列城市的海拔高度
int seen[MAXN][MAXN];  // 当前这次 BFS 的访问标记：值等于 stamp 表示本次访问过
int stamp;             // BFS 时间戳，递增后就不用每次清空 seen 数组
int able[MAXN];        // able[j]：干旱区第 j 列是否被某个蓄水厂覆盖
int segL[MAXN];        // 第 1 行第 j 列建蓄水厂时，覆盖的干旱区列区间左端点
int segR[MAXN];        // 右端点；区间为空时 segL = m + 1、segR = 0
int qx[MAXC], qy[MAXC]; // 手写 BFS 队列，存城市坐标

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

// 从第 1 行第 sy 列的城市建一个蓄水厂出发做 BFS，
// 求出它实际上能灌溉到的干旱区城市列区间 [segL[sy], segR[sy]]。
// 能通水的干旱区城市同时标进 able[]。
void flood(int sy) {
    stamp++;
    int head = 0, tail = 0;
    qx[tail] = 1;
    qy[tail] = sy;
    tail++;
    seen[1][sy] = stamp;

    int left = m + 1; // 覆盖到的最右小列
    int right = 0;    // 覆盖到的最右列

    while (head < tail) {
        int x = qx[head];
        int y = qy[head];
        head++;

        if (x == n) { // 走到第 n 行，说明这座干旱区城市可以通水
            if (y < left) left = y;
            if (y > right) right = y;
            able[y] = 1;
        }

        for (int d = 0; d < 4; d++) {
            int nx = x + dx[d];
            int ny = y + dy[d];
            if (nx < 1 || nx > n || ny < 1 || ny > m) continue;
            if (seen[nx][ny] == stamp) continue;
            if (h[nx][ny] >= h[x][y]) continue; // 水只能由高处流向低处
            seen[nx][ny] = stamp;
            qx[tail] = nx;
            qy[tail] = ny;
            tail++;
        }
    }

    segL[sy] = left;
    segR[sy] = right;
}

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cin >> h[i][j];
        }
    }
}

void solve() {
    for (int j = 1; j <= m; j++) {
        flood(j);
    }

    // 干旱区中一座城市如果没有任何蓄水厂能覆盖，方案就不存在。
    int bad = 0;
    for (int j = 1; j <= m; j++) {
        if (able[j] == 0) bad++;
    }
    if (bad > 0) {
        cout << 0 << "\n" << bad << "\n";
        return;
    }

    // 可行时每个蓄水厂覆盖的干旱区城市是一段连续区间，
    // 收集所有非空区间，按左端点排序。
    vector<pair<int, int> > seg;
    for (int j = 1; j <= m; j++) {
        if (segL[j] <= segR[j]) {
            seg.push_back(make_pair(segL[j], segR[j]));
        }
    }
    sort(seg.begin(), seg.end());

    // 贪心：下一个待覆盖的城市是 pos，在左端点不超过 pos 的区间里挑右端点最远的。
    int ans = 0;
    int pos = 1;
    int i = 0;
    while (pos <= m) {
        int far = pos - 1;
        while (i < (int)seg.size() && seg[i].first <= pos) {
            if (seg[i].second > far) far = seg[i].second;
            i++;
        }
        ans++;
        pos = far + 1;
    }

    cout << 1 << "\n" << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
