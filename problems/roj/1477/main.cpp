/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:27
 * update_at: 2026-10-05 03:27
 */
#include <algorithm>
#include <cstring>
#include <iostream>
using namespace std;

typedef long long ll;

const int MAXN = 510005; // 字典树节点上限：所有单词长度之和 + 1，再留少量余量
const int MAXW = 100005; // 单词数上限

int trie[MAXN][26];        // trie[u][c]：节点 u 走字符 c 到达的子节点；0 表示不存在，0 号节点就是根
int parent_node[MAXN];     // parent_node[v]：字典树上 v 的父亲节点
int up[MAXN];              // up[v]：v 在字典树上最近的“单词结尾”祖先；没有则为虚拟根 0
char is_end[MAXN];         // is_end[v]：v 是否是某个单词的结尾，只有 0/1，用 char 省内存
int word_node[MAXW];       // word_node[i]：第 i 个单词在字典树上的节点编号
int subtree_size[MAXN];    // subtree_size[v]：模型树上以单词节点 v 为根的子树里单词的个数（非单词节点为 0）
int order[MAXW];           // order[1..n]：单词节点按（父亲升序，同父亲按子树大小升序）排序的结果
int start_child[MAXN];     // start_child[u]：u 的儿子在 order[] 中的起始下标
int child_count[MAXN];     // child_count[u]：u 的儿子个数
int stack_node[MAXW];      // 迭代 DFS 栈：待访问的单词节点
ll stack_parent_pos[MAXW]; // 迭代 DFS 栈：对应节点父亲的序号，虚拟根的儿子记 0
char buf[MAXN];            // 读入单个单词的缓冲区
int n;
int node_total; // 当前用到的最大字典树节点编号，0 号是根

// 把单词 s 反转后插入字典树，返回它所在的节点编号。
// 反转后“后缀”变成“前缀”，单词的所有后缀就对应树上从根到该节点路径上的单词节点。
int insert_reversed(const char s[], int len) {
    int u = 0; // 从根出发
    for (int j = len - 1; j >= 0; j--) {
        int c = s[j] - 'a';
        if (trie[u][c] == 0) {
            node_total++;
            trie[u][c] = node_total;
            parent_node[node_total] = u;
        }
        u = trie[u][c];
    }
    return u;
}

// order 的排序规则：先按模型树上的父亲编号升序，同一父亲时按子树大小升序。
// 子树小的先访问，等价于“排队接水”的最优贪心。
bool cmp_word(int a, int b) {
    if (up[a] != up[b]) {
        return up[a] < up[b];
    }
    return subtree_size[a] < subtree_size[b];
}

void read_input() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> buf;
        int len = strlen(buf);
        int v = insert_reversed(buf, len);
        is_end[v] = 1;
        word_node[i] = v;
    }
}

void solve() {
    // 1. 求每个节点最近的“单词结尾”祖先。字典树上父亲编号一定小于儿子编号，正序一趟即可。
    for (int v = 1; v <= node_total; v++) {
        int p = parent_node[v];
        up[v] = is_end[p] ? p : up[p];
    }

    // 2. 自底向上累加模型树的子树大小。节点编号大的先算，保证儿子的规模先汇总到父亲。
    for (int v = 1; v <= n; v++) {
        subtree_size[word_node[v]] = 1;
    }
    for (int v = node_total; v >= 1; v--) {
        if (is_end[v]) {
            subtree_size[up[v]] += subtree_size[v];
        }
    }

    // 3. 每个单词节点连向它的最近单词祖先，得到模型树；把单词节点按（父亲，子树大小）排序。
    for (int i = 1; i <= n; i++) {
        order[i] = word_node[i];
    }
    sort(order + 1, order + n + 1, cmp_word);

    // 4. 排好序后同一父亲的儿子连续，扫描出每个父亲的儿子区间。
    int i = 1;
    while (i <= n) {
        int j = i;
        int p = up[order[i]];
        while (j <= n && up[order[j]] == p) {
            j++;
        }
        start_child[p] = i;
        child_count[p] = j - i;
        i = j;
    }

    // 5. 迭代 DFS 统计答案。压栈时按区间从大到小压，弹出时就变成子树小的先访问。
    int top = 0;
    for (int k = start_child[0] + child_count[0] - 1; k >= start_child[0]; k--) {
        top++;
        stack_node[top] = order[k];
        stack_parent_pos[top] = 0; // 虚拟根的儿子没有后缀，父亲序号视作 0
    }
    ll pos = 0; // 已填单词数，也是当前单词的序号
    ll ans = 0;
    while (top > 0) {
        int u = stack_node[top];
        ll parent_pos = stack_parent_pos[top];
        top--;
        pos++;
        ans += pos - parent_pos; // 合法序下代价 = 自己的序号 - 最近单词祖先的序号
        for (int k = start_child[u] + child_count[u] - 1; k >= start_child[u]; k--) {
            top++;
            stack_node[top] = order[k];
            stack_parent_pos[top] = pos;
        }
    }
    cout << ans << "\n";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    read_input();
    solve();

    return 0;
}
