#include <bits/stdc++.h>
using namespace std;

const int MAXM = 1005;
const long long NEG_INF = -(1LL << 60);

struct Point {
    int y;
    long long v;
    long long dp;
};

struct Line {
    long long k, b;
};

// 按列存点：col[x] 里保存所有横坐标为 x 的岛，按 y 从小到大处理。
vector<Point> col[MAXM];

// best_value[x][y]：同一个格子可能在输入中重复出现，保留价值最大的那个岛即可。
long long best_value[MAXM][MAXM];

int n, m;

// 每一行各维护一个上凸壳，用来做最大值查询。
struct Hull {
    vector<Line> q;
    int head = 0;

    void clear() {
        q.clear();
        head = 0;
    }

    bool empty() const {
        return head >= (int) q.size();
    }

    long long value(const Line &line, long long x) const {
        return line.k * x + line.b;
    }

    // 判断中间那条线是否永远不会成为最优。
    bool bad(const Line &a, const Line &b, const Line &c) const {
        __int128 left = (__int128) (a.b - b.b) * (c.k - b.k);
        __int128 right = (__int128) (b.b - c.b) * (b.k - a.k);
        return left >= right;
    }

    void add_line(long long k, long long b) {
        Line line;
        line.k = k;
        line.b = b;
        while ((int) q.size() - head >= 2 && bad(q[(int) q.size() - 2], q[(int) q.size() - 1], line)) {
            q.pop_back();
        }
        q.push_back(line);
    }

    long long query(long long x) {
        while ((int) q.size() - head >= 2 && value(q[head], x) <= value(q[head + 1], x)) {
            head++;
        }
        return value(q[head], x);
    }
};

Hull row_hull[MAXM];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            best_value[i][j] = -1;
        }
        col[i].clear();
        row_hull[i].clear();
    }

    for (int i = 1; i <= n; i++) {
        int x, y;
        long long v;
        cin >> x >> y >> v;
        best_value[x][y] = max(best_value[x][y], v);
    }

    for (int x = 1; x <= m; x++) {
        for (int y = 1; y <= m; y++) {
            if (best_value[x][y] >= 0) {
                Point p;
                p.y = y;
                p.v = best_value[x][y];
                p.dp = NEG_INF;
                col[x].push_back(p);
            }
        }
    }

    long long answer = NEG_INF;

    // g[y]：从之前的列转移到当前列时，最后一个点的纵坐标恰好为 y 的最优值。
    static long long g[MAXM];

    for (int x = 1; x <= m; x++) {
        if (col[x].empty()) {
            continue;
        }

        for (int y = 1; y <= m; y++) {
            g[y] = NEG_INF;
            if (!row_hull[y].empty()) {
                g[y] = row_hull[y].query(x);
            }
        }

        Hull prefix_hull;
        Hull same_column_hull;
        int add_y = 1;

        for (unsigned int i = 0; i < col[x].size(); i++) {
            int y = col[x][i].y;
            long long v = col[x][i].v;

            // 把所有 y' <= y 的历史状态加入前缀凸壳，
            // 对应“前一个点在更左边的列，且纵坐标也不超过当前点”。
            while (add_y <= y) {
                if (g[add_y] > NEG_INF / 2) {
                    prefix_hull.add_line(2LL * add_y, g[add_y]);
                }
                add_y++;
            }

            long long best = NEG_INF;

            if (!prefix_hull.empty()) {
                best = max(best, -1LL * x * x - 1LL * y * y + prefix_hull.query(y));
            }

            // 同一列内还能继续往下走，此时横坐标差是 0，只需要处理纵坐标代价。
            if (!same_column_hull.empty()) {
                best = max(best, -1LL * y * y + same_column_hull.query(y));
            }

            if (x == 1 && y == 1) {
                // 起点必须拿到。
                col[x][i].dp = v;
            } else if (best > NEG_INF / 2) {
                col[x][i].dp = best + v;
            }

            if (col[x][i].dp > NEG_INF / 2) {
                // 给同一列后面的点做转移：
                // dp[j] - (y - yj)^2 = -y^2 + (2*yj)*y + (dp[j] - yj^2)
                same_column_hull.add_line(2LL * y, col[x][i].dp - 1LL * y * y);
            }

            if (x == m && y == m) {
                answer = col[x][i].dp;
            }
        }

        // 当前列处理完后，把这些点作为未来列的候选前驱加入各自行对应的凸壳。
        for (unsigned int i = 0; i < col[x].size(); i++) {
            int y = col[x][i].y;
            long long dp = col[x][i].dp;
            if (dp <= NEG_INF / 2) {
                continue;
            }
            // dp[j] - (x - xj)^2 - (y - yj)^2
            // = -x^2 - y^2 + (2*xj)*x + (2*yj)*y + (dp[j] - xj^2 - yj^2)
            // 对固定 yj 的这一行来说，查询横坐标 x 时就是一条直线。
            row_hull[y].add_line(2LL * x, dp - 1LL * x * x - 1LL * y * y);
        }
    }

    cout << answer << '\n';
    return 0;
}
