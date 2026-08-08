#include <bits/stdc++.h>
using namespace std;

const int MAXN = 55;
int n;
long long a, b;
long long w[MAXN];

bool canFinish(long long t) {
    long long machine = 0;
    for (int i = 1; i <= n; i++) {
        long long left = w[i] - a * t;
        if (left <= 0) continue;
        machine += (left + b - 1) / b;
        if (machine > t) return false;
    }
    return machine <= t;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> a >> b;
    long long maxW = 0;
    for (int i = 1; i <= n; i++) cin >> w[i];
    for (int i = 1; i <= n; i++) {
        if (w[i] > maxW) maxW = w[i];
    }

    long long limit = (maxW + a - 1) / a;
    for (long long t = 0; t <= limit; t++) {
        if (canFinish(t)) {
            cout << t << '\n';
            return 0;
        }
    }

    // 理论上一定会在自然风干上界内找到答案，这里只是兜底。
    cout << limit << '\n';
    return 0;
}
