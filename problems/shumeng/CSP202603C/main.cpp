/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-08-17 22:40
 */
#include <bits/stdc++.h>
using namespace std;

// 内存被看作 [0, INF] 的一段连续空间，初始全部空闲。
const long long INF = 4000000000000000000LL;

// 一个进程接口对应的队列：占用的内存区间 [left, right] 与最近一次写入位置
struct QueueInfo {
    long long left;
    long long right;
    long long last; // 最近一次发送时对象写入的地址，-1 表示尚未发送过
};

// 空闲区间按左端点排序，用于按地址合并相邻区间
map<long long, long long> free_by_left;
// 空闲区间按 (长度, 左端点) 排序，用于找 best-fit 区间
set<pair<long long, long long> > free_by_size;

// 从两个有序结构中删除左端点为 left 的空闲区间。
void erase_free(long long left) {
    map<long long, long long>::iterator it = free_by_left.find(left);
    long long right = it->second;
    free_by_size.erase(make_pair(right - left + 1, left));
    free_by_left.erase(it);
}

// 插入空闲区间 [left, right]，并把它与左右相邻的区间合并。
void add_free(long long left, long long right) {
    map<long long, long long>::iterator it = free_by_left.lower_bound(left);
    // 先尝试与左侧相邻的区间合并
    if (it != free_by_left.begin()) {
        map<long long, long long>::iterator previous = it;
        --previous;
        if (previous->second + 1 >= left) {
            left = previous->first;
            right = max(right, previous->second);
            erase_free(previous->first);
        }
    }

    // 再向右吃掉所有与当前区间相邻的区间
    it = free_by_left.lower_bound(left);
    while (it != free_by_left.end() && it->first <= right + 1) {
        right = max(right, it->second);
        map<long long, long long>::iterator next = it;
        ++next;
        erase_free(it->first);
        it = next;
    }
    free_by_left[left] = right;
    free_by_size.insert(make_pair(right - left + 1, left));
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, q;
    cin >> n >> q;
    vector<vector<QueueInfo> > queues(n + 1); // queues[p] 保存进程 p 的接口队列
    free_by_left[0] = INF;                    // 初始只有一个覆盖全部内存的空闲区间
    free_by_size.insert(make_pair(INF + 1, 0));

    for (int operation = 0; operation < q; operation++) {
        string type;
        cin >> type;
        if (type == "new") {
            int process, length;
            cin >> process >> length;
            // best-fit：长度不小于 L 且最短、最靠左的空闲区间
            set<pair<long long, long long> >::iterator it =
                free_by_size.lower_bound(make_pair((long long)length, LLONG_MIN));
            long long left = it->second;
            long long right = free_by_left[left];
            erase_free(left);
            if (left + length <= right) { // 取走 L 个地址后还有剩余，重新加回
                add_free(left + length, right);
            }

            QueueInfo queue;
            queue.left = left;
            queue.right = left + length - 1;
            queue.last = -1;
            queues[process].push_back(queue);
            cout << left << '\n';
        } else if (type == "send") {
            int process;
            cin >> process;
            long long answer = 0;
            // 进程 p 的所有队列各写入一个对象，地址从 last 向右循环推进
            for (int i = 0; i < (int)queues[process].size(); i++) {
                QueueInfo &queue = queues[process][i];
                if (queue.last == -1 || queue.last == queue.right) {
                    queue.last = queue.left; // 首次写入或绕回左端点
                } else {
                    queue.last++;
                }
                answer += queue.last;
            }
            cout << answer << '\n';
        } else { // delete 操作
            int process, index;
            cin >> process >> index;
            QueueInfo queue = queues[process][index - 1];
            add_free(queue.left, queue.right); // 释放整个区间并合并
            queues[process].erase(queues[process].begin() + index - 1);
        }
    }
    return 0;
}