#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

const int INF = 0x3f3f3f3f;

struct Edge {
    int to, weight;
};

int t, n, m, k, p;
vector<vector<Edge>> adj;
vector<vector<Edge>> rev_adj;
vector<int> dist;
vector<int> rev_dist;
int dp[100005][55];
bool in_stack[100005][55];
bool has_infinity;

void dijkstra(int start, const vector<vector<Edge>>& graph, vector<int>& d) {
    d.assign(n + 1, INF);
    d[start] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, start});

    while (!pq.empty()) {
        auto [cdist, u] = pq.top();
        pq.pop();

        if (cdist > d[u]) continue;

        for (const auto& edge : graph[u]) {
            int v = edge.to;
            int w = edge.weight;
            if (d[u] + w < d[v]) {
                d[v] = d[u] + w;
                pq.push({d[v], v});
            }
        }
    }
}

int dfs(int u, int j) {
    if (dist[u] + j + rev_dist[u] > dist[n] + k) {
        return 0; // Pruning: Even with shortest path to end, it exceeds limit
    }
    
    if (in_stack[u][j]) {
        has_infinity = true;
        return 0;
    }
    
    if (dp[u][j] != -1) {
        return dp[u][j];
    }
    
    in_stack[u][j] = true;
    long long ways = 0;
    
    if (u == n) {
        ways = 1;
    }
    
    for (const auto& edge : adj[u]) {
        int v = edge.to;
        int w = edge.weight;
        int next_j = j + dist[u] + w - dist[v];
        
        if (next_j <= k) {
            ways = (ways + dfs(v, next_j)) % p;
            if (has_infinity) {
                in_stack[u][j] = false;
                return 0;
            }
        }
    }
    
    in_stack[u][j] = false;
    return dp[u][j] = ways;
}

void solve() {
    cin >> n >> m >> k >> p;
    adj.assign(n + 1, vector<Edge>());
    rev_adj.assign(n + 1, vector<Edge>());
    
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        adj[u].push_back({v, w});
        rev_adj[v].push_back({u, w});
    }
    
    dijkstra(1, adj, dist);
    dijkstra(n, rev_adj, rev_dist);
    
    for (int i = 1; i <= n; ++i) {
        for (int j = 0; j <= k; ++j) {
            dp[i][j] = -1;
            in_stack[i][j] = false;
        }
    }
    
    has_infinity = false;
    
    int ans = dfs(1, 0);
    
    if (has_infinity) {
        cout << -1 << "\n";
    } else {
        cout << ans << "\n";
    }
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
