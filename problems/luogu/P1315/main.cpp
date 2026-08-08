#include <bits/stdc++.h>
using namespace std;

const int MAXN = 1005;
const int MAXM = 10005;

int n, m, k;
int d[MAXN];
int latest_time[MAXN];   // latest_time[i]：第 i 站最晚需要等到什么时候
int down_cnt[MAXN];      // down_cnt[i]：在第 i 站下车的人数
int prefix_down[MAXN];   // 下车人数前缀和
int arrive_time[MAXN];   // arrive_time[i]：到达第 i 站的时刻
int depart_time[MAXN];   // depart_time[i]：离开第 i 站的时刻
int stop_end[MAXN];      // 把第 i 段路减 1 后，影响最远能传到哪一站
int station_end[MAXN];   // 如果第 i 站到达时间提前 1，影响最远能传到哪一站

int from_station[MAXM];
int to_station[MAXM];
int start_time[MAXM];

// 按当前 d[i] 重建整条线路的到站/发车时刻表。
void rebuild_schedule() {
    arrive_time[1] = 0;
    for (int i = 1; i <= n; i++) {
        depart_time[i] = max(arrive_time[i], latest_time[i]);
        if (i < n) {
            arrive_time[i + 1] = depart_time[i] + d[i];
        }
    }
}

// 计算当前总旅行时间。
long long calc_total_travel_time() {
    long long total = 0;
    for (int i = 1; i <= m; i++) {
        total += 1LL * arrive_time[to_station[i]] - start_time[i];
    }
    return total;
}

// 预处理每一段路在“再减 1”时，影响最远能传播到哪一站。
void build_stop_end() {
    station_end[n] = n;
    for (int i = n - 1; i >= 2; i--) {
        station_end[i] = i;
        if (arrive_time[i] > latest_time[i]) {
            station_end[i] = station_end[i + 1];
        }
    }

    for (int i = 1; i < n; i++) {
        stop_end[i] = station_end[i + 1];
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m >> k;
    for (int i = 1; i < n; i++) {
        cin >> d[i];
    }

    for (int i = 1; i <= m; i++) {
        cin >> start_time[i] >> from_station[i] >> to_station[i];
        latest_time[from_station[i]] = max(latest_time[from_station[i]], start_time[i]);
        down_cnt[to_station[i]]++;
    }

    for (int i = 1; i <= n; i++) {
        prefix_down[i] = prefix_down[i - 1] + down_cnt[i];
    }

    while (k--) {
        rebuild_schedule();
        build_stop_end();

        int best_pos = 0;
        int best_gain = 0;

        for (int i = 1; i < n; i++) {
            if (d[i] == 0) {
                continue;
            }
            int gain = prefix_down[stop_end[i]] - prefix_down[i];
            if (gain > best_gain) {
                best_gain = gain;
                best_pos = i;
            }
        }

        if (best_gain == 0) {
            break;
        }

        d[best_pos]--;
    }

    rebuild_schedule();
    cout << calc_total_travel_time() << '\n';

    return 0;
}
