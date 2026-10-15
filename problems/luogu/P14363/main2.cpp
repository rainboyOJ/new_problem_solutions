/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-22 19:52
 * update_at: 2026-10-15 12:30
 */
// main2.cpp：把规则和询问都转成字符对串，用 AC 自动机匹配，
// 再在 fail 树上按长度阈值离线计数。
//
// ==================== 教学导读 ====================
// 【核心思想：一次扫描同时匹配所有规则】逐询问逐规则检查太慢，
// 换个看法：一条规则在起点 p 可用 ⟺ 对每个 k，t1[p+k] = s1[k] 且 t2[p+k] = s2[k]。
// 把 t1、t2 逐位合成「字符对串」T：T[i] = (a[i], b[i])（编码 0..675），
// 规则也合成字符对串 R：R[k] = (s1[k], s2[k])。那么规则在 p 可用
// ⟺ R 恰好是 T[p .. p+|R|-1] 这段子串 —— 就是普通的模式串匹配！
//
// 【还要覆盖差异区间 [L, R]】规则长度为 k、起点为 p 时，要求 [p, p+k-1] ⊇ [L, R]。
// 固定结束位置 i = p+k-1（i >= R），则 p = i-k+1 >= L，即 k >= i-L+1。
// 于是：以 i 结尾、长度 >= i-L+1 的规则，都恰好贡献一个方案。
//
// 【AC 自动机 + fail 树怎么数】所有规则插入 Trie 建 AC 自动机，扫描 T 时每个位置 i
// 得到一个状态 state(i)。state(i) 的 fail 祖先（含自身）恰好是「所有以 i 结尾的
// 匹配规则」。把 fail 反过来建树，规则终点就是一些节点，问题变成：
//   对每个 (state, 阈值 k0)：state 的 fail 祖先里，深度 >= k0 的终止节点有多少个？
// 对每个 i >= R 拆一个这样的子问题（阈值 k0 = i-L+1）。
//
// 【离线回答】把终止节点按深度降序、子问题按阈值降序排序，双指针推进：
// 深度足够的终止节点就把它的 fail 子树整体 +weight（用 DFS 序区间加），
// 查询 state 的 tin 位置单点值。这就是树状数组上的经典离线套路。
//
// 【图怎么存】Trie 和 fail 树都用「vector<int> g[maxn] 邻接表」存孩子：
//   trie_g[u] 是 u 的 Trie 孩子，边字符挂在孩子上（node[v].ch = 到 v 的边字符）；
//   fail_g[u] 是 u 在 fail 树上的孩子。
// 建完 Trie 后给每个节点的孩子按字符排序，find_child 就能二分查找，转移 O(log 676)。
// AC 自动机用 std::queue 做 BFS 建 fail 指针；fail 树分两步：先建树（build_fail_tree
// 只加边），再在树上遍历求 DFS 序（dfs_fail_tree），每一步都一眼能看懂。
//
// 【复杂度】O((L1+L2) log(L1+L2))，适用于全部数据。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// Trie 只由规则建成：L1 = 规则左右串总长度 <= 5e6，单侧 <= 2.5e6，
// 所以节点数不超过 2500001。两个 vector<int> 邻接表各占 24 字节/节点。
const int MAXNODE = 2500000 + 10;

// 一个 Trie 节点。深度 = 到根路径上的字符数，即该节点对应字符对串的长度。
struct Node {
    int ch;     // 入边上的字符对编码 0..675；根没有入边，记 -1
    int depth;  // 深度 = 该节点对应字符对串的长度（就是规则长度）
    int fail;   // fail 指针
    int weight; // 终止权重：以该节点结尾的规则条数（相同规则不去重）
    int tin;    // fail 树 DFS 序：进入时间戳
    int tout;   // fail 树 DFS 序：离开时间戳，子树是区间 [tin, tout]
};

// Ask：一个离线子问题
// need：规则长度阈值（只统计深度 >= need 的终止节点）；
// state：询问扫描到的 AC 状态（所有以当前位置结尾的匹配规则都在它的 fail 祖先上）；
// id：原始询问编号（一个询问会拆出多个子问题，答案累加）
struct Ask {
    int need;
    int state;
    int id;
};

int n, q;

Node node[MAXNODE];         // 节点池，编号 0..node_cnt-1，0 是根
vector<int> trie_g[MAXNODE]; // trie_g[u]：u 的 Trie 孩子（vector<int> g[maxn] 存图）
vector<int> fail_g[MAXNODE]; // fail_g[u]：u 在 fail 树上的孩子（同一套存图方式）
int node_cnt;                // 已创建的节点数，新建节点的编号就是 node_cnt

int dfs_timer; // fail 树 DFS 序的时间戳

vector<int> terminal_nodes; // 所有终止节点
vector<Ask> asks;           // 所有离线子问题
vector<ll> answer;          // 每个询问的答案
vector<ll> bit;             // 树状数组（差分 + 单点查前缀）

// 一对字符 (a, b) 编码成 0..675 的新字符：
// 把「双串逐位相等」变成「单串子串匹配」，是本解法最关键的一步。
int code_pair(char a, char b) {
    return (a - 'a') * 26 + (b - 'a');
}

