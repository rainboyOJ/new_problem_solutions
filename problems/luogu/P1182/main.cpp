#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m;
long long a[MAXN];

bool check(long long limit) {
    int segments = 1;
    long long cur_sum = 0;

    for (int i = 1; i <= n; i++) {
        if (a[i] > limit) {
            return false;
        }
        if (cur_sum + a[i] <= limit) {
            cur_sum += a[i];
        } else {
            segments++;
            cur_sum = a[i];
        }
    }

    return segments <= m;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    long long left = 0;
    long long right = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        left = max(left, a[i]);
        right += a[i];
    }

    while (left < right) {
        long long mid = (left + right) >> 1;
        if (check(mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }

    cout << left << '\n';
    return 0;
}
