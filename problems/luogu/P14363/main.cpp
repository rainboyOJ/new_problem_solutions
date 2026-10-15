/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-15 09:53
 * update_at: 2026-10-15 21:26
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
// 【怎么数】按差异核心分组，每组把规则和询问的两侧插入两棵普通 Trie：
//   左 Trie 插入反转后的不变前缀；右 Trie 插入正向不变后缀。
//   规则左终点是询问左终点的祖先，且规则右终点是询问右终点的祖先，才合法。
// DFS 左 Trie：进入节点时激活恰好挂在这里的规则，离开时撤销。
// 回答询问时，激活集合恰好是当前节点到根路径上全部规则；
// 再沿询问右终点到根求 weight 之和，筛出右侧同样匹配的规则。
//
// 【复杂度】设 T=L1+L2，分组 O(T log(n+1))，建树和左 DFS 为 O(26T)，
// 右侧查询总长度受 L2 限制。固定字母表下总时间 O(T log(n+1))，空间 O(T)。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXGROUP = 200000 + 10; // 差异核心组数不超过规则数 n
const int MAXNODE = 5000000 + 10; // 规则与询问单侧总长度至多 5000000，另有两个根

// 普通 Trie：ch[c] 存字符 c 对应的孩子编号，0 表示没有。
// 节点编号至多 5000002，权重不超过 n，因此用 int。
struct Node {
    int ch[26]; // 'a' 到 'z' 的孩子
    int parent; // 父节点，右树求祖先链之和时使用
    int weight; // 右树：在这里结束的已激活规则数
};

struct Record {
    string a;      // 两侧内容均不改变，只需保存原串（a 是 t1 / s1，b 只用来找差异）
    int l, r;      // 首尾差异位置，0-based；[l, r] 外的字符替换前后不变
    int right;     // 右 Trie 的终点（右端匹配到的最深节点）
    int query_id; // 规则为 0，询问为原始询问编号
};

Node node[MAXNODE];
vector<int> record_ids[MAXNODE]; // 节点桶：左终点为 u 的记录编号，放在 record_ids[u]
vector<int> group_records[MAXGROUP]; // 核心组桶：属于第 g 组的记录编号
bool has_query[MAXGROUP]; // 询问桶：第 g 组是否包含询问
int node_cnt, group_cnt;
ll n, q;
map<pair<string, string>, int> core_id;
vector<Record> records(1); // 完整记录从编号 1 开始保存
vector<ll> answer;

int new_node(int parent) {
    node_cnt++;
    // 组间复用节点池，重新使用的节点必须清空全部孩子。
    for (int c = 0; c < 26; c++) node[node_cnt].ch[c] = 0;
    node[node_cnt].parent = parent;
    record_ids[node_cnt].clear(); // 节点编号复用时，挂载的记录也必须清空
    node[node_cnt].weight = 0;
    return node_cnt;
}

// 字符 ch 对应的孩子不存在时新建，否则直接走过去。
int get_child(int u, int ch) {
    if (node[u].ch[ch] == 0) node[u].ch[ch] = new_node(u);
    return node[u].ch[ch];
}

void read_record(int query_id) {
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
        g = ++group_cnt;
        core_id[key] = g;
    } else {
        g = it->second;
    }
    if (query_id != 0) has_query[g] = true; // 标记本组需要建 Trie 统计

    Record current;
    current.a = move(a);
    current.l = l;
    current.r = r;
    current.right = 0;
    current.query_id = query_id;
    records.push_back(move(current));
    int record_id = records.size() - 1;
    group_records[g].push_back(record_id);
}

// 规则和询问一起插入：左侧反转，右侧正向，空侧边对应根。
// 左 Trie 存「核心左边那段的反转」：P 是 X 的后缀 ⟺ rev(P) 是 rev(X) 的前缀，
// 规则左终点在询问左终点的祖先链上，就满足左侧条件。
// 右 Trie 存「核心右边那段」，同理用前缀关系表达「S 是 Y 的前缀」。
void build_group(int g, int left_root, int right_root) {
    // 建树阶段：依次插入本组记录，挂到左终点，并记住右终点。
    for (auto record_id : group_records[g]) {
        int u = left_root;
        for (ll i = records[record_id].l - 1; i >= 0; i--) {
            u = get_child(u, records[record_id].a[i] - 'a');
        }
        record_ids[u].push_back(record_id); // 把这条记录挂在左终点上

        u = right_root;
        ll len = records[record_id].a.size();
        for (ll i = records[record_id].r + 1; i < len; i++) {
            u = get_child(u, records[record_id].a[i] - 'a');
        }
        records[record_id].right = u;
    }
}

// 计数阶段：左侧的匹配由 DFS 路径保证，右侧沿祖先链求和。
void enter_node(int u) {
    // 同节点上的规则必须全部激活后，再回答这里的询问（规则之间不区分先后）。
    // 「激活」= 在右 Trie 的规则终点上 weight +1，表示这条规则当前可用。
    for (auto record_id : record_ids[u]) {
        if (records[record_id].query_id == 0) node[records[record_id].right].weight++;
    }
    for (auto record_id : record_ids[u]) {
        if (records[record_id].query_id != 0) {
            // 询问：沿右 Trie 父指针把 weight 加起来。
            // 只要规则的右端节点是 v 的祖先（含 v 本身），就满足「S 是 Y 的前缀」，
            // 左端条件已由当前激活集合保证，因此这个和就是答案。
            ll result = 0;
            for (int v = records[record_id].right; v != 0; v = node[v].parent) {
                result += node[v].weight;
            }
            answer[records[record_id].query_id] = result;
        }
    }
}

void leave_node(int u) {
    for (auto record_id : record_ids[u]) {
        if (records[record_id].query_id == 0) node[records[record_id].right].weight--;
    }
}

// 左 Trie 的递归 DFS：进入时激活规则并回答询问，访问完孩子后撤销。
// 激活集合恰好是当前节点到根路径上的全部规则。
void dfs_left(int u) {
    enter_node(u);
    for (int c = 0; c < 26; c++) {
        int v = node[u].ch[c];
        if (v != 0) dfs_left(v);
    }
    leave_node(u);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    records.reserve(n + q + 1);
    answer.assign(q + 1, 0);
    for (ll i = 1; i <= n; i++) read_record(0);
    for (ll i = 1; i <= q; i++) read_record(i);
    core_id.clear(); // 分组完成，释放核心字典，再处理各组的 Trie

    for (int g = 1; g <= group_cnt; g++) {
        if (!has_query[g]) continue;
        node_cnt = 0; // 组间复用节点池，只初始化实际用到的节点
        int left_root = new_node(0);
        int right_root = new_node(0);
        build_group(g, left_root, right_root);
        dfs_left(left_root);
    }
    for (ll i = 1; i <= q; i++) cout << answer[i] << '\n';
    return 0;
}
