// brute.cpp：直接 Floyd 求任意两点最短路。
// 规模小的时候很好理解，也适合拿来对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXP = 500 + 5;
const long long INF = (1LL << 60);

int p, f, c;
int fav[MAXP];
long long dist_arr[MAXP][MAXP];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> p >> f >> c;

    for (int i = 1; i <= f; i++) {
        cin >> fav[i];
    }

    for (int i = 1; i <= p; i++) {
        for (int j = 1; j <= p; j++) {
            if (i == j) {
                dist_arr[i][j] = 0;
            }
            else {
                dist_arr[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= c; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        if (w < dist_arr[u][v]) {
            dist_arr[u][v] = w;
            dist_arr[v][u] = w;
        }
    }

    for (int k = 1; k <= p; k++) {
        for (int i = 1; i <= p; i++) {
            for (int j = 1; j <= p; j++) {
                if (dist_arr[i][k] + dist_arr[k][j] < dist_arr[i][j]) {
                    dist_arr[i][j] = dist_arr[i][k] + dist_arr[k][j];
                }
            }
        }
    }

    int answer = 1;
    long long best_sum = INF;

    for (int i = 1; i <= p; i++) {
        long long cur_sum = 0;
        for (int j = 1; j <= f; j++) {
            cur_sum += dist_arr[i][fav[j]];
        }

        if (cur_sum < best_sum) {
            best_sum = cur_sum;
            answer = i;
        }
    }

    cout << answer << '\n';

    return 0;
}
