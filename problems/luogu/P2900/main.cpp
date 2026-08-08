#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

struct Rect {
    long long x, y;
} a[MAXN], b[MAXN];

int n, m;
long long dp[MAXN];
int q[MAXN];

bool cmp_rect(const Rect &lhs, const Rect &rhs) {
    if (lhs.x != rhs.x) {
        return lhs.x < rhs.x;
    }
    return lhs.y > rhs.y;
}

long double slope(int i, int j) {
    return (long double) (dp[j] - dp[i]) / (long double) (b[i + 1].y - b[j + 1].y);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i].x >> a[i].y;
    }

    sort(a + 1, a + n + 1, cmp_rect);

    // 去掉被支配的矩形：
    // 按 x 递增后，只保留 y 严格递减的部分。
    m = 0;
    for (int i = 1; i <= n; i++) {
        while (m > 0 && b[m].y <= a[i].y) {
            m--;
        }
        b[++m] = a[i];
    }

    int head = 1, tail = 1;
    q[1] = 0;
    dp[0] = 0;

    // 约定 b[m + 1].y = 0，方便 slope 中访问 j + 1。
    b[m + 1].y = 0;

    for (int i = 1; i <= m; i++) {
        while (head < tail && slope(q[head], q[head + 1]) <= b[i].x) {
            head++;
        }

        int j = q[head];
        dp[i] = dp[j] + b[i].x * b[j + 1].y;

        while (head < tail && slope(q[tail - 1], q[tail]) >= slope(q[tail], i)) {
            tail--;
        }
        q[++tail] = i;
    }

    cout << dp[m] << '\n';
    return 0;
}