// 新建一个节点，入边字符为 ch，返回编号
int new_node(int ch) {
    int id = node_cnt;
    node_cnt++;
    node[id].ch = ch;
    node[id].depth = 0;
    node[id].fail = 0;
    node[id].weight = 0;
    node[id].tin = 0;
    node[id].tout = 0;
    return id;
}

// 建树时取 u 的 ch 孩子，不存在就新建。
// 此时孩子还没排序，线性扫一遍；建完 Trie 统一排序后才用 find_child 二分。
int get_or_add_child(int u, int ch) {
    for (size_t i = 0; i < trie_g[u].size(); i++) {
        int v = trie_g[u][i];
        if (node[v].ch == ch) {
            return v;
        }
    }
    int v = new_node(ch);
    node[v].depth = node[u].depth + 1;
    trie_g[u].push_back(v);
    return v;
}

// 在 u 的孩子里二分查找字符 ch 对应的孩子，找不到返回 -1。
// 前提：trie_g[u] 已按 node[v].ch 升序排好（sort_children 做的）。
int find_child(int u, int ch) {
    int cnt = trie_g[u].size(); // 孩子个数
    int l = 0;
    int r = cnt - 1;
    while (l <= r) {
        int mid = (l + r) >> 1;
        int v = trie_g[u][mid];
        if (node[v].ch == ch) {
            return v;
        }
        if (node[v].ch < ch) {
            l = mid + 1;
        } else {
            r = mid - 1;
        }
    }
    return -1;
}

// 把规则 (a, b) 的字符对串插入 Trie，终止节点权值 +1
void insert_pair_string(const string &a, const string &b) {
    int u = 0;
    int len = a.size();
    for (int i = 0; i < len; i++) {
        int ch = code_pair(a[i], b[i]);
        u = get_or_add_child(u, ch);
    }
    node[u].weight++;
}

// Trie 孩子按入边字符升序排序（比较函数不用 lambda）
bool cmp_child(int a, int b) {
    return node[a].ch < node[b].ch;
}

// 给每个节点的孩子排序，之后 find_child 可以二分查找
void sort_children() {
    for (int u = 0; u < node_cnt; u++) {
        if (trie_g[u].size() > 1) {
            sort(trie_g[u].begin(), trie_g[u].end(), cmp_child);
        }
    }
}

// 沿 fail 链走一步转移，返回下一个 AC 状态
int move_state(int u, int ch) {
    while (u != 0 && find_child(u, ch) == -1) {
        u = node[u].fail;
    }
    int v = find_child(u, ch);
    if (v == -1) {
        return 0;
    }
    return v;
}

// BFS 建 AC 自动机的 fail 指针，用 std::queue 逐层扩展
void build_ac_automaton() {
    queue<int> que;

    // 根的孩子 fail 指向根
    for (size_t i = 0; i < trie_g[0].size(); i++) {
        int v = trie_g[0][i];
        node[v].fail = 0;
        que.push(v);
    }

    while (!que.empty()) {
        int u = que.front();
        que.pop();
        for (size_t i = 0; i < trie_g[u].size(); i++) {
            int v = trie_g[u][i];
            int ch = node[v].ch;

            // 求 fail[v]：从 fail[u] 出发沿 fail 链找能走字符 ch 的节点，
            // 找不到就落到根。这个节点就是 v 对应串的最长真后缀所在位置。
            int f = node[u].fail;
            while (f != 0 && find_child(f, ch) == -1) {
                f = node[f].fail;
            }
            int go = find_child(f, ch);
            if (go == -1) {
                node[v].fail = 0;
            } else {
                node[v].fail = go;
            }
            que.push(v);
        }
    }
}

// 建 fail 树：把每个非根节点挂到 fail 指针指向的节点下面，只加边，不遍历。
// fail 指针反向后恰好是一棵树（根是 0）：u 的 fail 祖先就是 u 到根的路径。
void build_fail_tree() {
    for (int i = 1; i < node_cnt; i++) {
        fail_g[node[i].fail].push_back(i);
    }
}

// 在 fail 树上遍历求 DFS 序：u 的子树对应连续区间 [tin[u], tout[u]]。
// 用显式栈模拟递归，避免长链（深度可达百万级）爆系统栈。
void dfs_fail_tree() {
    dfs_timer = 0;
    vector<int> st;      // 当前 DFS 路径
    vector<size_t> iter; // 每个栈帧下一个要访问的孩子下标

    st.push_back(0);
    iter.push_back(0);
    node[0].tin = ++dfs_timer;

    while (!st.empty()) {
        int u = st.back();
        if (iter.back() < fail_g[u].size()) {
            // 还有孩子没访问：进入下一个孩子
            int v = fail_g[u][iter.back()];
            iter.back()++;
            node[v].tin = ++dfs_timer;
            st.push_back(v);
            iter.push_back(0);
        } else {
            // 孩子全部访问完：离开 u，子树区间到此为止
            node[u].tout = dfs_timer;
            st.pop_back();
            iter.pop_back();
        }
    }
}

