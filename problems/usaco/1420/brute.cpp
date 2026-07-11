/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 15:44
 * update_at: 2026-07-11 15:46
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXC = 1005;
const int MAXP = 200005;

int n, p;
int x_pos[MAXP], y_pos[MAXP];
int label[MAXC][MAXC];
vector<pair<int, int> > path_points; // 按围栏行走顺序记录所有整数点。

int sign(int x) {
    if (x > 0) return 1;
    if (x < 0) return -1;
    return 0;
}

void walk_segment(int x1, int y1, int x2, int y2) {
    int dx = sign(x2 - x1);
    int dy = sign(y2 - y1);
    int dist = abs(x2 - x1) + abs(y2 - y1);

    int x = x1;
    int y = y1;
    for (int step = 0; step < dist; step++) {
        path_points.push_back(make_pair(x, y));
        x += dx;
        y += dy;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> p;

    for (int x = 0; x < MAXC; x++) {
        for (int y = 0; y < MAXC; y++) {
            label[x][y] = -1;
        }
    }

    for (int i = 1; i <= p; i++) {
        cin >> x_pos[i] >> y_pos[i];
    }

    for (int i = 1; i <= p; i++) {
        int j = i + 1;
        if (j == p + 1) j = 1;
        walk_segment(x_pos[i], y_pos[i], x_pos[j], y_pos[j]);
    }

    for (int i = 0; i < (int)path_points.size(); i++) {
        int x = path_points[i].first;
        int y = path_points[i].second;
        label[x][y] = i;
    }

    int perimeter = (int)path_points.size();

    while (n--) {
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;

        int d = abs(label[x1][y1] - label[x2][y2]);
        cout << min(d, perimeter - d) << '\n';
    }

    return 0;
}
