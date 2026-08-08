#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int INF = 1e9;

int n;
char grid[MAXN][MAXN];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

struct CowState {
    int x, y, dir;
};

struct State {
    CowState a, b;
};

map<tuple<int, int, int, int, int, int>, int> dista;

bool inside(int x, int y) {
    return x >= 0 && x < n && y >= 0 && y < n;
}

bool is_goal(int x, int y) {
    return x == 0 && y == n - 1;
}

CowState move_forward(CowState s) {
    if (is_goal(s.x, s.y)) {
        return s;
    }
    int nx = s.x + dx[s.dir];
    int ny = s.y + dy[s.dir];
    if (!inside(nx, ny) || grid[nx][ny] == 'H') {
        return s;
    }
    s.x = nx;
    s.y = ny;
    return s;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }

    queue<State> q;
    State start;
    start.a = {n - 1, 0, 0};
    start.b = {n - 1, 0, 1};

    tuple<int, int, int, int, int, int> key =
        make_tuple(start.a.x, start.a.y, start.a.dir, start.b.x, start.b.y, start.b.dir);
    dista[key] = 0;
    q.push(start);

    while (!q.empty()) {
        State cur = q.front();
        q.pop();

        tuple<int, int, int, int, int, int> cur_key =
            make_tuple(cur.a.x, cur.a.y, cur.a.dir, cur.b.x, cur.b.y, cur.b.dir);
        int now = dista[cur_key];

        if (is_goal(cur.a.x, cur.a.y) && is_goal(cur.b.x, cur.b.y)) {
            cout << now << '\n';
            return 0;
        }

        // 左转
        State s1 = cur;
        s1.a.dir = (s1.a.dir + 3) % 4;
        s1.b.dir = (s1.b.dir + 3) % 4;
        tuple<int, int, int, int, int, int> k1 =
            make_tuple(s1.a.x, s1.a.y, s1.a.dir, s1.b.x, s1.b.y, s1.b.dir);
        if (!dista.count(k1)) {
            dista[k1] = now + 1;
            q.push(s1);
        }

        // 右转
        State s2 = cur;
        s2.a.dir = (s2.a.dir + 1) % 4;
        s2.b.dir = (s2.b.dir + 1) % 4;
        tuple<int, int, int, int, int, int> k2 =
            make_tuple(s2.a.x, s2.a.y, s2.a.dir, s2.b.x, s2.b.y, s2.b.dir);
        if (!dista.count(k2)) {
            dista[k2] = now + 1;
            q.push(s2);
        }

        // 前进
        State s3 = cur;
        s3.a = move_forward(s3.a);
        s3.b = move_forward(s3.b);
        tuple<int, int, int, int, int, int> k3 =
            make_tuple(s3.a.x, s3.a.y, s3.a.dir, s3.b.x, s3.b.y, s3.b.dir);
        if (!dista.count(k3)) {
            dista[k3] = now + 1;
            q.push(s3);
        }
    }

    return 0;
}
