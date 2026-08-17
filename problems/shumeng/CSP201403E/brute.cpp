/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:52
 */
// brute.cpp：小数据暴力解，枚举每个任务的资源方案和执行顺序。
#include <bits/stdc++.h>
using namespace std;

const int INF = 0x3f3f3f3f;

int n;
int run_time[45][7];
int resource_mask[7] = {1, 2, 3, 5, 6, 7, 0};
map<unsigned long long, int> memo;

unsigned long long make_key(int done, int cpu1, int cpu2, int gpu) {
    unsigned long long key = (unsigned long long)done;
    key = key * 512 + cpu1;
    key = key * 512 + cpu2;
    key = key * 512 + gpu;
    return key;
}

int dfs(int done, int cpu1, int cpu2, int gpu) {
    if (cpu1 > cpu2) {
        swap(cpu1, cpu2);
    }

    unsigned long long key = make_key(done, cpu1, cpu2, gpu);
    map<unsigned long long, int>::iterator it = memo.find(key);
    if (it != memo.end()) {
        return it->second;
    }

    if (done == (1 << n) - 1) {
        return max(cpu2, gpu);
    }

    int answer = INF;
    for (int task = 0; task < n; task++) {
        if ((done & (1 << task)) != 0) {
            continue;
        }

        for (int mode = 0; mode < 6; mode++) {
            int mask = resource_mask[mode];
            int start = 0;
            if ((mask & 1) != 0) {
                start = max(start, cpu1);
            }
            if ((mask & 2) != 0) {
                start = max(start, cpu2);
            }
            if ((mask & 4) != 0) {
                start = max(start, gpu);
            }

            int next_cpu1 = cpu1;
            int next_cpu2 = cpu2;
            int next_gpu = gpu;
            if ((mask & 1) != 0) {
                next_cpu1 = start + run_time[task][mode];
            }
            if ((mask & 2) != 0) {
                next_cpu2 = start + run_time[task][mode];
            }
            if ((mask & 4) != 0) {
                next_gpu = start + run_time[task][mode];
            }

            answer = min(answer, dfs(done | (1 << task), next_cpu1, next_cpu2, next_gpu));
        }
    }

    memo[key] = answer;
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    for (int i = 0; i < n; i++) {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        run_time[i][0] = a;
        run_time[i][1] = a;
        run_time[i][2] = b;
        run_time[i][3] = c;
        run_time[i][4] = c;
        run_time[i][5] = d;
    }

    cout << dfs(0, 0, 0, 0) << '\n';
    return 0;
}
