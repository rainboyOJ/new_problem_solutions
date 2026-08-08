#include <bits/stdc++.h>
using namespace std;

// brute.cpp：Floyd 求小数据可达性，再枚举买入点和卖出点。

const int MAXN = 55;

int n, m;
int price_city[MAXN];
bool reach[MAXN][MAXN];

void read_input() {
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> price_city[i];
    }

    for (int i = 1; i <= n; i++) {
        reach[i][i] = true;
    }

    for (int i = 1; i <= m; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        reach[x][y] = true;
        if (z == 2) {
            reach[y][x] = true;
        }
    }
}

void floyd_reach() {
    for (int k = 1; k <= n; k++) {
        for (int i = 1; i <= n; i++) {
            if (!reach[i][k]) {
                continue;
            }
            for (int j = 1; j <= n; j++) {
                if (reach[k][j]) {
                    reach[i][j] = true;
                }
            }
        }
    }
}

int solve_brute() {
    floyd_reach();
    int answer = 0;
    for (int buy = 1; buy <= n; buy++) {
        if (!reach[1][buy]) {
            continue;
        }
        for (int sell = 1; sell <= n; sell++) {
            if (reach[buy][sell] && reach[sell][n]) {
                answer = max(answer, price_city[sell] - price_city[buy]);
            }
        }
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    cout << solve_brute() << '\n';

    return 0;
}
