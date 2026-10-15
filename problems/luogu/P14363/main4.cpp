/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-15 00:29
 * update_at: 2026-10-15 11:26
 */
// main4.cpp：差异核心离线分桶 + 每组左右 Trie + DFS 激活与祖先链求和。
// 总时间 O(L1+L2)，确定性；核心、左右侧都按下一个字符离线分组建树。
//
// ==================== 教学导读 ====================
// 【和 main.cpp 的关系】计数部分完全一样（前后缀分解 → 左 Trie DFS 激活 →
// 右 Trie 祖先链求和），差别只在「建树和分组」：main.cpp 用 map 比字符串分组、
// 用逐字符查孩子建 Trie，代价里带 log；本解把这两处都换成「离线分桶」，做到严格线性。
//
// 【离线分桶建 Trie】一次性拿到一批要插入的串，不用逐个从根往下找孩子：
// 在每个节点处，把所有经过这里的串按「下一个字符」分桶（26 或 676 个桶），
// 每个非空桶就是一个新孩子。这样每个字符只被读常数次，建树总代价 O(总长)。
// 串走到头（next_char 返回 -1）时，记录就挂在当前节点上——
// 相同的串必然挂在同一个终点，所以「终点上的记录链表」就是精确分组，不需要 map。
//
// 【三种建树模式】同一个 build_trie 用 mode 参数复用：
//   CORE：按差异核心的字符对 (a[pos], b[pos]) 建树，终点链表就是核心组；
//   LEFT：按核心左边那段的反转（从核心向左走）建树，终点链表挂规则/询问；
//   RIGHT：按核心右边那段正向建树，只记终点编号。
// 每个核心组复用全局节点池（node_cnt 归零重建），内存与单组规模无关。
//
// 【计数为什么线性】每条规则只在左 Trie 终点上挂一次、激活撤销各一次；
// 每个询问沿右 Trie 祖先链求和，所有询问的链长之和受右 Trie 总长 L2 限制。
// 总复杂度 O(L1+L2)，不依赖字母表大小的乘法因子（桶是 O(1) 分发）。
//
// 【细节坑】全局 bucket 数组只在当前节点用过、且用完立刻清空，
// 所以父节点处理孩子之前必须先把所有桶收走（见 build_trie 末尾）。
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
// 核心读取字符对（保证 (A,B) 逐位一致），左侧反转读取，右侧正向读取。
// depth 是「已经匹配的字符个数」，三种模式共用同一个分桶循环。
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
// work 是显式任务栈，串再长也不使用递归；孩子不需要保存边字符（字符就是桶号）。
// 串走到头时：CORE/LEFT 模式把记录挂到当前节点的 items 链表上（终点即分组），
// RIGHT 模式只把终点编号写回 item[id].right。
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
        // CORE 模式：终点上挂满记录，就是一个完整的差异核心组，交给 solve_groups。
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
// 「激活」= 在右 Trie 的规则终点 weight +1，表示这条规则当前可用。
void enter_node(int u) {
    for (int id = node[u].items; id != 0; id = item[id].left_next) {
        if (item[id].id == 0) node[item[id].right].weight++;
    }
    for (int id = node[u].items; id != 0; id = item[id].left_next) {
        if (item[id].id != 0) {
            ll result = 0;
            // 暴力沿右 Trie 的祖先链求和；所有询问的链长之和受 L2 限制。
            // 被统计到的规则：左端已被 DFS 路径保证「P 是 X 的后缀」，
            // 右端是 v 的祖先保证「S 是 Y 的前缀」，两个条件都恰好满足。
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
// 进入 = 激活当前节点上的规则，离开 = 撤销，保证兄弟分支不互相干扰。
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
