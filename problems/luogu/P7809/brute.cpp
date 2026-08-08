#include <bits/stdc++.h>
using namespace std;

const int MAXN = 205;

int n, m;
int a[MAXN];

int solve_non_decreasing(int l, int r) {
    int answer = 0;

    // 枚举分界点 k：取左边全部 0，右边全部 1。
    for (int k = l - 1; k <= r; k++) {
        int cnt0 = 0;
        int cnt1 = 0;
        for (int i = l; i <= k; i++) {
            if (a[i] == 0) {
                cnt0++;
            }
        }
        for (int i = k + 1; i <= r; i++) {
            if (a[i] == 1) {
                cnt1++;
            }
        }
        answer = max(answer, cnt0 + cnt1);
    }

    return answer;
}

int solve_increasing(int l, int r) {
    int answer = 1;

    for (int i = l; i <= r; i++) {
        for (int j = i + 1; j <= r; j++) {
            if (a[i] < a[j]) {
                answer = 2;
            }
        }
    }

    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    while (m--) {
        int op, l, r;
        cin >> op >> l >> r;

        if (op == 1) {
            cout << solve_non_decreasing(l, r) << '\n';
        }
        else {
            cout << solve_increasing(l, r) << '\n';
        }
    }

    return 0;
}
