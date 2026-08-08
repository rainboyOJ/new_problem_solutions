/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-19 09:46
 * update_at: 2026-07-19 09:59
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 100005;

int n;
long long charger_power;
long long use_rate[MAXN];
long long stored_energy[MAXN];

bool possible(double seconds) {
    double available = charger_power * seconds;
    double needed = 0.0;

    for (int i = 1; i <= n; i++) {
        double lack = use_rate[i] * seconds - stored_energy[i];
        if (lack > 0) {
            needed += lack;
            if (needed > available) return false;
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> charger_power;

    long long total_use = 0;
    long long total_stored = 0;
    for (int i = 1; i <= n; i++) {
        cin >> use_rate[i] >> stored_energy[i];
        total_use += use_rate[i];
        total_stored += stored_energy[i];
    }

    if (total_use <= charger_power) {
        cout << -1 << '\n';
        return 0;
    }

    double left = 0.0;
    double right = (double)total_stored / (total_use - charger_power);

    for (int iteration = 1; iteration <= 80; iteration++) {
        double middle = (left + right) / 2;
        if (possible(middle)) {
            left = middle;
        } else {
            right = middle;
        }
    }

    cout << fixed << setprecision(10) << left << '\n';
    return 0;
}
