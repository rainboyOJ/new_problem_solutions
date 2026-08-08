#include <bits/stdc++.h>
using namespace std;

int n, d;
long long h[15];
int assignDay[15], bestAssign[15];
long long bestValue;

long long evalPlan() {
    long long happy = 0;
    long long mn = (1LL << 60);
    int idx = 1;

    for (int day = 1; day <= d; day++) {
        while (idx <= n && assignDay[idx] == day) {
            happy += h[idx];
            idx++;
        }
        mn = min(mn, happy);
        happy /= 2;
    }

    if (idx <= n) return -1;
    return mn;
}

void dfs(int idx, int lastDay) {
    if (idx > n) {
        long long val = evalPlan();
        if (val > bestValue) {
            bestValue = val;
            for (int i = 1; i <= n; i++) bestAssign[i] = assignDay[i];
        }
        return;
    }

    for (int day = lastDay; day <= d; day++) {
        assignDay[idx] = day;
        dfs(idx + 1, day);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> d;
    for (int i = 1; i <= n; i++) cin >> h[i];

    bestValue = -1;
    dfs(1, 1);

    cout << bestValue << '\n';
    for (int i = 1; i <= n; i++) {
        cout << bestAssign[i] << '\n';
    }

    return 0;
}
