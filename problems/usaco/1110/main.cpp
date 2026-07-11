/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 19:42
 * update_at: 2026-07-11 19:44
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXG = 3005;
const int SHIFT = 1000;

int n;
bool has_cow[MAXG][MAXG];
queue<pair<int, int> > q;
int total_cows;

int dx[4] = {1, -1, 0, 0};
int dy[4] = {0, 0, 1, -1};

void check_comfortable(int x, int y) {
    if (!has_cow[x][y]) return;

    int cnt = 0;
    int empty_x = -1;
    int empty_y = -1;

    for (int d = 0; d < 4; d++) {
        int nx = x + dx[d];
        int ny = y + dy[d];
        if (has_cow[nx][ny]) {
            cnt++;
        } else {
            empty_x = nx;
            empty_y = ny;
        }
    }

    if (cnt == 3) {
        q.push(make_pair(empty_x, empty_y));
    }
}

void process_queue() {
    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (has_cow[x][y]) continue;

        has_cow[x][y] = true;
        total_cows++;

        check_comfortable(x, y);
        for (int d = 0; d < 4; d++) {
            check_comfortable(x + dx[d], y + dy[d]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        int x, y;
        cin >> x >> y;
        x += SHIFT;
        y += SHIFT;

        q.push(make_pair(x, y));
        process_queue();

        cout << total_cows - i << '\n';
    }

    return 0;
}
