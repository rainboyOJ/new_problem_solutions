#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<int> d(n + 1), special_days(m + 1), t(k + 1);
    for (int i = 1; i <= n; ++i) {
        cin >> d[i];
    }

    set<int> special;
    for (int i = 1; i <= m; ++i) {
        cin >> special_days[i];
        special.insert(special_days[i]);
    }
    for (int i = 1; i <= k; ++i) {
        cin >> t[i];
    }

    map<int, long long> learn, review;
    int last_day = 0;

    for (int i = 1; i <= n; ++i) {
        int first_day = d[i];
        while (special.count(first_day)) {
            ++first_day;
        }
        ++learn[first_day];
        last_day = max(last_day, first_day);

        for (int j = 1; j <= k; ++j) {
            int day = first_day + t[j];
            while (special.count(day)) {
                ++day;
            }
            ++review[day];
            last_day = max(last_day, day);
        }
    }

    cout << last_day << '\n';
    for (int day = 1; day <= last_day; ++day) {
        cout << learn[day] << ' ' << review[day] << '\n';
    }
    return 0;
}
