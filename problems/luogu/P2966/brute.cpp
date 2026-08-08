#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
const int MAXM = 505;
const long long INF = (1LL << 60);

struct Edge {
    int to;
    int w;
};

struct State {
    int u;
    int rank_id;
    long long edge_sum;

    bool operator < (const State &other) const {
        return edge_sum > other.edge_sum;
    }
};

int n, m, q;
int toll_fee[MAXN];
int toll_rank[MAXN];
int toll_value[MAXN];
long long dist_state[MAXN][MAXN];
vector<Edge> g[MAXN];

int prepare_ranks() {
    vector<int> vals;
    for (int i = 1; i <= n; i++) {
        vals.push_back(toll_fee[i]);
    }
    sort(vals.begin(), vals.end());
    vals.erase(unique(vals.begin(), vals.end()), vals.end());

    int cnt = (int) vals.size();
    for (int i = 1; i <= cnt; i++) {
        toll_value[i] = vals[i - 1];
    }
    for (int i = 1; i <= n; i++) {
        toll_rank[i] = lower_bound(vals.begin(), vals.end(), toll_fee[i]) - vals.begin() + 1;
    }
    return cnt;
}

long long solve_one_query(int s, int t, int rank_cnt) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= rank_cnt; j++) {
            dist_state[i][j] = INF;
        }
    }

    priority_queue<State> pq;
    dist_state[s][toll_rank[s]] = 0;
    pq.push({s, toll_rank[s], 0});

    while (!pq.empty()) {
        State cur = pq.top();
        pq.pop();

        int u = cur.u;
        int rk = cur.rank_id;
        long long edge_sum = cur.edge_sum;

        if (edge_sum != dist_state[u][rk]) {
            continue;
        }

        for (size_t i = 0; i < g[u].size(); i++) {
            int v = g[u][i].to;
            int nr = max(rk, toll_rank[v]);
            long long nd = edge_sum + g[u][i].w;

            if (nd < dist_state[v][nr]) {
                dist_state[v][nr] = nd;
                pq.push({v, nr, nd});
            }
        }
    }

    long long ret = INF;
    for (int rk = 1; rk <= rank_cnt; rk++) {
        if (dist_state[t][rk] >= INF / 2) {
            continue;
        }
        long long total_cost = dist_state[t][rk] + toll_value[rk];
        if (total_cost < ret) {
            ret = total_cost;
        }
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> q;

    for (int i = 1; i <= n; i++) {
        cin >> toll_fee[i];
        g[i].clear();
    }

    for (int i = 1; i <= m; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        g[u].push_back({v, len});
        g[v].push_back({u, len});
    }

    int rank_cnt = prepare_ranks();

    for (int i = 1; i <= q; i++) {
        int s, t;
        cin >> s >> t;
        cout << solve_one_query(s, t, rank_cnt) << '\n';
    }

    return 0;
}
