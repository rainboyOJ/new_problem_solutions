#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1000005;
const long long INF = (1LL << 60);

int n;
int h[MAXN];
long long dp_rest[MAXN];
long long dp_tired[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
    }

    for (int i = 0; i <= n; i++) {
        dp_rest[i] = INF;
        dp_tired[i] = INF;
    }

    // 在地面时还没有消耗法力，因此可以直接选择跳或爬。
    dp_rest[0] = 0;

    for (int i = 0; i < n; i++) {
        // 从“已经休息好”的状态出发，可以继续爬。
        if (dp_rest[i] < INF / 2) {
            dp_rest[i + 1] = min(dp_rest[i + 1], dp_rest[i] + h[i + 1]);

            // 也可以施法跳 1 层或 2 层，跳完后会进入疲惫状态。
            dp_tired[i + 1] = min(dp_tired[i + 1], dp_rest[i]);
            if (i + 2 <= n) {
                dp_tired[i + 2] = min(dp_tired[i + 2], dp_rest[i]);
            }
        }

        // 如果刚刚跳到这一层，就必须先爬至少一层来恢复体力。
        if (dp_tired[i] < INF / 2) {
            dp_rest[i + 1] = min(dp_rest[i + 1], dp_tired[i] + h[i + 1]);
        }
    }

    cout << min(dp_rest[n], dp_tired[n]) << '\n';
    return 0;
}
