#include <bits/stdc++.h>
using namespace std;

const int MAXX = 100000 + 5;

int n, w;
int sum_brightness[MAXX];
int prefix_sum[MAXX];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> w;
    int max_pos = 0;

    for (int i = 1; i <= n; i++) {
        int x, b;
        cin >> x >> b;
        sum_brightness[x] += b;
        if (x > max_pos) {
            max_pos = x;
        }
    }

    for (int i = 1; i <= max_pos; i++) {
        prefix_sum[i] = prefix_sum[i - 1] + sum_brightness[i];
    }

    int answer = 0;

    if (w == 0) {
        // W=0 时，窗户只能看到某一个精确位置上的星星。
        for (int i = 1; i <= max_pos; i++) {
            if (sum_brightness[i] > answer) {
                answer = sum_brightness[i];
            }
        }
    } else {
        // 题目保证 W 为奇数，此时长度为 W 的闭区间恰好覆盖连续 W 个整数位置。
        for (int right = 1; right <= max_pos; right++) {
            int left = right - w + 1;
            if (left < 1) {
                left = 1;
            }
            int current = prefix_sum[right] - prefix_sum[left - 1];
            if (current > answer) {
                answer = current;
            }
        }
    }

    cout << answer << '\n';

    return 0;
}
