#include <bits/stdc++.h>
using namespace std;

const int MAXN = 50000 + 5;
int n, d;
long long h[MAXN];
int eatDay[MAXN];

bool check(long long need, bool savePlan) {
    long long happy = 0;
    int idx = 1;

    if (savePlan) {
        for (int i = 1; i <= n; i++) eatDay[i] = 0;
    }

    for (int day = 1; day <= d; day++) {
        while (happy < need && idx <= n) {
            happy += h[idx];
            if (savePlan) eatDay[idx] = day;
            idx++;
        }

        if (happy < need) return false;
        happy /= 2;
    }

    if (savePlan) {
        while (idx <= n) {
            eatDay[idx] = d;
            idx++;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    long long sum = 0;
    for (int i = 1; i <= n; i++) {
        cin >> h[i];
        sum += h[i];
    }

    long long l = 0, r = sum;
    while (l < r) {
        long long mid = (l + r + 1) / 2;
        if (check(mid, false)) {
            l = mid;
        } else {
            r = mid - 1;
        }
    }

    check(l, true);
    cout << l << '\n';
    for (int i = 1; i <= n; i++) {
        cout << eatDay[i] << '\n';
    }

    return 0;
}
