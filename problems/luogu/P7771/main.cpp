#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
vector<int> graph[MAXN];
vector<int> weak[MAXN];
int indeg[MAXN], outdeg[MAXN], iter_[MAXN];
vector<int> path;

bool check_connected() {
    int start = 0;
    for (int i = 1; i <= n; i++) {
        if (indeg[i] + outdeg[i] > 0) {
            start = i;
            break;
        }
    }

    if (start == 0) {
        return true;
    }

    vector<int> vis(n + 1, 0);
    stack<int> st;
    st.push(start);
    vis[start] = 1;

    while (!st.empty()) {
        int u = st.top();
        st.pop();

        for (int v : weak[u]) {
            if (!vis[v]) {
                vis[v] = 1;
                st.push(v);
            }
        }
    }

    for (int i = 1; i <= n; i++) {
        if (indeg[i] + outdeg[i] > 0 && !vis[i]) {
            return false;
        }
    }
    return true;
}

int find_start() {
    int start_cnt = 0, end_cnt = 0;
    int start = 0;

    for (int i = 1; i <= n; i++) {
        if (outdeg[i] == indeg[i] + 1) {
            start_cnt++;
            start = i;
        } else if (indeg[i] == outdeg[i] + 1) {
            end_cnt++;
        } else if (indeg[i] != outdeg[i]) {
            return -1;
        }
    }

    if (start_cnt == 1 && end_cnt == 1) {
        return start;
    }
    if (start_cnt == 0 && end_cnt == 0) {
        for (int i = 1; i <= n; i++) {
            if (outdeg[i] > 0) {
                return i;
            }
        }
        return 1;
    }
    return -1;
}

void hierholzer(int start) {
    vector<int> st;
    st.push_back(start);

    while (!st.empty()) {
        int u = st.back();
        if (iter_[u] < (int) graph[u].size()) {
            int v = graph[u][iter_[u]++];
            st.push_back(v);
        } else {
            path.push_back(u);
            st.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;

    for (int i = 1; i <= n; i++) {
        graph[i].clear();
        weak[i].clear();
        indeg[i] = outdeg[i] = iter_[i] = 0;
    }

    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        weak[u].push_back(v);
        weak[v].push_back(u);
        outdeg[u]++;
        indeg[v]++;
    }

    for (int i = 1; i <= n; i++) {
        sort(graph[i].begin(), graph[i].end());
    }

    if (!check_connected()) {
        cout << "No\n";
        return 0;
    }

    int start = find_start();
    if (start == -1) {
        cout << "No\n";
        return 0;
    }

    path.clear();
    hierholzer(start);

    if ((int) path.size() != m + 1) {
        cout << "No\n";
        return 0;
    }

    for (int i = m; i >= 0; i--) {
        cout << path[i];
        if (i > 0) {
            cout << ' ';
        }
    }
    cout << '\n';

    return 0;
}
