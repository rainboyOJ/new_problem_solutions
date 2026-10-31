#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 505;

ll a[MAXN];
int dist_u[MAXN];
ll ways[MAXN];
int q[MAXN];

void solve() {
    int n;
    ll d;
    if (scanf("%d%lld", &n, &d) != 2) return;
    for (int i = 1; i <= n; i++) {
        scanf("%lld", &a[i]);
    }

    ll ans = 0;
    // 暴力枚举起点 u，通过单源最短路 BFS 统计到达所有点 v 的最短路条数
    for (int u = 1; u <= n; u++) {
        for (int i = 1; i <= n; i++) {
            dist_u[i] = -1;
            ways[i] = 0;
        }
        dist_u[u] = 0;
        ways[u] = 1;
        int head = 0, tail = 0;
        q[tail++] = u;

        while (head < tail) {
            int cur = q[head++];
            for (int nxt = 1; nxt <= n; nxt++) {
                if (abs(a[nxt] - a[cur]) <= d) {
                    if (dist_u[nxt] == -1) {
                        dist_u[nxt] = dist_u[cur] + 1;
                        ways[nxt] = ways[cur];
                        q[tail++] = nxt;
                    } else if (dist_u[nxt] == dist_u[cur] + 1) {
                        ways[nxt] += ways[cur];
                    }
                }
            }
        }

        for (int v = u + 1; v <= n; v++) {
            if (ways[v] == 2) {
                ans++;
            }
        }
    }

    printf("%lld\n", ans);
}

int main() {
    int c, t;
    if (scanf("%d%d", &c, &t) == 2) {
        while (t--) {
            solve();
        }
    }
    return 0;
}
