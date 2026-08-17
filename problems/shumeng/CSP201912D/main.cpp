/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:41
 */
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 505;

// 一个区块：parent 是前一块下标，id 是题目给出的块编号，length 是所在链长度。
struct Block {
    int parent, id, length;
};

// 一条在途的链消息：time 是到达时刻，node 是接收节点，chain 是链的末块下标。
struct Message {
    long long time;
    int node, chain;
};

// 小根堆，按到达时刻从小到大取消息。
struct MessageOrder {
    bool operator()(const Message &left, const Message &right) const {
        return left.time > right.time;
    }
};

// 一条输入操作：产生块或查询。
struct Operation {
    int node, block;
    long long time;
    bool is_query;
};

int n, m, delay_time;
int current_chain[MAXN];  // 每个节点当前主链的末块下标
int incoming_chain[MAXN]; // 同一时刻收到的所有链中最好的一个，-1 表示尚未收到
vector<int> graph[MAXN];  // 无向图邻接表
vector<Block> blocks;     // 全部区块，下标即区块编号
priority_queue<Message, vector<Message>, MessageOrder> message_queue;

// 判断链 left 是否严格优于链 right；right == -1 表示没有任何候选。
bool is_better(int left, int right) {
    if (right == -1) return true;
    if (blocks[left].length != blocks[right].length) {
        return blocks[left].length > blocks[right].length;
    }
    return blocks[left].id < blocks[right].id;
}

// 节点 node 把末块为 chain 的链发给所有邻居，t 个时刻后到达。
void send_chain(int node, int chain, long long time) {
    for (int i = 0; i < (int)graph[node].size(); i++) {
        Message message = {time + delay_time, graph[node][i], chain};
        message_queue.push(message);
    }
}

// 处理所有在 time 时刻到达的消息：先合并出每个节点收到的最优链，再统一更新。
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

// 沿父指针回溯整条链并正序输出。
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

    // 读入全部操作：两个数表示查询，三个数表示产生块。
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

    Block genesis = {-1, 0, 1}; // 创世块 0，链长 1
    blocks.push_back(genesis);
    for (int i = 1; i <= n; i++) current_chain[i] = 0;
    fill(incoming_chain, incoming_chain + MAXN, -1);

    int operation_index = 0;
    while (operation_index < operation_count) {
        long long now = operations[operation_index].time;
        // 一个时刻内先处理所有已经到达的消息（接收阶段）。
        while (!message_queue.empty() && message_queue.top().time <= now) {
            process_messages(message_queue.top().time);
        }

        // 当前时刻的所有产生块：接在接收阶段确定的主链末尾。
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
        // 同一节点产生多个块时只发送最终主链一次。
        sort(changed_nodes.begin(), changed_nodes.end());
        changed_nodes.erase(unique(changed_nodes.begin(), changed_nodes.end()), changed_nodes.end());
        for (int i = 0; i < (int)changed_nodes.size(); i++) {
            int node = changed_nodes[i];
            send_chain(node, current_chain[node], now);
        }
        // 查询排在当前时刻所有产生块之后。
        for (int i = operation_index; i < end; i++) {
            if (operations[i].is_query) print_chain(current_chain[operations[i].node]);
        }
        operation_index = end;
    }

    return 0;
}