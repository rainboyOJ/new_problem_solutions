#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

typedef long long ll;

const int MAXN = 2005;
const int MAXV = 305;
const double INF = 1e18;

int n, m, v, e;
int c[MAXN], d[MAXN];
double k[MAXN];
int dis[MAXV][MAXV];

double f[MAXN][2];
double nf[MAXN][2];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    if (!(cin >> n >> m >> v >> e)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> c[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> d[i];
    }
    for (int i = 1; i <= n; ++i) {
        cin >> k[i];
    }

    for (int i = 1; i <= v; ++i) {
        for (int j = 1; j <= v; ++j) {
            if (i == j) dis[i][j] = 0;
            else dis[i][j] = 1e8;
        }
    }

    for (int i = 0; i < e; ++i) {
        int u, v_node, w;
        cin >> u >> v_node >> w;
        if (w < dis[u][v_node]) {
            dis[u][v_node] = w;
            dis[v_node][u] = w;
        }
    }

    for (int p = 1; p <= v; ++p) {
        for (int i = 1; i <= v; ++i) {
            for (int j = 1; j <= v; ++j) {
                if (dis[i][p] + dis[p][j] < dis[i][j]) {
                    dis[i][j] = dis[i][p] + dis[p][j];
                }
            }
        }
    }

    for (int j = 0; j <= m; ++j) {
        f[j][0] = f[j][1] = INF;
    }
    f[0][0] = 0.0;
    if (m >= 1) {
        f[1][1] = 0.0;
    }

    for (int i = 2; i <= n; ++i) {
        for (int j = 0; j <= m; ++j) {
            nf[j][0] = nf[j][1] = INF;
        }
        for (int j = 0; j <= min(i, m); ++j) {
            // 第 i 节课不申请
            double v1 = f[j][0] + dis[c[i-1]][c[i]];
            double v2 = f[j][1] + k[i-1] * dis[d[i-1]][c[i]] + (1.0 - k[i-1]) * dis[c[i-1]][c[i]];
            nf[j][0] = min(v1, v2);
            
            // 第 i 节课申请
            if (j > 0) {
                double v3 = f[j-1][0] + k[i] * dis[c[i-1]][d[i]] + (1.0 - k[i]) * dis[c[i-1]][c[i]];
                double v4 = f[j-1][1] + 
                            k[i-1] * k[i] * dis[d[i-1]][d[i]] + 
                            k[i-1] * (1.0 - k[i]) * dis[d[i-1]][c[i]] + 
                            (1.0 - k[i-1]) * k[i] * dis[c[i-1]][d[i]] + 
                            (1.0 - k[i-1]) * (1.0 - k[i]) * dis[c[i-1]][c[i]];
                nf[j][1] = min(v3, v4);
            }
        }
        for (int j = 0; j <= m; ++j) {
            f[j][0] = nf[j][0];
            f[j][1] = nf[j][1];
        }
    }

    double ans = INF;
    for (int j = 0; j <= m; ++j) {
        ans = min(ans, f[j][0]);
        ans = min(ans, f[j][1]);
    }

    cout << fixed << setprecision(2) << ans << "\n";

    return 0;
}
