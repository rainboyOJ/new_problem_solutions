#include <bits/stdc++.h>
using namespace std;

const int MAXN = 300005;

int n;
long long s;
long long t[MAXN], c[MAXN];
long long sum_t[MAXN], sum_c[MAXN];
long long dp[MAXN];
int q[MAXN];

long long X(int i) {
    return sum_c[i];
}

long long Y(int i) {
    return dp[i] - sum_t[i] * (sum_c[n] - sum_c[i]);
}

bool better_front(int a, int b, long long k) {
    return (__int128) (Y(b) - Y(a)) <= (__int128) k * (X(b) - X(a));
}

bool bad(int a, int b, int cidx) {
    return (__int128) (Y(b) - Y(a)) * (X(cidx) - X(b))
         >= (__int128) (Y(cidx) - Y(b)) * (X(b) - X(a));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> s;
    for (int i = 1; i <= n; i++) {
        cin >> t[i] >> c[i];
        sum_t[i] = sum_t[i - 1] + t[i];
        sum_c[i] = sum_c[i - 1] + c[i];
    }

    int head = 1, tail = 1;
    q[1] = 0;
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        long long k = sum_t[i] + s;
        while (head < tail && better_front(q[head], q[head + 1], k)) {
            head++;
        }

        int j = q[head];
        dp[i] = dp[j]
              + (sum_t[i] - sum_t[j]) * (sum_c[n] - sum_c[j])
              + s * (sum_c[n] - sum_c[j]);

        while (head < tail && bad(q[tail - 1], q[tail], i)) {
            tail--;
        }
        q[++tail] = i;
    }

    cout << dp[n] << '\n';
    return 0;
}
