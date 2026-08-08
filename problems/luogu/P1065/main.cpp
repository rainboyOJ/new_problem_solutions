#include <bits/stdc++.h>
using namespace std;

const int MAXM = 25;     // 最大机器数
const int MAXN = 25;     // 最大工件数
const int MAXT = 10005;  // 时间轴上限

int m, n;
int order_list[MAXM * MAXN];        // 安排顺序：按顺序列出每次要安排的工件编号
int machine_id[MAXN][MAXM];         // machine_id[job][step] 工件 job 的第 step 道工序在哪台机器
int cost_time[MAXN][MAXM];          // cost_time[job][step] 工件 job 的第 step 道工序加工时长

int next_step[MAXN];                // 工件 job 下一次要安排第几道工序
int finish_time[MAXN];              // 工件 job 已安排完的最后时间（最早可开始下一道工序的时间）
bool busy[MAXM][MAXT];              // busy[machine][time] 标记该机器该时刻是否被占用

/* ===== 输入层：读取全部原始数据 ===== */
void read_input() {
    cin >> m >> n;
    int tot = m * n;

    for (int i = 1; i <= tot; i++)
        cin >> order_list[i];

    for (int job = 1; job <= n; job++)
        for (int step = 1; step <= m; step++)
            cin >> machine_id[job][step];

    for (int job = 1; job <= n; job++)
        for (int step = 1; step <= m; step++)
            cin >> cost_time[job][step];
}

/* ===== 调度层：核心调度逻辑 ===== */

// 在机器 mac 上从 start 时刻向后找一段长度为 len 的连续空闲时间。
int find_available_slot(int mac, int start, int len) {
    while (true) {
        bool ok = true;
        for (int t = start; t < start + len; t++) {
            if (busy[mac][t]) {
                start = t + 1;     // 遇到冲突，跳到冲突时刻之后继续找
                ok = false;
                break;
            }
        }
        if (ok) break;
    }
    return start;
}

int schedule_all() {
    int tot = m * n;
    int answer = 0;

    for (int i = 1; i <= tot; i++) {
        int job = order_list[i];           // 当前要安排的工件
        int step = ++next_step[job];       // 当前安排的是该工件的第几道工序
        int mac = machine_id[job][step];   // 目标机器
        int len = cost_time[job][step];    // 加工时长

        // 开始时间不能早于该工件上一道工序完成的时间
        int start = finish_time[job];

        // 在目标机器上找到最早的一段连续空闲时间段
        start = find_available_slot(mac, start, len);

        // 占用该机器上的 [start, start+len) 时间段
        for (int t = start; t < start + len; t++)
            busy[mac][t] = true;

        finish_time[job] = start + len;
        if (answer < finish_time[job])
            answer = finish_time[job];
    }
    return answer;
}

/* ===== 主控层：组装各层 ===== */
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();

    int ans = schedule_all();

    cout << ans << '\n';
    return 0;
}
