#include <bits/stdc++.h>
using namespace std;

// brute.cpp：按操作顺序直接修改、直接统计区间不同颜色，只适合小数据。

const int MAXN = 505;
const int MAXV = 1005;

int n, m;
int color[MAXN];
int seen[MAXV];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> color[i];
    }
    for (int i = 1; i <= m; i++) {
        char op;
        int x, y;
        cin >> op >> x >> y;
        if (op == 'Q') {
            for (int c = 0; c < MAXV; c++) {
                seen[c] = 0;
            }
            int answer = 0;
            for (int j = x; j <= y; j++) {
                if (!seen[color[j]]) {
                    seen[color[j]] = 1;
                    answer++;
                }
            }
            cout << answer << '\n';
        } else {
            color[x] = y;
        }
    }

    return 0;
}
