#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int T;
int n;
long long a[MAXN];
long long b[MAXN];
long long left_max_arr[MAXN];
long long right_max_arr[MAXN];

// brute.cpp：小数据暴力解。
// 做法是枚举被修改的位置，再枚举修改后的高度，直接重新计算总积水量。

long long calc_water(long long arr[]) {
    left_max_arr[0] = 0;
    for (int i = 1; i <= n; i++) {
        left_max_arr[i] = max(left_max_arr[i - 1], arr[i]);
    }

    right_max_arr[n + 1] = 0;
    for (int i = n; i >= 1; i--) {
        right_max_arr[i] = max(right_max_arr[i + 1], arr[i]);
    }

    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        long long level = min(left_max_arr[i], right_max_arr[i]);
        if (level > arr[i]) {
            sum += level - arr[i];
        }
    }
    return sum;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    while (T--) {
        cin >> n;
        long long mx = 0;
        for (int i = 1; i <= n; i++) {
            cin >> a[i];
            mx = max(mx, a[i]);
        }

        // 小数据对拍时，枚举到 max(a)+1 已经足够。
        // 因为把某个位置改得更高，不会比改成这个范围内更优。
        long long answer = (long long)4e18;
        for (int pos = 1; pos <= n; pos++) {
            for (int new_height = 1; new_height <= mx + 1; new_height++) {
                for (int i = 1; i <= n; i++) {
                    b[i] = a[i];
                }
                b[pos] = new_height;
                answer = min(answer, calc_water(b));
            }
        }

        cout << answer << '\n';
    }

    return 0;
}
