#include <bits/stdc++.h>
using namespace std;

const int MAXN = 5005;
const long long INF = (1LL << 62);

int n;
long long x[MAXN], y[MAXN];
long long dist_to_tree[MAXN];
bool vis[MAXN];

long long dis2(int i, int j) {
    long long dx = x[i] - x[j];
    long long dy = y[i] - y[j];
    return dx * dx + dy * dy;
}

long double prim() {
    for (int i = 1; i <= n; i++) {
        dist_to_tree[i] = INF;
        vis[i] = false;
    }

    dist_to_tree[1] = 0;
    long double answer = 0;

    for (int i = 1; i <= n; i++) {
        int u = 0;
        for (int j = 1; j <= n; j++) {
            if (vis[j]) {
                continue;
            }
            if (u == 0 || dist_to_tree[j] < dist_to_tree[u]) {
                u = j;
            }
        }

        vis[u] = true;
        answer += sqrtl((long double)dist_to_tree[u]);

        for (int v = 1; v <= n; v++) {
            if (vis[v]) {
                continue;
            }
            long long w = dis2(u, v);
            if (w < dist_to_tree[v]) {
                dist_to_tree[v] = w;
            }
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> y[i];
    }

    cout << fixed << setprecision(2) << (double)prim() << '\n';

    return 0;
}
