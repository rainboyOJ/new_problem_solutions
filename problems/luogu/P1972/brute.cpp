#include <bits/stdc++.h>
using namespace std;

// brute.cpp：每个询问直接用桶统计不同颜色，只适合小数据。

const int MAXN = 505;
const int MAXC = 1005;

int n, m;
int a[MAXN];
int seen[MAXC];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> m;
    for (int i = 1; i <= m; i++) {
        int l, r;
        cin >> l >> r;
        int answer = 0;
        for (int c = 0; c < MAXC; c++) {
            seen[c] = 0;
        }
        for (int j = l; j <= r; j++) {
            if (!seen[a[j]]) {
                seen[a[j]] = 1;
                answer++;
            }
        }
        cout << answer << '\n';
    }

    return 0;
}
