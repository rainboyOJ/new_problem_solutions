/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:17
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

struct Block {
    int parent, id, length;
};

struct Message {
    long long time;
    int node, chain;
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
int current_chain[MAXN], incoming_chain[MAXN];
vector<int> graph[MAXN];
vector<Block> blocks;
priority_queue<Message, vector<Message>, MessageOrder> message_queue;

bool is_better(int left, int right) {
    if (right == -1) return true;
    if (blocks[left].length != blocks[right].length) {
        return blocks[left].length > blocks[right].length;
    }
    return blocks[left].id < blocks[right].id;
}

void send_chain(int node, int chain, long long time) {
    for (int i = 0; i < (int)graph[node].size(); i++) {
        Message message = {time + delay_time, graph[node][i], chain};
        message_queue.push(message);
    }
}

void process_messages(long long time) {
    vector<int> touched;
    while (!message_queue.empty() && message_queue.top().time == time) {
        Message message = message_queue.top();
        message_queue.pop();
        if (incoming_chain[message.node] == -1) touched.push_back(message.node);
        if (is_better(message.chain, incoming_chain[message.node])) {
            incoming_chain[message.node] = message.chain;
        }
    }
    for (int i = 0; i < (int)touched.size(); i++) {
        int node = touched[i];
        if (is_better(incoming_chain[node], current_chain[node])) {
            current_chain[node] = incoming_chain[node];
            send_chain(node, current_chain[node], time);
        }
        incoming_chain[node] = -1;
    }
}

void print_chain(int chain) {
    vector<int> answer;
    while (chain != -1) {
        answer.push_back(blocks[chain].id);
        chain = blocks[chain].parent;
    }
    reverse(answer.begin(), answer.end());
    cout << answer.size();
    for (int i = 0; i < (int)answer.size(); i++) cout << ' ' << answer[i];
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

    Block genesis = {-1, 0, 1};
    blocks.push_back(genesis);
    for (int i = 1; i <= n; i++) current_chain[i] = 0;
    fill(incoming_chain, incoming_chain + MAXN, -1);

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
            Block block = {current_chain[node], operations[i].block,
                           blocks[current_chain[node]].length + 1};
            blocks.push_back(block);
            current_chain[node] = (int)blocks.size() - 1;
            changed_nodes.push_back(node);
        }
        sort(changed_nodes.begin(), changed_nodes.end());
        changed_nodes.erase(unique(changed_nodes.begin(), changed_nodes.end()), changed_nodes.end());
        for (int i = 0; i < (int)changed_nodes.size(); i++) {
            int node = changed_nodes[i];
            send_chain(node, current_chain[node], now);
        }
        for (int i = operation_index; i < end; i++) {
            if (operations[i].is_query) print_chain(current_chain[operations[i].node]);
        }
        operation_index = end;
    }

    return 0;
}
