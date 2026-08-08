#include <bits/stdc++.h>
using namespace std;

const int MAXM = 505;
const int MAXN = 1005;
const long long INF = (1LL << 62);

int monkey_cnt, tree_cnt;
long long jump_len[MAXM];
long long x[MAXN], y[MAXN];
long long dist_to_tree[MAXN];
bool vis[MAXN];

long long dis2(int i, int j) {
    long long dx = x[i] - x[j];
    long long dy = y[i] - y[j];
    return dx * dx + dy * dy;
}

long long prim_need() {
    for (int i = 1; i <= tree_cnt; i++) {
        dist_to_tree[i] = INF;
        vis[i] = false;
    }

    dist_to_tree[1] = 0;
    long long need = 0;

    for (int i = 1; i <= tree_cnt; i++) {
        int u = 0;
        for (int j = 1; j <= tree_cnt; j++) {
            if (vis[j]) {
                continue;
            }
            if (u == 0 || dist_to_tree[j] < dist_to_tree[u]) {
                u = j;
            }
        }

        vis[u] = true;
        need = max(need, dist_to_tree[u]);

        for (int v = 1; v <= tree_cnt; v++) {
            if (vis[v]) {
                continue;
            }
            long long w = dis2(u, v);
            if (w < dist_to_tree[v]) {
                dist_to_tree[v] = w;
            }
        }
    }

    return need;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> monkey_cnt;
    for (int i = 1; i <= monkey_cnt; i++) {
        cin >> jump_len[i];
    }

    cin >> tree_cnt;
    for (int i = 1; i <= tree_cnt; i++) {
        cin >> x[i] >> y[i];
    }

    long long need = prim_need();

    int answer = 0;
    for (int i = 1; i <= monkey_cnt; i++) {
        if (jump_len[i] * jump_len[i] >= need) {
            answer++;
        }
    }

    cout << answer << '\n';

    return 0;
}
