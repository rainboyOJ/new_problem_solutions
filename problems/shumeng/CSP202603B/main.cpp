/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-07-31 16:22
 */
#include <bits/stdc++.h>
using namespace std;

struct FlexibleTask {
    int cups;
    long double gain_per_cup;
};

struct OrdinaryTask {
    int cups;
    int gain;
};

bool compare_flexible(const FlexibleTask &x, const FlexibleTask &y) {
    return x.gain_per_cup > y.gain_per_cup;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    long double initial = 0;
    vector<FlexibleTask> flexible;
    vector<OrdinaryTask> ordinary;
    for (int i = 0; i < n; i++) {
        int type, t, a, b;
        cin >> type >> t >> a >> b;
        initial += t;
        if (type == 0) {
            FlexibleTask task;
            task.cups = a;
            task.gain_per_cup = (long double)b / a;
            flexible.push_back(task);
        } else {
            OrdinaryTask task;
            task.cups = a;
            task.gain = b;
            ordinary.push_back(task);
        }
    }

    sort(flexible.begin(), flexible.end(), compare_flexible);
    vector<long double> flexible_gain(m + 1, 0);
    for (int capacity = 0; capacity <= m; capacity++) {
        int left = capacity;
        for (int i = 0; i < (int)flexible.size(); i++) {
            int used = min(left, flexible[i].cups);
            flexible_gain[capacity] += used * flexible[i].gain_per_cup;
            left -= used;
            if (left == 0) break;
        }
    }

    const long double NEGATIVE = -1e100L;
    vector<long double> dp(m + 1, NEGATIVE);
    dp[0] = 0;
    for (int i = 0; i < (int)ordinary.size(); i++) {
        for (int used = m; used >= ordinary[i].cups; used--) {
            if (dp[used - ordinary[i].cups] > NEGATIVE / 2) {
                dp[used] = max(dp[used],
                    dp[used - ordinary[i].cups] + ordinary[i].gain);
            }
        }
    }

    long double best_gain = 0;
    for (int used = 0; used <= m; used++) {
        if (dp[used] > NEGATIVE / 2) {
            best_gain = max(best_gain, dp[used] + flexible_gain[m - used]);
        }
    }
    cout << fixed << setprecision(6) << (double)(initial - best_gain) << '\n';
    return 0;
}
