/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-15 09:53
 * update_at: 2026-10-15 11:26
 */
// main.cpp：map 精确分组差异核心，每组普通插入左右 Trie。
// 左 Trie DFS 激活规则，在右 Trie 沿父指针直接求和。
//
// ==================== 教学导读（主解思路） ====================
// 【前后缀分解】把一条非恒等规则写成 s1 = P + A + S，s2 = P + B + S：
//   (A, B) 是首尾差异之间的双串内容，叫「差异核心」；P 是不变前缀，S 是不变后缀。
// 把等长询问同样拆成 t1 = X + C + Y，t2 = X + D + Y（(C, D) 是它的差异核心）。
//
// 【关键观察】首尾差异都要对齐：替换起点 p 必须满足 p + l = L 且 p + r = R
// （l、r 是规则差异位置，L、R 是询问差异位置）。所以规则可用的充要条件是：
//   ① 差异核心相同：(A, B) == (C, D)；
//   ② P 是 X 的后缀（不变前缀紧贴核心向左匹配，且不越出串首）；
//   ③ S 是 Y 的前缀（不变后缀紧贴核心向右匹配，且不越出串尾）。
// 满足三条时替换起点唯一，答案贡献 1。
//
// 【怎么数】按差异核心精确分组（map），只有同组的规则/询问才互相匹配。
// 每组建两棵 Trie：
//   左 Trie：插入「P 反转后的字符串」，询问的 X 反转后沿 Trie 走到最深匹配节点 u；
//            P 是 X 的后缀 ⟺ 规则反转后是 X 反转后的前缀 ⟺ 规则挂在 u 的子树里；
//   右 Trie：插入 S，询问的 Y 沿 Trie 走到最深匹配节点 v，同理规则挂在 v 的子树里。
// 然后对左 Trie 做一次 DFS：
//   进入节点 u 时，把子树里（即挂在 u 到根路径上的）所有规则「激活」——
//   在右 Trie 终点的 weight 上 +1；同节点的询问沿右 Trie 父指针把 weight 加起来，
//   就是「左端匹配 u、右端在 v 祖先链上」的规则数，恰好是条件②③都满足的规则数。
//   离开节点时撤销激活，保证兄弟分支不互相干扰。
//
// 【复杂度】分组 O((L1+L2) log(n+1))（map 键是字符串，但比较总代价受总长度限制）；
// 建 Trie、DFS 都是线性；右祖先链求和的总长度也受 L2 限制。适用于全部数据。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXNODE = 5000000 + 10; // 规则与询问单侧总长度至多 5000000，另有两个根

// 稀疏 Trie：每个节点最多 26 个孩子，child/sibling 连接出边。
// 节点、记录编号不超过 5000002，权重不超过 n，用 int 控制内存。
struct Node {
    int ch, child, sibling, parent;
    int items, weight;
};

struct Item {
    string a;      // 两侧内容均不改变，只需保存原串（a 是 t1 / s1，b 只用来找差异）
    int l, r;      // 首尾差异位置，0-based；[l, r] 外的字符替换前后不变
    int next;      // 同一差异核心组的记录链表
    int left_next; // 挂在左 Trie 终点的记录链表（左端匹配情况相同的记录）
    int right;     // 右 Trie 的终点（右端匹配到的最深节点）
    int id;        // 规则为 0，询问为原编号
};

struct Group {
    int head;
    bool has_query;
};

struct Frame {
    int u, child; // 显式 DFS 栈：当前节点与尚未访问的下一个孩子
};

Node node[MAXNODE];
int node_cnt;
ll n, q;
map<pair<string, string>, int> core_id;
vector<Item> items(1); // 编号 0 表示链表结束
vector<Group> groups(1);
vector<Frame> dfs_stack;
vector<ll> answer;

int new_node(int parent, int ch) {
    node_cnt++;
    node[node_cnt].ch = ch;
    node[node_cnt].parent = parent;
    node[node_cnt].child = node[node_cnt].sibling = 0;
    node[node_cnt].items = node[node_cnt].weight = 0;
    return node_cnt;
}

// 普通 Trie 插入：有这个孩子就走过去，没有就新建。
int get_child(int u, int ch) {
    for (int v = node[u].child; v != 0; v = node[v].sibling) {
        if (node[v].ch == ch) return v;
    }
    int v = new_node(u, ch);
    node[v].sibling = node[u].child;
    node[u].child = v;
    return v;
}

