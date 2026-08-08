// main.cpp：二分完成天数，把每个点转成最晚种植日，再做树上 EDF 调度。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long need_h[MAXN], b[MAXN], c[MAXN];
vector<int> g[MAXN], child[MAXN];
int deadline_day[MAXN];
int min_subtree_deadline[MAXN];
vector<int> order_nodes;

__int128 sum_linear(long long bb, long long cc, long long l, long long r) {
    if (l > r) {
        return 0;
    }
    __int128 cnt = (__int128)r - l + 1;
    __int128 sum_x = (__int128)(l + r) * cnt / 2;
    return (__int128)bb * cnt + (__int128)cc * sum_x;
}

__int128 growth_sum(int u, long long l, long long r) {
    if (l > r) {
        return 0;
    }
    if (c[u] >= 0) {
        return sum_linear(b[u], c[u], l, r);
    }

    long long dec = -c[u];
    long long last_big = (b[u] - 1) / dec; // x <= last_big 时 b-c*x 至少为 1
    long long mid = min(r, last_big);
    __int128 result = 0;
    if (l <= mid) {
        result += sum_linear(b[u], c[u], l, mid);
    }
    if (mid + 1 <= r) {
        result += (__int128)r - (mid + 1) + 1;
    }
    return result;
}

int calc_deadline(int u, long long total_day) {
    if (growth_sum(u, 1, total_day) < need_h[u]) {
        return 0;
    }

    long long left = 1;
    long long right = total_day;
    while (left < right) {
        long long mid = (left + right + 1) / 2;
        if (growth_sum(u, mid, total_day) >= need_h[u]) {
            left = mid;
        } else {
            right = mid - 1;
        }
    }

    if (left > n) {
        return n;
    }
    return (int)left;
}

bool check(long long total_day) {
    if (total_day < n) {
        return false;
    }

    for (int i = 1; i <= n; i++) {
        deadline_day[i] = calc_deadline(i, total_day);
        if (deadline_day[i] == 0) {
            return false;
        }
    }

    for (int i = (int)order_nodes.size() - 1; i >= 0; i--) {
        int u = order_nodes[i];
        min_subtree_deadline[u] = deadline_day[u];
        for (int j = 0; j < (int)child[u].size(); j++) {
            int v = child[u][j];
            min_subtree_deadline[u] = min(min_subtree_deadline[u], min_subtree_deadline[v]);
        }
    }

    priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;
    q.push(make_pair(min_subtree_deadline[1], 1));

    for (int day = 1; day <= n; day++) {
        if (q.empty()) {
            return false;
        }
        int u = q.top().second;
        q.pop();
        if (deadline_day[u] < day) {
            return false;
        }
        for (int i = 0; i < (int)child[u].size(); i++) {
            int v = child[u][i];
            q.push(make_pair(min_subtree_deadline[v], v));
        }
    }

    return true;
}

void build_rooted_tree() {
    vector<int> parent(n + 1, 0);
    queue<int> q;
    parent[1] = -1;
    q.push(1);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        order_nodes.push_back(u);
        for (int i = 0; i < (int)g[u].size(); i++) {
            int v = g[u][i];
            if (v == parent[u]) {
                continue;
            }
            parent[v] = u;
            child[u].push_back(v);
            q.push(v);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> need_h[i] >> b[i] >> c[i];
    }
    for (int i = 1; i < n; i++) {
        int u, v;
        cin >> u >> v;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    build_rooted_tree();

    long long left = 1;
    long long right = 1000000000LL;
    while (left < right) {
        long long mid = (left + right) / 2;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << left << '\n';
    return 0;
}
