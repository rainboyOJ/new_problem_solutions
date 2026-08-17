/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

// 灵活型任务：咖啡可以取 [0, a] 内任意实数，每杯收益恒为 b/a。
struct FlexibleTask {
    int cups;              // 最多可提供的咖啡杯数 a
    long double gain_per_cup; // 每杯咖啡减少的耗时 b/a
};

// 普通型任务：只能选择 0 杯或 a 杯，只能整件加速。
struct OrdinaryTask {
    int cups;   // 完整加速需要消耗的咖啡杯数 a
    int gain;   // 完整加速减少的耗时 b
};

// 灵活任务按单位咖啡收益从大到小排序，保证贪心填充最优。
bool compare_flexible(const FlexibleTask &x, const FlexibleTask &y) {
    return x.gain_per_cup > y.gain_per_cup;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m;
    cin >> n >> m;
    long double initial = 0; // 不做任何加速时的总耗时
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

    // flexible_gain[c]：把恰好 c 杯咖啡全部分给灵活任务时的最大总减少量。
    // 因为每杯收益固定，从收益率最高的任务开始依次装满即可。
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

    // dp[used]：用恰好 used 杯咖啡从普通任务中获得的最大总减少量。
    // 普通任务只能整件选择，等价于 0/1 背包。
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

    // 枚举普通任务用掉 used 杯，剩下的 m-used 杯交给灵活任务。
    long double best_gain = 0;
    for (int used = 0; used <= m; used++) {
        if (dp[used] > NEGATIVE / 2) {
            best_gain = max(best_gain, dp[used] + flexible_gain[m - used]);
        }
    }
    cout << fixed << setprecision(6) << initial - best_gain << '\n';
    return 0;
}