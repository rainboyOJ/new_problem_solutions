#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50005;

int n;
long long L;
long long c[MAXN], sum[MAXN];
long long dp[MAXN];
int q[MAXN];

long long X(int i) {
    return sum[i] + i;
}

long long S(int i) {
    return X(i) + L + 1;
}

long long Y(int i) {
    long long t = S(i);
    return dp[i] + t * t;
}

bool better_front(int a, int b, long long k) {
    return (__int128) (Y(b) - Y(a)) <= (__int128) k * (S(b) - S(a));
}

bool bad(int a, int b, int cidx) {
    return (__int128) (Y(b) - Y(a)) * (S(cidx) - S(b))
         >= (__int128) (Y(cidx) - Y(b)) * (S(b) - S(a));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> L;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
        sum[i] = sum[i - 1] + c[i];
    }

    int head = 1, tail = 1;
    q[1] = 0;
    dp[0] = 0;

    for (int i = 1; i <= n; i++) {
        long long k = 2LL * X(i);
        while (head < tail && better_front(q[head], q[head + 1], k)) {
            head++;
        }

        int j = q[head];
        long long t = X(i) - X(j) - L - 1;
        dp[i] = dp[j] + t * t;

        while (head < tail && bad(q[tail - 1], q[tail], i)) {
            tail--;
        }
        q[++tail] = i;
    }

    cout << dp[n] << '\n';
    return 0;
}
