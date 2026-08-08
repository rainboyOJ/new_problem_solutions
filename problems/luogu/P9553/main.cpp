#include <bits/stdc++.h>
using namespace std;

const int MAX_DAY = 5000;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;

    vector<long long> first_plan(MAX_DAY + 5, 0);
    int max_day = 0;
    for (int i = 1; i <= n; ++i) {
        int d;
        cin >> d;
        ++first_plan[d];
        max_day = max(max_day, d);
    }

    vector<int> special_days(m + 1), review_offset(k + 1);
    vector<int> is_special(MAX_DAY + 5, 0);
    for (int i = 1; i <= m; ++i) {
        cin >> special_days[i];
        is_special[special_days[i]] = 1;
        max_day = max(max_day, special_days[i]);
    }
    for (int i = 1; i <= k; ++i) {
        cin >> review_offset[i];
        max_day = max(max_day, review_offset[i]);
    }

    vector<long long> learn(MAX_DAY + 5, 0), review(MAX_DAY + 5, 0);

    // 先求每一天实际新学多少单词。特殊日上的任务整体顺延到下一天。
    for (int day = 1; day <= MAX_DAY - 2; ++day) {
        if (first_plan[day] == 0) {
            continue;
        }
        if (is_special[day]) {
            first_plan[day + 1] += first_plan[day];
        } else {
            learn[day] += first_plan[day];
        }
    }

    vector<int> next_day(MAX_DAY + 5, 0);
    next_day[MAX_DAY] = MAX_DAY;
    for (int day = MAX_DAY - 1; day >= 1; --day) {
        if (is_special[day]) {
            next_day[day] = next_day[day + 1];
        } else {
            next_day[day] = day;
        }
    }

    int last_day = 0;
    for (int day = 1; day <= MAX_DAY - 2; ++day) {
        if (learn[day] == 0) {
            continue;
        }
        last_day = max(last_day, day);
        for (int j = 1; j <= k; ++j) {
            int real_day = next_day[day + review_offset[j]];
            review[real_day] += learn[day];
            last_day = max(last_day, real_day);
        }
    }

    cout << last_day << '\n';
    for (int day = 1; day <= last_day; ++day) {
        cout << learn[day] << ' ' << review[day] << '\n';
    }
    return 0;
}
