#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100000 + 5;

int n, w;
int x[MAXN];
int b[MAXN];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> w;
    int min_pos = 1000000000;
    int max_pos = 0;

    for (int i = 1; i <= n; i++) {
        cin >> x[i] >> b[i];
        if (x[i] < min_pos) {
            min_pos = x[i];
        }
        if (x[i] > max_pos) {
            max_pos = x[i];
        }
    }

    int answer = 0;

    if (w == 0) {
        // 没有边缘时，只能选中一个精确位置。
        for (int pos = min_pos; pos <= max_pos; pos++) {
            int current = 0;
            for (int i = 1; i <= n; i++) {
                if (x[i] == pos) {
                    current += b[i];
                }
            }
            if (current > answer) {
                answer = current;
            }
        }
    } else {
        int half = w / 2;
        // 枚举窗户中心位置，直接判断每颗星星是否落在窗口内。
        for (int center = min_pos - half; center <= max_pos + half; center++) {
            int left = center - half;
            int right = center + half;
            int current = 0;
            for (int i = 1; i <= n; i++) {
                if (left <= x[i] && x[i] <= right) {
                    current += b[i];
                }
            }
            if (current > answer) {
                answer = current;
            }
        }
    }

    cout << answer << '\n';

    return 0;
}
