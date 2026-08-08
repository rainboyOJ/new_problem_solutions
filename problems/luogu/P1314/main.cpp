#include <bits/stdc++.h>
using namespace std;

const int MAXN = 200005;
const int MAXM = 200005;

int n, m;
long long s;
int w[MAXN], v[MAXN];
int L[MAXM], R[MAXM];
long long cnt_prefix[MAXN];
long long sum_prefix[MAXN];
int max_w;

long long abs128(__int128 x) {
    if (x < 0) {
        x = -x;
    }
    return (long long)x;
}

// 计算当前阈值 W 下的总检验值。
__int128 calc_value(int W) {
    cnt_prefix[0] = 0;
    sum_prefix[0] = 0;

    for (int i = 1; i <= n; i++) {
        cnt_prefix[i] = cnt_prefix[i - 1];
        sum_prefix[i] = sum_prefix[i - 1];

        if (w[i] >= W) {
            cnt_prefix[i]++;
            sum_prefix[i] += v[i];
        }
    }

    __int128 total = 0;
    for (int i = 1; i <= m; i++) {
        long long cnt = cnt_prefix[R[i]] - cnt_prefix[L[i] - 1];
        long long sumv = sum_prefix[R[i]] - sum_prefix[L[i] - 1];
        total += (__int128)cnt * sumv;
    }

    return total;
}

void print_int128(__int128 x) {
    if (x == 0) {
        cout << 0 << '\n';
        return;
    }

    if (x < 0) {
        cout << '-';
        x = -x;
    }

    string s;
    while (x > 0) {
        s.push_back(char('0' + x % 10));
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s << '\n';
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

    int left = 0, right = max_w + 1;

    // y(W) 随 W 增大单调不增。
    // 找到第一个使 y(W) <= s 的 W。
    while (left < right) {
        int mid = (left + right) >> 1;
        __int128 val = calc_value(mid);

        if (val <= s) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    __int128 ans = -1;

    __int128 val1 = calc_value(left);
    ans = val1 - s;
    if (ans < 0) {
        ans = -ans;
    }

    if (left > 0) {
        __int128 val2 = calc_value(left - 1);
        __int128 diff = val2 - s;
        if (diff < 0) {
            diff = -diff;
        }
        if (diff < ans) {
            ans = diff;
        }
    }

    print_int128(ans);

    return 0;
}
