/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

// 一个进程的全部运行信息
struct Process {
    char type;       // 进程类型 X / A / B / C
    int start_time;  // 开始活动的段首
    int patience;    // 忍耐限度 w
    vector<int> resource; // 每个任务要申请的资源
    vector<int> duration; // 每个任务的持续段数
    int task;        // 当前正在执行第几个任务（从 0 开始）
    int state; // 0: 未开始，1: 申请资源，2: 运行，3: 完成
    int wait_start;  // 本轮等待开始的段首
    int remain;      // 当前任务剩余运行段数
    long long gain;  // 累计收益
    long long finish_time; // 完成时的段号，-1 表示未正常结束
};

vector<Process> process_list; // 1 下标
int owner[41];                // 每种资源当前的占有者，0 表示待使用
bool owns[11][41];            // 进程 i 是否占有资源 j

// 进程 process 抢占资源 resource，把原占有者从该资源上挤掉。
void acquire_resource(int process, int resource) {
    if (owner[resource] != 0) {
        owns[owner[resource]][resource] = false;
    }
    owner[resource] = process;
    owns[process][resource] = true;
}

void release_all(int process) {
    for (int resource = 1; resource <= 40; resource++) {
        if (owns[process][resource]) {
            owns[process][resource] = false;
            owner[resource] = 0;
        }
    }
}

