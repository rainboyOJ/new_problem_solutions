/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:41
 */
// brute.cpp：小数据直接模拟。消息中复制整条链，便于和正式解对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 20;

// 消息携带完整链：time 到达时刻，node 接收节点，chain 整条链的块编号序列。
struct Message {
    long long time;
    int node;
    vector<int> chain;
};

struct MessageOrder {
    bool operator()(const Message &left, const Message &right) const {
        return left.time > right.time;
    }
};

struct Operation {
    int node, block;
    long long time;
    bool is_query;
};

int n, m, delay_time;
vector<int> graph[MAXN], current_chain[MAXN], incoming_chain[MAXN];
bool received[MAXN];
priority_queue<Message, vector<Message>, MessageOrder> message_queue;

// 判断链 left 是否优于链 right；right 为空表示没有任何候选。
bool is_better(const vector<int> &left, const vector<int> &right) {
    if (right.empty()) return true;
    if (left.size() != right.size()) return left.size() > right.size();
    return left.back() < right.back();
}

void send_chain(int node, long long time) {
    for (int i = 0; i < (int)graph[node].size(); i++) {
        Message message = {time + delay_time, graph[node][i], current_chain[node]};
        message_queue.push(message);
    }
}

// 处理同一时刻到达的消息：先合并最优链，再统一更新并转发。
void process_messages(long long time) {
    vector<int> touched;
    while (!message_queue.empty() && message_queue.top().time == time) {
        Message message = message_queue.top();
        message_queue.pop();
        if (!received[message.node]) {
            received[message.node] = true;
            touched.push_back(message.node);
        }
        if (is_better(message.chain, incoming_chain[message.node])) {
            incoming_chain[message.node] = message.chain;
        }
    }
    for (int i = 0; i < (int)touched.size(); i++) {
        int node = touched[i];
        if (is_better(incoming_chain[node], current_chain[node])) {
            current_chain[node] = incoming_chain[node];
            send_chain(node, time);
        }
        incoming_chain[node].clear();
        received[node] = false;
    }
}

void print_chain(int node) {
    cout << current_chain[node].size();
    for (int i = 0; i < (int)current_chain[node].size(); i++) {
        cout << ' ' << current_chain[node][i];
    }
    cout << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        graph[u].push_back(v);
        graph[v].push_back(u);
    }
    int operation_count;
    cin >> delay_time >> operation_count;
    string line;
    getline(cin, line);

    vector<Operation> operations;
    for (int i = 0; i < operation_count; i++) {
        getline(cin, line);
        stringstream input(line);
        vector<long long> value;
        long long number;
        while (input >> number) value.push_back(number);
        Operation operation;
        operation.node = (int)value[0];
        operation.time = value[1];
        operation.is_query = value.size() == 2;
        operation.block = operation.is_query ? 0 : (int)value[2];
        operations.push_back(operation);
    }

    for (int i = 1; i <= n; i++) current_chain[i].push_back(0); // 创世块

    int operation_index = 0;
    while (operation_index < operation_count) {
        long long now = operations[operation_index].time;
        while (!message_queue.empty() && message_queue.top().time <= now) {
            process_messages(message_queue.top().time);
        }

        int end = operation_index;
        while (end < operation_count && operations[end].time == now) end++;
        vector<int> changed_nodes;
        for (int i = operation_index; i < end; i++) {
            if (operations[i].is_query) continue;
            int node = operations[i].node;
            current_chain[node].push_back(operations[i].block);
            changed_nodes.push_back(node);
        }
        sort(changed_nodes.begin(), changed_nodes.end());
        changed_nodes.erase(unique(changed_nodes.begin(), changed_nodes.end()), changed_nodes.end());
        for (int i = 0; i < (int)changed_nodes.size(); i++) {
            send_chain(changed_nodes[i], now);
        }
        for (int i = operation_index; i < end; i++) {
            if (operations[i].is_query) print_chain(operations[i].node);
        }
        operation_index = end;
    }

    return 0;
}