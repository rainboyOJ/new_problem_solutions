#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1055;

int n;
int target_x, target_y;
int x[MAXN], y[MAXN], r[MAXN];
vector<int> g[MAXN];
int root_id, target_id;
bool vis[MAXN];
bool found_answer;
long double answer_sum;

bool touch(int i, int j) {
    long long dx = 1LL * x[i] - x[j];
    long long dy = 1LL * y[i] - y[j];
    long long sum_r = 1LL * r[i] + r[j];
    return dx * dx + dy * dy == sum_r * sum_r;
}

void build_graph() {
    for (int i = 1; i <= n; i++) {
        g[i].clear();
    }

    for (int i = 1; i <= n; i++) {
        for (int j = i + 1; j <= n; j++) {
            if (touch(i, j)) {
                g[i].push_back(j);
                g[j].push_back(i);
            }
        }
    }
}

void find_special_nodes() {
    root_id = 0;
    target_id = 0;
    for (int i = 1; i <= n; i++) {
        if (x[i] == 0 && y[i] == 0) {
            root_id = i;
        }
        if (x[i] == target_x && y[i] == target_y) {
            target_id = i;
        }
    }
}

// 朴素做法：在相切图里直接搜从驱动轮到目标轮的那条路径，
// 搜索过程中把当前滚轮速度和前面路径上的速度和一起传下去。
void dfs(int u, long double speed_now, long double sum_now) {
    if (found_answer) {
        return;
    }

    vis[u] = true;
    sum_now += fabsl(speed_now);

    if (u == target_id) {
        answer_sum = sum_now;
        found_answer = true;
        vis[u] = false;
        return;
    }

    for (int i = 0; i < (int) g[u].size(); i++) {
        int v = g[u][i];
        if (vis[v]) {
            continue;
        }
        long double next_speed = -speed_now * (long double) r[u] / r[v];
        dfs(v, next_speed, sum_now);
    }

    vis[u] = false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> target_x >> target_y;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i] >> r[i];
    }

    build_graph();
    find_special_nodes();

    found_answer = false;
    answer_sum = 0.0L;
    memset(vis, 0, sizeof(vis));
    dfs(root_id, 10000.0L, 0.0L);

    cout << (long long) floorl(answer_sum + 1e-12L) << '\n';
    return 0;
}
