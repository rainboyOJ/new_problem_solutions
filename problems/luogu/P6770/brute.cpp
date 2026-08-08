// brute.cpp：用 Floyd 求 1 号草地到所有点的最短路，再检查每头牛是否能在 M 秒内到达。
// 只适合小数据，但更贴近题意。
#include <bits/stdc++.h>
using namespace std;

const int MAXF = 105;
const long long INF = (1LL << 60);

int f, p, c, m_limit;
int cow_pos[105];
long long dist_arr[MAXF][MAXF];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> f >> p >> c >> m_limit;

    for (int i = 1; i <= f; i++) {
        for (int j = 1; j <= f; j++) {
            if (i == j) {
                dist_arr[i][j] = 0;
            }
            else {
                dist_arr[i][j] = INF;
            }
        }
    }

    for (int i = 1; i <= p; i++) {
        int u, v, len;
        cin >> u >> v >> len;
        if (len < dist_arr[u][v]) {
            dist_arr[u][v] = len;
            dist_arr[v][u] = len;
        }
    }

    for (int i = 1; i <= c; i++) {
        cin >> cow_pos[i];
    }

    for (int k = 1; k <= f; k++) {
        for (int i = 1; i <= f; i++) {
            for (int j = 1; j <= f; j++) {
                if (dist_arr[i][k] + dist_arr[k][j] < dist_arr[i][j]) {
                    dist_arr[i][j] = dist_arr[i][k] + dist_arr[k][j];
                }
            }
        }
    }

    vector<int> answer;
    for (int i = 1; i <= c; i++) {
        if (dist_arr[1][cow_pos[i]] <= m_limit) {
            answer.push_back(i);
        }
    }

    cout << answer.size() << '\n';
    for (size_t i = 0; i < answer.size(); i++) {
        cout << answer[i] << '\n';
    }

    return 0;
}
