#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;
const int MAXM = 25;

int n, m;
long long s;
int w[MAXN], v[MAXN];
int L[MAXM], R[MAXM];
int max_w;

void print_int128(__int128 x) {
    if (x == 0) {
        cout << 0 << '\n';
        return;
    }

    if (x < 0) {
        cout << '-';
        x = -x;
    }

    string str;
    while (x > 0) {
        str.push_back(char('0' + x % 10));
        x /= 10;
    }
    reverse(str.begin(), str.end());
    cout << str << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> s;

    max_w = 0;
    for (int i = 1; i <= n; i++) {
        cin >> w[i] >> v[i];
        max_w = max(max_w, w[i]);
    }

    for (int i = 1; i <= m; i++) {
        cin >> L[i] >> R[i];
    }

    // brute.cpp：小数据暴力。
    // 直接枚举所有可能的 W，按定义计算总检验值 y，
    // 再取 |y-s| 的最小值。
    __int128 ans = -1;

    for (int W = 0; W <= max_w + 1; W++) {
        __int128 total = 0;

        for (int i = 1; i <= m; i++) {
            long long cnt = 0;
            long long sumv = 0;

            for (int j = L[i]; j <= R[i]; j++) {
                if (w[j] >= W) {
                    cnt++;
                    sumv += v[j];
                }
            }

            total += (__int128)cnt * sumv;
        }

        __int128 diff = total - s;
        if (diff < 0) {
            diff = -diff;
        }

        if (ans == -1 || diff < ans) {
            ans = diff;
        }
    }

    print_int128(ans);

    return 0;
}
