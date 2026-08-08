#include <bits/stdc++.h>
using namespace std;

const int MAXN = 500000 + 5;
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
    for (int i = 1; i <= n; i++) {
        cin >> w[i];
        if (w[i] > maxW) maxW = w[i];
    }

    long long l = 0, r = (maxW + a - 1) / a;
    while (l < r) {
        long long mid = (l + r) / 2;
        if (canFinish(mid)) {
            r = mid;
        } else {
            l = mid + 1;
        }
    }

    cout << l << '\n';
    return 0;
}
