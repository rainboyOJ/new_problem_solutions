/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 21:01
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 605;
int sum[MAXN][MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, levels, radius, threshold;
    cin >> n >> levels >> radius >> threshold;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int value;
            cin >> value;
            sum[i][j] = sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1] + value;
        }
    }
    int answer = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            int top = max(1, i - radius), bottom = min(n, i + radius);
            int left = max(1, j - radius), right = min(n, j + radius);
            int total = sum[bottom][right] - sum[top - 1][right] - sum[bottom][left - 1] + sum[top - 1][left - 1];
            int count = (bottom - top + 1) * (right - left + 1);
            if (total <= threshold * count) answer++;
        }
    }
    cout << answer << '\n';
    return 0;
}
