#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n, m, p1, p2_ans;
long long s1, s2;
long long c[MAXN];

long long calc_initial_diff() {
    long long dragon = 0;
    long long tiger = 0;

    for (int i = 1; i <= n; i++) {
        if (i < m) {
            dragon += c[i] * (m - i);
        }
        else if (i > m) {
            tiger += c[i] * (i - m);
        }
    }

    if (p1 < m) {
        dragon += s1 * (m - p1);
    }
    else if (p1 > m) {
        tiger += s1 * (p1 - m);
    }

    return dragon - tiger;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    cin >> m >> p1 >> s1 >> s2;

    long long diff = calc_initial_diff();
    long long best_abs = -1;

    p2_ans = 1;
    for (int p2 = 1; p2 <= n; p2++) {
        long long new_diff = diff;

        if (p2 < m) {
            new_diff += s2 * (m - p2);
        }
        else if (p2 > m) {
            new_diff -= s2 * (p2 - m);
        }

        long long cur_abs = llabs(new_diff);
        if (best_abs == -1 || cur_abs < best_abs ||
            (cur_abs == best_abs && p2 < p2_ans)) {
            best_abs = cur_abs;
            p2_ans = p2;
        }
    }

    cout << p2_ans << '\n';

    return 0;
}
