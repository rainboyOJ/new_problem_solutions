/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-15 00:29
 * update_at: 2026-10-15 00:29
 */
// main3.cpp：差异核心离线分桶 + 每组左右 Trie + DFS 激活与祖先链求和。
// 总时间 O(L1+L2)，确定性；核心、左右侧都按下一个字符离线分组建树。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXNODE = 5000000 + 10; // 有效输入单侧总长度至多 5000000，另有两个根
const int SIGMA = 26 * 26;
const int CORE = 0, LEFT = 1, RIGHT = 2;

// 一个有效规则或询问；保留原串，通过 l/r 访问三段，不复制子串。
struct Item {
    string a, b;
    int l, r;
    int next;      // 离线分桶时的临时链表；核心建完后连接同核心的记录
    int left_next; // 挂在左 Trie 终点的记录链表，不受右 Trie 建树影响
    int right;     // 右 Trie 的终点
    int id;        // 规则为 0，询问为原编号
};

// 节点编号、记录数不超过 5000002，用 int 控制大数组内存。
struct Node {
    int child, sibling, parent;
    int items;  // 核心树或左 Trie 的终点记录链表
    int weight; // 右 Trie 上当前激活的规则数量，最多 n
};

struct Bucket {
    int head; // 下一字符相同的记录链表，0 表示空桶
};

struct Work {
    int u, head, depth; // 在 u 处理这一批记录，当前字符下标为 depth
};

Node node[MAXNODE];
Bucket bucket[SIGMA]; // 全过程共用，初始化一次，只清空实际使用的桶
vector<Item> item;
vector<Work> work;
vector<int> used, groups, members;
vector<ll> answer;
ll n, q;
int node_cnt;

// 节点池先用于核心树，然后每个核心组复用；只初始化实际新建的节点。
int new_node(int parent) {
    node_cnt++;
    node[node_cnt].child = node[node_cnt].sibling = 0;
    node[node_cnt].parent = parent;
    node[node_cnt].items = node[node_cnt].weight = 0;
    return node_cnt;
}

// 读入规则或询问，长度不同、无变化的记录不参与建树。
void read_item(int query_id, int &head) {
    Item current;
    cin >> current.a >> current.b;
    if (current.a.size() != current.b.size()) return;
    current.l = current.r = -1;
    ll len = current.a.size();
    for (ll i = 0; i < len; i++) {
        if (current.a[i] != current.b[i]) {
            if (current.l == -1) current.l = i;
            current.r = i;
        }
    }
    if (current.l == -1) return;
    current.next = head;
    current.left_next = current.right = 0;
    current.id = query_id;
    item.push_back(move(current));
    head = item.size() - 1;
}

// 按建树模式读下一个字符；-1 表示串已结束。
// 核心读取字符对，左侧反转读取，右侧正向读取。
int next_char(int id, int depth, int mode) {
    const Item &s = item[id];
    if (mode == CORE) {
        if (depth > s.r - s.l) return -1;
        int pos = s.l + depth;
        return (s.a[pos] - 'a') * 26 + s.b[pos] - 'a';
    }
    if (mode == LEFT) {
        if (depth >= s.l) return -1;
        return s.a[s.l - 1 - depth] - 'a';
    }
    ll pos = s.r + 1 + depth;
    ll len = s.a.size();
    if (pos >= len) return -1;
    return s.a[pos] - 'a';
}

// 离线建 Trie：每个节点把经过这里的记录按下一字符分桶。
// work 是显式任务栈，串再长也不使用递归；孩子不需要保存边字符。
void build_trie(int root, int head, int mode) {
    work.clear();
    work.push_back({root, head, 0});
    while (!work.empty()) {
        Work current = work.back();
        work.pop_back();
        used.clear();
        for (int id = current.head; id != 0; ) {
            int next = item[id].next; // 改链表前保存原来的下一条记录
            int ch = next_char(id, current.depth, mode);
            if (ch == -1) {
                if (mode == CORE) {
                    item[id].next = node[current.u].items;
                    node[current.u].items = id;
                } else if (mode == LEFT) {
                    item[id].left_next = node[current.u].items;
                    node[current.u].items = id;
                } else {
                    item[id].right = current.u;
                }
            } else {
                if (bucket[ch].head == 0) used.push_back(ch);
                item[id].next = bucket[ch].head;
                bucket[ch].head = id;
            }
            id = next;
        }
        if (mode == CORE && node[current.u].items != 0) {
            groups.push_back(node[current.u].items);
        }
        // 必须先取走并清空本节点的所有桶，再处理任何孩子，才能复用全局桶。
        for (size_t i = 0; i < used.size(); i++) {
            int ch = used[i];
            int v = new_node(current.u);
            node[v].sibling = node[current.u].child;
            node[current.u].child = v;
            work.push_back({v, bucket[ch].head, current.depth + 1});
            bucket[ch].head = 0;
        }
    }
}

// 根据本核心组的记录编号，重建临时链表；左右建树分别调用一次。
int make_list() {
    int head = 0;
    for (size_t i = 0; i < members.size(); i++) {
        int id = members[i];
        item[id].next = head;
        head = id;
    }
    return head;
}

// 进入左 Trie 的节点：先激活全部规则，再回答同节点的全部询问。
void enter_node(int u) {
    for (int id = node[u].items; id != 0; id = item[id].left_next) {
        if (item[id].id == 0) node[item[id].right].weight++;
    }
    for (int id = node[u].items; id != 0; id = item[id].left_next) {
        if (item[id].id != 0) {
            ll result = 0;
            // 暴力沿右 Trie 的祖先链求和；所有询问的链长之和受 L2 限制。
            for (int v = item[id].right; v != 0; v = node[v].parent) {
                result += node[v].weight;
            }
            answer[item[id].id] = result;
        }
    }
}

// 离开左 Trie 的节点：撤销这里的规则，避免影响其他分支。
void leave_node(int u) {
    for (int id = node[u].items; id != 0; id = item[id].left_next) {
        if (item[id].id == 0) node[item[id].right].weight--;
    }
}

// 用 child / sibling / parent 模拟 DFS，不开递归栈或额外长链栈。
void dfs_left(int root) {
    int u = root;
    while (u != 0) {
        enter_node(u);
        if (node[u].child != 0) {
            u = node[u].child;
            continue;
        }
        while (u != 0) {
            leave_node(u);
            if (node[u].sibling != 0) {
                u = node[u].sibling;
                break;
            }
            u = node[u].parent;
        }
    }
}

void solve_groups() {
    for (size_t g = 0; g < groups.size(); g++) {
        members.clear();
        bool has_rule = false, has_query = false;
        for (int id = groups[g]; id != 0; id = item[id].next) {
            members.push_back(id);
            if (item[id].id == 0) has_rule = true;
            else has_query = true;
        }
        if (!has_rule || !has_query) continue;

        // groups 保存的是记录链表头，不是核心树节点，因此可以安全复用节点池。
        node_cnt = 0;
        int left_root = new_node(0);
        int right_root = new_node(0);
        build_trie(left_root, make_list(), LEFT);
        build_trie(right_root, make_list(), RIGHT);
        dfs_left(left_root);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    item.reserve(n + q + 1);
    item.resize(1); // 记录编号从 1 开始，0 是链表结束标记
    answer.assign(q + 1, 0);
    int head = 0;
    for (ll i = 1; i <= n; i++) read_item(0, head);
    for (ll i = 1; i <= q; i++) read_item(i, head);
    int core_root = new_node(0);
    build_trie(core_root, head, CORE);
    solve_groups();
    for (ll i = 1; i <= q; i++) cout << answer[i] << '\n';
    return 0;
}
