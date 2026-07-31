/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 18:00
 */
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int n;
int a[45], c[45], serial_time[45];

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;

    // 只用单 CPU 运行所有任务，贪心分到当前负载较小的 CPU，得到一个上界。
    int cpu1_load = 0;
    int cpu2_load = 0;
    for (int i = 1; i <= n; i++) {
        int b, d;
        cin >> a[i] >> b >> c[i] >> d;
        serial_time[i] = min(b, d);

        if (cpu1_load <= cpu2_load) {
            cpu1_load += a[i];
        } else {
            cpu2_load += a[i];
        }
    }

    int limit = max(cpu1_load, cpu2_load);
    int width = limit + 1;
    int layer_size = width * width * width;
    vector<int> dp(2 * layer_size, INF);

    dp[0] = 0;

    for (int task = 1; task <= n; task++) {
        int current_layer = task & 1;
        int previous_layer = current_layer ^ 1;
        int current_offset = current_layer * layer_size;
        int previous_offset = previous_layer * layer_size;

        for (int cpu1 = 0; cpu1 <= limit; cpu1++) {
            for (int cpu2 = cpu1; cpu2 <= limit; cpu2++) {
                int current_base = current_offset + (cpu1 * width + cpu2) * width;
                const int *previous_same = &dp[previous_offset + (cpu1 * width + cpu2) * width];

                int cpu1_after_a = -1;
                int cpu2_after_a = -1;
                int cpu1_after_c = -1;
                int cpu2_after_c = -1;

                if (cpu1 >= a[task]) {
                    cpu1_after_a = previous_offset + ((cpu1 - a[task]) * width + cpu2) * width;
                }
                if (cpu2 >= a[task]) {
                    int next_cpu1 = cpu1;
                    int next_cpu2 = cpu2 - a[task];
                    if (next_cpu1 > next_cpu2) {
                        swap(next_cpu1, next_cpu2);
                    }
                    cpu2_after_a = previous_offset + (next_cpu1 * width + next_cpu2) * width;
                }
                if (cpu1 >= c[task]) {
                    cpu1_after_c = previous_offset + ((cpu1 - c[task]) * width + cpu2) * width;
                }
                if (cpu2 >= c[task]) {
                    int next_cpu1 = cpu1;
                    int next_cpu2 = cpu2 - c[task];
                    if (next_cpu1 > next_cpu2) {
                        swap(next_cpu1, next_cpu2);
                    }
                    cpu2_after_c = previous_offset + (next_cpu1 * width + next_cpu2) * width;
                }

                int c_time = c[task];
                for (int gpu = 0; gpu <= limit; gpu++) {
                    int value = previous_same[gpu] + serial_time[task];

                    if (cpu1_after_a != -1) {
                        value = min(value, dp[cpu1_after_a + gpu]);
                    }
                    if (cpu2_after_a != -1) {
                        value = min(value, dp[cpu2_after_a + gpu]);
                    }
                    if (gpu >= c_time) {
                        if (cpu1_after_c != -1) {
                            value = min(value, dp[cpu1_after_c + gpu - c_time]);
                        }
                        if (cpu2_after_c != -1) {
                            value = min(value, dp[cpu2_after_c + gpu - c_time]);
                        }
                    }

                    // 当前状态已经不可能得到不超过上界的答案，直接丢弃。
                    if (value + max(cpu2, gpu) > limit) {
                        value = INF;
                    }
                    dp[current_base + gpu] = value;
                }
            }
        }
    }

    int answer = INF;
    int final_offset = (n & 1) * layer_size;
    for (int cpu1 = 0; cpu1 <= limit; cpu1++) {
        for (int cpu2 = cpu1; cpu2 <= limit; cpu2++) {
            int base = final_offset + (cpu1 * width + cpu2) * width;
            for (int gpu = 0; gpu <= limit; gpu++) {
                answer = min(answer, dp[base + gpu] + max(cpu2, gpu));
            }
        }
    }

    cout << answer << '\n';
    return 0;
}
