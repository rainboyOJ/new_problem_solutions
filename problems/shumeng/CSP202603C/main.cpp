/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:22
 * update_at: 2026-07-31 16:22
 */
#include <bits/stdc++.h>
using namespace std;

const long long INF = 4000000000000000000LL;

struct QueueInfo {
    long long left;
    long long right;
    long long last;
};

map<long long, long long> free_by_left;
set<pair<long long, long long>> free_by_size;

void erase_free(long long left) {
    map<long long, long long>::iterator it = free_by_left.find(left);
    long long right = it->second;
    free_by_size.erase(make_pair(right - left + 1, left));
    free_by_left.erase(it);
}

void add_free(long long left, long long right) {
    map<long long, long long>::iterator it = free_by_left.lower_bound(left);
    if (it != free_by_left.begin()) {
        map<long long, long long>::iterator previous = it;
        --previous;
        if (previous->second + 1 >= left) {
            left = previous->first;
            right = max(right, previous->second);
            erase_free(previous->first);
        }
    }

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
    vector<vector<QueueInfo>> queues(n + 1);
    free_by_left[0] = INF;
    free_by_size.insert(make_pair(INF + 1, 0));

    for (int operation = 0; operation < q; operation++) {
        string type;
        cin >> type;
        if (type == "new") {
            int process, length;
            cin >> process >> length;
            set<pair<long long, long long>>::iterator it =
                free_by_size.lower_bound(make_pair((long long)length, LLONG_MIN));
            long long left = it->second;
            long long right = free_by_left[left];
            erase_free(left);
            if (left + length <= right) {
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
            for (int i = 0; i < (int)queues[process].size(); i++) {
                QueueInfo &queue = queues[process][i];
                if (queue.last == -1 || queue.last == queue.right) {
                    queue.last = queue.left;
                } else {
                    queue.last++;
                }
                answer += queue.last;
            }
            cout << answer << '\n';
        } else {
            int process, index;
            cin >> process >> index;
            QueueInfo queue = queues[process][index - 1];
            add_free(queue.left, queue.right);
            queues[process].erase(queues[process].begin() + index - 1);
        }
    }
    return 0;
}
