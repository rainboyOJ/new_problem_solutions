// brute.cpp：枚举每一条边，把它长度加倍后用 Floyd 求最短路。
// 只适合小数据，但非常直观，适合帮助理解和对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;
const int MAXM = 5005;
const long long INF = (1LL << 60);

int n, m;
int eu[MAXM], ev[MAXM];
long long ew[MAXM];
long long dist_arr[MAXN][MAXN];

void build_graph(int doubled_edge_id) {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (i == j) {
                dist_arr[i][j] = 0;
            }
            else {
                dist_arr[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= m; i++) {
        long long len = ew[i];
        if (i == doubled_edge_id) {
            len *= 2;
        }

        if (len < dist_arr[eu[i]][ev[i]]) {
            dist_arr[eu[i]][ev[i]] = len;
            dist_arr[ev[i]][eu[i]] = len;
        }
    }
}

void floyd() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {
                if (dist_arr[i][k] + dist_arr[k][j] < dist_arr[i][j]) {
                    dist_arr[i][j] = dist_arr[i][k] + dist_arr[k][j];
                }
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        cin >> eu[i] >> ev[i] >> ew[i];
    }

    build_graph(0);
    floyd();
    long long original_dist = dist_arr[1][n];

    long long answer = 0;
    for (int i = 1; i <= m; i++) {
        build_graph(i);
        floyd();
        answer = max(answer, dist_arr[1][n] - original_dist);
    }

    cout << answer << '\n';

    return 0;
}
