#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n, k;
int a[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= i; j++) {
            cin >> a[i][j];
        }
    }

    long long answer = 0;

    // 枚举每个大小为 k 的正三角形的顶点。
    for (int i = 1; i + k - 1 <= n; i++) {
        for (int j = 1; j <= i; j++) {
            int best = 0;

            // 直接把这个子三角形里的所有点扫一遍，取最大值。
            for (int dx = 0; dx < k; dx++) {
                for (int dy = 0; dy <= dx; dy++) {
                    best = max(best, a[i + dx][j + dy]);
                }
            }

            answer += best;
        }
    }

    cout << answer << '\n';
    return 0;
}
