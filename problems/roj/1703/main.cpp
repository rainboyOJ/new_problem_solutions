/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 17:19
 * update_at: 2026-10-07 17:19
 */
// 一本通 1703《量子纠缠》：trie 上的状态等价类合并（并查集 + 出边同余闭包）。
//
// 建模：把每个数字串看作 trie 上的一个状态，"串在信息集中"记在该状态上的 fin 标记。
//   "纠缠 a b" 要求对任意后缀 X 都有 (a+X 在信息集) <=> (b+X 在信息集)，
//   这正是 Myhill-Nerode 意义下"状态 a 与状态 b 右语言相同"，两个状态必须并成一类。
// 合并两个等价类时，相同字符的出边也要成对合并，否则等价类不自洽；
// 而这些后继的等价类又可能被进一步合并，所以要用显式栈把闭包做到底。
// 出边只增不减地记在等价类代表元上，查询时每走一步先转到代表元，
// 于是同一类的所有串共享同一套后继 —— 晚到的 1 操作会自动"传染"整个类。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

// 状态数上界：操作 1 每条串 <= L 个点，操作 3 贡献两条串，故
// 点数 <= 1 + c*2*L = 1 + 2050*2*50 = 205001，这里取 25 万留余量
const int MAXNODE = 250005;
const int CHAR_SET = 10;     // 数字串的字符集 0~9

// 状态：出边表 + 并查集父指针 + 是否在信息集中的标记
struct Node {
    int ch[CHAR_SET];  // ch[c] = 走字符 c 到达的状态编号，0 表示没有这条出边
    int fa;            // 并查集父指针：指向同等价类的另一个状态
    bool fin;          // 该状态（等价类代表元）是否已经在信息集中
};

Node node[MAXNODE];  // node[u] 就是状态 u，状态 0 是"无出边"哨兵，根状态是 1
int node_cnt = 1;    // 已创建的状态个数（根状态编号为 1）
bool has_added;      // 是否发生过操作 1：fin 只置真不置假，没加过串时询问一律为 0

// 开一个新状态：出边全空，自己是独立等价类的代表元
int new_node() {
    node_cnt++;
    node[node_cnt].fa = node_cnt;
    node[node_cnt].fin = false;
    return node_cnt;
}

// 并查集找根 + 路径压缩，返回状态 x 所在等价类的代表元
int find_root(int x) {
    int r = x;
    while (node[r].fa != r) r = node[r].fa;  // 第一遍：找到根
    while (node[x].fa != x) {                // 第二遍：把路径上的点直接挂到根
        int p = node[x].fa;
        node[x].fa = r;
        x = p;
    }
    return r;
}

// 沿串 s 在自动机上走一遍，缺的边现场开点，返回末状态所在等价类的代表元
int ensure_state(const string& s) {
    int cur = 1;  // 根状态（空串）
    ll n = s.size();
    for (ll i = 0; i < n; i++) {
        int c = s[i] - '0';
        if (node[cur].ch[c] == 0) node[cur].ch[c] = new_node();
        cur = find_root(node[cur].ch[c]);
    }
    return cur;
}

// 询问串 s 落在哪个等价类：走不通返回 0，否则返回代表元
int find_state(const string& s) {
    int cur = 1;
    ll n = s.size();
    for (ll i = 0; i < n; i++) {
        int c = s[i] - '0';
        int nxt = node[cur].ch[c];
        if (nxt == 0) return 0;  // 前缀就不在 trie 里，串必然不在信息集中
        cur = find_root(nxt);
    }
    return cur;
}

// 合并 p、q 所在的两个等价类，并沿 10 条出边做同余闭包（显式栈代替递归）
void merge_state(int p, int q) {
    vector<pair<int, int> > stk;  // 待合并的状态对
    stk.push_back(make_pair(p, q));
    while (!stk.empty()) {
        int x = stk.back().first;
        int y = stk.back().second;
        stk.pop_back();
        int a = find_root(x);
        int b = find_root(y);
        if (a == b) continue;  // 已经在同一类里
        node[b].fa = a;        // b 并入 a 的等价类
        node[a].fin = node[a].fin || node[b].fin;
        for (int c = 0; c < CHAR_SET; c++) {
            int u = node[a].ch[c];
            int v = node[b].ch[c];
            if (v == 0) continue;  // b 这条出边是空的，没有要合并的后继
            if (u == 0) {
                node[a].ch[c] = v;  // a 缺的边直接接上 b 的
            } else if (find_root(u) != find_root(v)) {
                stk.push_back(make_pair(u, v));  // 两个后继也要同余
            }
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    node[1].fa = 1;  // 根状态自己是代表元

    ll m;
    cin >> m;
    string s, a, b;
    for (ll i = 1; i <= m; i++) {
        int op;
        cin >> op;
        if (op == 1) {
            cin >> s;  // 加入信息集的串
            node[ensure_state(s)].fin = true;
            has_added = true;
        } else if (op == 2) {
            cin >> s;  // 询问串
            // 一次 1 操作都没发生时信息集恒空，不必走自动机
            int v = has_added ? find_state(s) : 0;
            if (v != 0 && node[v].fin) {
                cout << 1 << '\n';
            } else {
                cout << 0 << '\n';
            }
        } else {
            cin >> a >> b;  // 互相纠缠的两个串
            merge_state(ensure_state(a), ensure_state(b));
        }
    }
    return 0;
}
