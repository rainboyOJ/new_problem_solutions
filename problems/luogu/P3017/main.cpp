/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-16 17:48
 * update_at: 2026-07-22 21:04
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXR = 505;
const int MAXC = 505;

int R, C, A, B;
int a[MAXR][MAXC];
int col_sum[MAXC]; // 当前横带中每一列的权值和
long long total_sum;

bool check(int target) {
    memset(col_sum, 0, sizeof(col_sum));
    int strips = 0;

    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            col_sum[j] += a[i][j];
        }

        int pieces = 0;
        int cur = 0;
        for (int j = 1; j <= C; j++) {
            cur += col_sum[j];
            if (cur >= target) {
                pieces++;
                cur = 0;
            }
        }

        // 当前横带已经能切出 B 块，越早结束越不影响后面。
        if (pieces >= B) {
            strips++;
            memset(col_sum, 0, sizeof(col_sum));
        }
    }

    return strips >= A;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> R >> C >> A >> B;
    for (int i = 1; i <= R; i++) {
        for (int j = 1; j <= C; j++) {
            cin >> a[i][j];
            total_sum += a[i][j];
        }
    }

    int left = 0;
    int right = (int)(total_sum / (A * B)) + 1;
    while (left + 1 < right) {
        int mid = (left + right) / 2;
        if (check(mid)) {
            left = mid;
        }
        else {
            right = mid;
        }
    }

    cout << left << '\n';

    return 0;
}