void read_item(int query_id) {
    string a, b;
    cin >> a >> b;
    if (a.size() != b.size()) return; // 替换不改变长度，不等长直接丢掉（答案为 0）
    // 求差异区间 [l, r]，它就是「差异核心」在原串中的位置
    int l = -1, r = -1;
    ll len = a.size();
    for (ll i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            if (l == -1) l = i;
            r = i;
        }
    }
    if (l == -1) return; // 恒等规则不能得到不同的目标串

    // 用差异核心 (A, B) 作为分组键：只有核心相同的规则和询问才可能互相匹配
    pair<string, string> key(a.substr(l, r - l + 1), b.substr(l, r - l + 1));
    auto it = core_id.find(key);
    int g;
    if (it == core_id.end()) {
        if (query_id != 0) return; // 没有这个核心的规则，询问答案为 0
        g = groups.size();
        core_id[key] = g;
        groups.push_back({0, false});
    } else {
        g = it->second;
    }
    if (query_id != 0) groups[g].has_query = true; // 标记本组需要建 Trie 统计

    Item current;
    current.a = move(a);
    current.l = l;
    current.r = r;
    current.next = groups[g].head;
    current.left_next = current.right = 0;
    current.id = query_id;
    items.push_back(move(current));
    groups[g].head = items.size() - 1;
}

// 规则和询问一起插入：左侧反转，右侧正向，空侧边对应根。
// 左 Trie 存「核心左边那段的反转」：P 是 X 的后缀 ⟺ rev(P) 是 rev(X) 的前缀，
// 这样 Trie 上越深匹配得越多，DFS 子树就能枚举所有「P 是 X 后缀」的规则。
// 右 Trie 存「核心右边那段」，同理用前缀关系表达「S 是 Y 的前缀」。
void build_group(int g, int left_root, int right_root) {
    for (int id = groups[g].head; id != 0; id = items[id].next) {
        int u = left_root;
        for (ll i = items[id].l - 1; i >= 0; i--) {
            u = get_child(u, items[id].a[i] - 'a');
        }
        items[id].left_next = node[u].items;
        node[u].items = id;

        u = right_root;
        ll len = items[id].a.size();
        for (ll i = items[id].r + 1; i < len; i++) {
            u = get_child(u, items[id].a[i] - 'a');
        }
        items[id].right = u;
    }
}

void enter_node(int u) {
    // 同节点上的规则必须全部激活后，再回答这里的询问（规则之间不区分先后）。
    // 「激活」= 在右 Trie 的规则终点上 weight +1，表示这条规则当前可用。
    for (int id = node[u].items; id != 0; id = items[id].left_next) {
        if (items[id].id == 0) node[items[id].right].weight++;
    }
    for (int id = node[u].items; id != 0; id = items[id].left_next) {
        if (items[id].id != 0) {
            // 询问：沿右 Trie 父指针把 weight 加起来。
            // 只要规则的右端节点是 v 的祖先（含 v 本身），就满足「S 是 Y 的前缀」，
            // 而左端条件已由「规则挂在当前 DFS 节点子树里」保证，故和就是答案。
            ll result = 0;
            for (int v = items[id].right; v != 0; v = node[v].parent) {
                result += node[v].weight;
            }
            answer[items[id].id] = result;
        }
    }
}

void leave_node(int u) {
    for (int id = node[u].items; id != 0; id = items[id].left_next) {
        if (items[id].id == 0) node[items[id].right].weight--;
    }
}

// 显式栈模拟普通 DFS，避免超长前缀导致递归爆栈。
// 整个 DFS 过程中，激活集合恰好是「当前节点到根这条路径上的所有规则」，
// 也就是所有「左端被 rev(X) 前缀匹配」的规则，配合右 Trie 求和完成计数。
void dfs_left(int root) {
    dfs_stack.clear();
    enter_node(root);
    dfs_stack.push_back({root, node[root].child});
    while (!dfs_stack.empty()) {
        int u = dfs_stack.back().u;
        int v = dfs_stack.back().child;
        if (v == 0) {
            leave_node(u);
            dfs_stack.pop_back();
        } else {
            dfs_stack.back().child = node[v].sibling;
            enter_node(v);
            dfs_stack.push_back({v, node[v].child});
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    items.reserve(n + q + 1);
    answer.assign(q + 1, 0);
    for (ll i = 1; i <= n; i++) read_item(0);
    for (ll i = 1; i <= q; i++) read_item(i);
    core_id.clear(); // 分组完成，释放核心字典，再处理各组的 Trie

    for (size_t g = 1; g < groups.size(); g++) {
        if (!groups[g].has_query) continue;
        node_cnt = 0; // 组间复用节点池，只初始化实际用到的节点
        int left_root = new_node(0, -1);
        int right_root = new_node(0, -1);
        build_group(g, left_root, right_root);
        dfs_left(left_root);
    }
    for (ll i = 1; i <= q; i++) cout << answer[i] << '\n';
    return 0;
}
