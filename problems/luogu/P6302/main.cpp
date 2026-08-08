#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 62);
const int MAXN = 100005;
const int MAXM = 1000005;

struct Train {
    int x, y, p, q;
} tr[MAXM];

struct Line {
    long long k, b;
};

int n, m;
long long A, B, C;
long long dp[MAXM];
vector<int> depart_at[40005];
vector<int> arrive_at[40005];

// 每个站维护一个下凸壳，表示已经到达该站的所有方案。
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

    // 下凸壳判劣。
    bool bad(const Line &a, const Line &b, const Line &c) const {
        __int128 left = (__int128) (b.b - a.b) * (b.k - c.k);
        __int128 right = (__int128) (c.b - b.b) * (a.k - b.k);
        return left >= right;
    }

    void add_line(long long k, long long b) {
        Line line;
        line.k = k;
        line.b = b;
        if (!q.empty() && q.back().k == line.k) {
            if (q.back().b <= line.b) {
                return;
            }
            q.pop_back();
            if (head > (int) q.size()) {
                head = (int) q.size();
            }
        }
        while ((int) q.size() - head >= 2 && bad(q[(int) q.size() - 2], q[(int) q.size() - 1], line)) {
            q.pop_back();
        }
        q.push_back(line);
    }

    long long query(long long x) {
        while ((int) q.size() - head >= 2 && value(q[head], x) >= value(q[head + 1], x)) {
            head++;
        }
        return value(q[head], x);
    }
};

Hull station_hull[MAXN];

long long wait_cost(long long t) {
    return A * t * t + B * t + C;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> A >> B >> C;
    for (int i = 1; i <= m; i++) {
        cin >> tr[i].x >> tr[i].y >> tr[i].p >> tr[i].q;
        depart_at[tr[i].p].push_back(i);
        arrive_at[tr[i].q].push_back(i);
    }

    // 起点站 1 在时刻 0 就已经可以开始等待。
    // 若下一班车在时刻 p 发车，那么代价就是：
    // A p^2 + B p + C
    station_hull[1].add_line(-2LL * A * 0, 0);

    long long answer = INF;

    for (int t = 0; t <= 40000; t++) {
        // 先处理这个时刻到达的列车，因为 q_u <= p_v，允许到站后立刻换乘同一时刻发车的车。
        for (unsigned int idx = 0; idx < arrive_at[t].size(); idx++) {
            int id = arrive_at[t][idx];
            if (dp[id] >= INF / 2) {
                continue;
            }
            int y = tr[id].y;
            int q = tr[id].q;

            // 若之后在时刻 p >= q 从这个站继续走，
            // 新增等待代价是 A(p-q)^2 + B(p-q) + C。
            // 展开后关于 p 的部分为：
            // A p^2 + B p + C + (-2Aq) * p + (dp + Aq^2 - Bq)
            // 所以插入一条斜率 -2Aq 的直线。
            long long k = -2LL * A * q;
            long long b = dp[id] + A * 1LL * q * q - B * 1LL * q;
            station_hull[y].add_line(k, b);
        }

        for (unsigned int idx = 0; idx < depart_at[t].size(); idx++) {
            int id = depart_at[t][idx];
            int x = tr[id].x;
            int p = tr[id].p;

            dp[id] = INF;
            if (station_hull[x].empty()) {
                continue;
            }

            long long best = station_hull[x].query(p);
            dp[id] = A * 1LL * p * p + B * 1LL * p + C + best;

            if (tr[id].y == n) {
                answer = min(answer, dp[id] + tr[id].q);
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