// 计算当前完整系统状态的哈希，用于检测死锁循环。
// 状态包含每个进程的阶段/任务/剩余段数/等待时长以及每种资源的占有者。
unsigned long long state_hash(int current_time, int max_start, int resource_count) {
    unsigned long long result = 1469598103934665603ULL;
    for (int i = 1; i < (int)process_list.size(); i++) {
        Process &process = process_list[i];
        int age = 0;
        if (process.state == 1) {
            age = current_time - process.wait_start;
            if (process.type != 'X') age = min(age, process.patience + 1);
            else age = min(age, 1);
        }
        result ^= (unsigned long long)(process.state + 5 * process.task +
            31 * process.remain + 997 * age + 10007 * i);
        result *= 1099511628211ULL;
    }
    for (int resource = 1; resource <= resource_count; resource++) {
        result ^= (unsigned long long)(owner[resource] + 131 * resource);
        result *= 1099511628211ULL;
    }
    if (current_time <= max_start) result ^= (unsigned long long)current_time;
    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, resource_count;
    cin >> n >> resource_count;
    process_list.resize(n + 1);
    int max_start = 0;
    for (int i = 1; i <= n; i++) {
        Process &process = process_list[i];
        cin >> process.type;
        int task_count;
        if (process.type == 'X') {
            cin >> process.start_time >> task_count;
            process.patience = 0;
        } else {
            cin >> process.start_time >> process.patience >> task_count;
        }
        max_start = max(max_start, process.start_time);
        process.resource.resize(task_count);
        process.duration.resize(task_count);
        for (int j = 0; j < task_count; j++) {
            cin >> process.resource[j] >> process.duration[j];
        }
        process.task = 0;
        process.state = 0;
        process.wait_start = 0;
        process.remain = 0;
        process.gain = 0;
        process.finish_time = -1;
    }

    memset(owner, 0, sizeof(owner));
    memset(owns, 0, sizeof(owns));
    unordered_set<unsigned long long> visited;
    long long current_time = 1;
    int finished = 0;
    while (finished < n) {
        for (int i = 1; i <= n; i++) {
            if (process_list[i].state == 0 &&
                process_list[i].start_time <= current_time) {
                process_list[i].state = 1;
                process_list[i].wait_start = (int)current_time;
            }
        }

        if (current_time > max_start) {
            unsigned long long hash =
                state_hash((int)current_time, max_start, resource_count);
            if (!visited.insert(hash).second) break;
        }

        // 段首：先收集所有处于申请状态的进程对资源的请求。
        // 同一资源的所有申请必须一起处理，不能按进程编号逐个修改资源状态。
        vector<int> requests[41];
        for (int i = 1; i <= n; i++) {
            if (process_list[i].state == 1) {
                int resource = process_list[i].resource[process_list[i].task];
                requests[resource].push_back(i);
            }
        }

        // release_after 标记段末需要释放全部资源的进程（A 类放弃行为）
        vector<int> release_after(n + 1, 0);
        for (int resource = 1; resource <= resource_count; resource++) {
            if (requests[resource].empty()) continue;
            vector<int> forced;
            for (int j = 0; j < (int)requests[resource].size(); j++) {
                int process_id = requests[resource][j];
                Process &process = process_list[process_id];
                if (process.type == 'C' &&
                    current_time >= process.wait_start + process.patience) {
                    forced.push_back(process_id);
                }
            }

            if (!forced.empty()) {
                int winner = *max_element(forced.begin(), forced.end());
                for (int j = 0; j < (int)forced.size(); j++) {
                    int process_id = forced[j];
                    Process &process = process_list[process_id];
                    if (process_id == winner) acquire_resource(process_id, resource);
                    process.state = 2;
                    process.remain = process.duration[process.task];
                }
                for (int j = 0; j < (int)requests[resource].size(); j++) {
                    int process_id = requests[resource][j];
                    bool is_forced = false;
                    for (int u = 0; u < (int)forced.size(); u++) {
                        if (forced[u] == process_id) is_forced = true;
                    }
                    if (is_forced) continue;
                    Process &process = process_list[process_id];
                    if (process.type == 'B' &&
                        current_time >= process.wait_start + process.patience - 1) {
                        process.state = 2;
                        process.remain = process.duration[process.task];
                    } else if (process.type == 'A' &&
                        current_time >= process.wait_start + process.patience - 1) {
                        release_after[process_id] = 1;
                    }
                }
            } else if (owner[resource] == 0) {
                int winner = *min_element(requests[resource].begin(),
                    requests[resource].end());
                for (int j = 0; j < (int)requests[resource].size(); j++) {
                    int process_id = requests[resource][j];
                    Process &process = process_list[process_id];
                    if (process_id == winner) {
                        acquire_resource(process_id, resource);
                        process.state = 2;
                        process.remain = process.duration[process.task];
                    } else if (process.type == 'B' &&
                        current_time >= process.wait_start + process.patience - 1) {
                        process.state = 2;
                        process.remain = process.duration[process.task];
                    } else if (process.type == 'A' &&
                        current_time >= process.wait_start + process.patience - 1) {
                        release_after[process_id] = 1;
                    }
                }
            } else {
                for (int j = 0; j < (int)requests[resource].size(); j++) {
                    int process_id = requests[resource][j];
                    Process &process = process_list[process_id];
                    if (process.type == 'B' &&
                        current_time >= process.wait_start + process.patience - 1) {
                        process.state = 2;
                        process.remain = process.duration[process.task];
                    } else if (process.type == 'A' &&
                        current_time >= process.wait_start + process.patience - 1) {
                        release_after[process_id] = 1;
                    }
                }
            }
        }

        // 段中：处于运行状态的进程获得等于当前持有资源数的收益，并消耗一段运行时间
        for (int i = 1; i <= n; i++) {
            Process &process = process_list[i];
            if (process.state == 2) {
                int held_count = 0;
                for (int resource = 1; resource <= resource_count; resource++) {
                    if (owns[i][resource]) held_count++;
                }
                process.gain += held_count;
                process.remain--;
            }
        }

        for (int i = 1; i <= n; i++) {
            Process &process = process_list[i];
            if (release_after[i]) {
                release_all(i);
                process.wait_start = (int)current_time + 1;
            }
            if (process.state == 2 && process.remain == 0) {
                process.task++;
                if (process.task == (int)process.resource.size()) {
                    process.state = 3;
                    process.finish_time = current_time;
                    release_all(i);
                    finished++;
                } else {
                    process.state = 1;
                    process.wait_start = (int)current_time + 1;
                }
            }
        }
        current_time++;
    }

    for (int i = 1; i <= n; i++) {
        if (process_list[i].state == 3) {
            cout << process_list[i].gain << ' '
                 << process_list[i].finish_time - process_list[i].start_time + 1 << '\n';
        } else {
            cout << process_list[i].gain << " -1\n";
        }
    }
    return 0;
}
