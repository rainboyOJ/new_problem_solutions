// brute.cpp：小数据最短路，状态为“到达哪个站点、还剩多少公里油量”。
#include <bits/stdc++.h>
using namespace std;

const long long INF = (1LL << 60);
const int MAXN = 25;
const int MAXF = 405;

struct Node {
    long long cost;
    int pos;
    int fuel;

    bool operator < (const Node &other) const {
        return cost > other.cost;
    }
};

int n, d;
int v[MAXN];
int a[MAXN];
long long dista[MAXN][MAXF];
int max_fuel;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    for (int i = 1; i <= n - 1; i++) {
        cin >> v[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    max_fuel = 0;
    for (int i = 1; i <= n - 1; i++) {
        max_fuel += v[i];
    }
    // 因为只能按整升买油，最优解中油量可能会比“刚好够剩余路程”多出不到 d 公里。
    max_fuel += d;

    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= max_fuel; j++) {
            dista[i][j] = INF;
        }
    }

    priority_queue<Node> q;
    dista[1][0] = 0;
    q.push((Node){0, 1, 0});

    while (!q.empty()) {
        Node cur = q.top();
        q.pop();

        if (cur.cost != dista[cur.pos][cur.fuel]) {
            continue;
        }

        if (cur.pos == n) {
            cout << cur.cost << '\n';
            return 0;
        }

        // 在当前站点买一升油。
        if (cur.fuel + d <= max_fuel && dista[cur.pos][cur.fuel + d] > cur.cost + a[cur.pos]) {
            dista[cur.pos][cur.fuel + d] = cur.cost + a[cur.pos];
            q.push((Node){dista[cur.pos][cur.fuel + d], cur.pos, cur.fuel + d});
        }

        // 油量足够时，直接开到下一站。
        if (cur.fuel >= v[cur.pos] && dista[cur.pos + 1][cur.fuel - v[cur.pos]] > cur.cost) {
            dista[cur.pos + 1][cur.fuel - v[cur.pos]] = cur.cost;
            q.push((Node){cur.cost, cur.pos + 1, cur.fuel - v[cur.pos]});
        }
    }

    return 0;
}