// ---- 树状数组：区间加、单点查（差分实现）----

void bit_add(int pos, ll val) {
    int nbit = bit.size() - 1;
    while (pos <= nbit) {
        bit[pos] += val;
        pos += pos & -pos;
    }
}

void bit_range_add(int l, int r, ll val) {
    bit_add(l, val);
    bit_add(r + 1, -val);
}

ll bit_query(int pos) {
    ll res = 0;
    while (pos > 0) {
        res += bit[pos];
        pos -= pos & -pos;
    }
    return res;
}

// 终止节点按深度从大到小排序
bool cmp_terminal_depth(int a, int b) {
    return node[a].depth > node[b].depth;
}

// 离线子问题按长度阈值从大到小排序
bool cmp_ask_need(const Ask &a, const Ask &b) {
    return a.need > b.need;
}

// 离线回答所有子问题：
// 深度不小于阈值的终止节点，其 fail 子树整体加权后，查状态的 DFS 序位置。
// 为什么查 tin[state] 就够：终止节点 u 加在 [tin[u], tout[u]] 上，
// u 是 state 的 fail 祖先 ⟺ state 在 u 的子树里 ⟺ tin[state] ∈ [tin[u], tout[u]]。
void answer_offline_asks() {
    bit.assign(node_cnt + 2, 0);

    sort(terminal_nodes.begin(), terminal_nodes.end(), cmp_terminal_depth);
    sort(asks.begin(), asks.end(), cmp_ask_need);

    int ptr = 0;
    int term_cnt = terminal_nodes.size();
    int ask_cnt = asks.size();
    for (int i = 0; i < ask_cnt; i++) {
        // 把深度足够的终止节点子树加进树状数组
        while (ptr < term_cnt && node[terminal_nodes[ptr]].depth >= asks[i].need) {
            int u = terminal_nodes[ptr];
            bit_range_add(node[u].tin, node[u].tout, node[u].weight);
            ptr++;
        }
        answer[asks[i].id] += bit_query(node[asks[i].state].tin);
    }
}

// 处理一个询问：找出 [L,R] 后，把每个可能结束位置拆成一个离线子问题。
// 规则长度为 k、替换起点为 p 时，要求区间 [p, p+k-1] 覆盖 [L, R]，
// 于是 p = L - (k 的差异前缀长)，等价于统计深度阈值满足条件的终止节点个数。
// 换个更直接的说法：结束位置 i = p+k-1 必须 >= R，且 p = i-k+1 >= L，
// 所以 k >= i-L+1；每个 i >= R 对应一个子问题 (state(i), need = i-L+1)。
void process_query(int id, const string &a, const string &b) {
    // 替换不改变长度
    if (a.size() != b.size()) {
        answer[id] = 0;
        return;
    }

    int len = a.size();
    // first_diff / last_diff 即询问两串的差异区间 [L, R]
    int first_diff = -1;
    int last_diff = -1;
    for (int i = 0; i < len; i++) {
        if (a[i] != b[i]) {
            if (first_diff == -1) {
                first_diff = i;
            }
            last_diff = i;
        }
    }

    if (first_diff == -1) {
        answer[id] = 0; // 两串完全相同，题目保证 t1 != t2，必无解
        return;
    }

    // 扫描字符对串，每个结束位置 i >= R 产生一个子问题：
    // 统计 fail 祖先中深度 >= i - L + 1 的终止节点数量（深度 = 规则长度）。
    // state 始终是「T[0..i] 的最长后缀规则前缀」，fail 祖先就是所有匹配的规则。
    int state = 0;
    for (int i = 0; i < len; i++) {
        int ch = code_pair(a[i], b[i]);
        state = move_state(state, ch);
        if (i >= last_diff) {
            Ask ask;
            ask.need = i - first_diff + 1;
            ask.state = state;
            ask.id = id;
            asks.push_back(ask);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    new_node(-1); // 先把根节点（编号 0）开出来，根没有入边字符

    // 每条规则的左右串逐位合成字符对串，插入 Trie
    string a, b;
    for (int i = 1; i <= n; i++) {
        cin >> a >> b;
        insert_pair_string(a, b);
    }

    sort_children();      // 孩子按边字符排序，find_child 才能二分查找
    build_ac_automaton(); // BFS 求 fail 指针
    build_fail_tree();    // fail 指针反向建树（只加边）
    dfs_fail_tree();      // 在 fail 树上遍历，求 DFS 序

    // 收集所有终止节点（即所有规则串的结尾）
    for (int i = 1; i < node_cnt; i++) {
        if (node[i].weight > 0) {
            terminal_nodes.push_back(i);
        }
    }

    answer.assign(q + 1, 0);
    asks.reserve(1000000);
    // 每个询问在线拆成若干离线子问题，扫完 Trie 后统一回答
    for (int id = 1; id <= q; id++) {
        cin >> a >> b;
        process_query(id, a, b);
    }

    answer_offline_asks();

    for (int id = 1; id <= q; id++) {
        cout << answer[id] << '\n';
    }

    return 0;
}
