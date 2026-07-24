/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2025-11-28 15:41
 * update_at: 2025-11-28 15:41
 */
/*
 * 题目：[CSP-J 2020] 表达式 (luogu 7073)
 * 核心思路：
 * 1. 表达式为后缀表达式，通过栈将其转化为表达式树。
 * 2. 第一次 DFS (dfs1)：从下往上求出所有节点原本的值。
 * 3. 第二次 DFS (dfs2)：从上往下传递"当前节点的改变是否会影响最终结果"。
 *    - 对于非门 (!)，影响直接向下传递。
 *    - 对于与门 (&)，如果另一半的值为 1，则本侧的改变会影响整体结果；否则被短路。
 *    - 对于或门 (|)，如果另一半的值为 0，则本侧的改变会影响整体结果；否则被短路。
 * 4. 预处理结束后，针对每个查询只需 O(1) 查表。
 */

#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

const int MAXN = 1e6+5;
int n, q;
int init_val[MAXN];

vector<string> tokens; // 后缀表达式的所有 token

// 表达式树节点
// type: 0 表示变量, 1 表示非门(!), 2 表示与门(&), 3 表示或门(|)
struct Node {
    int type;
    int lch, rch;
    int var_id;
    int val;
} node[MAXN];
int node_cnt = 0;

int var_pos[MAXN]; // 记录变量 x_i 对应的节点编号
stack<int> stk;

// dfs1: 从下至上求出每个节点的值
int dfs1(int u) {
    if (node[u].type == 0) {
        return node[u].val = init_val[node[u].var_id];
    }
    if (node[u].type == 1) {
        int child_val = dfs1(node[u].lch);
        return node[u].val = child_val ^ 1;
    }
    int lval = dfs1(node[u].lch);
    int rval = dfs1(node[u].rch);
    if (node[u].type == 2) {
        return node[u].val = lval & rval;
    }
    return node[u].val = lval | rval;
}

int can_affect[MAXN]; // 记录某节点的改变是否影响根节点的结果

// dfs2: 从根向下传播“影响标记”
// about: 当前节点的改变是否会影响根节点
void dfs2(int u, int about) {
    can_affect[u] = about;
    if (node[u].type == 0) return; // 变量节点，到达叶子
    if (node[u].type == 1) {
        // 非门不改变受影响的性质
        dfs2(node[u].lch, about);
        return;
    }
    int lch = node[u].lch, rch = node[u].rch;
    if (node[u].type == 2) { // 与门 &
        if (about) {
            // 如果与门整体受影响，则左子树受影响的前提是右子树为 1
            dfs2(lch, node[rch].val == 1);
            dfs2(rch, node[lch].val == 1);
        } else {
            dfs2(lch, 0);
            dfs2(rch, 0);
        }
    } else { // 或门 |
        if (about) {
            // 如果或门整体受影响，则左子树受影响的前提是右子树为 0
            dfs2(lch, node[rch].val == 0);
            dfs2(rch, node[lch].val == 0);
        } else {
            dfs2(lch, 0);
            dfs2(rch, 0);
        }
    }
}

// 读入表达式所有 token 和变量个数 n
void init_tokens() {
    string tok;
    while (cin >> tok) {
        if (tok[0] >= '0' && tok[0] <= '9') {
            n = stoi(tok);
            break; // 表达式 token 只含 x... ! & |，遇到数字就是 n
        }
        tokens.push_back(tok);
    }
}

// 根据全局 tokens 建立表达式树，返回根节点编号
int build_tree() {
    for (const string &tok : tokens) {
        if (tok[0] == 'x') {
            int id = stoi(tok.substr(1));
            node[++node_cnt] = {0, 0, 0, id, 0};
            var_pos[id] = node_cnt;
            stk.push(node_cnt);
        } else if (tok[0] == '!') {
            int child = stk.top(); stk.pop();
            node[++node_cnt] = {1, child, 0, 0, 0};
            stk.push(node_cnt);
        } else {
            int right = stk.top(); stk.pop();
            int left  = stk.top(); stk.pop();
            if (tok[0] == '&')
                node[++node_cnt] = {2, left, right, 0, 0};
            else
                node[++node_cnt] = {3, left, right, 0, 0};
            stk.push(node_cnt);
        }
    }
    return stk.top();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    init_tokens();
    for (int i = 1; i <= n; i++) {
        cin >> init_val[i];
    }

    int root = build_tree();
    dfs1(root);
    dfs2(root, 1);

    cin >> q;
    int root_val = node[root].val;
    while (q--) {
        int x;
        cin >> x;
        if (can_affect[var_pos[x]])
            cout << (root_val ^ 1) << '\n';
        else
            cout << root_val << '\n';
    }
    return 0;
}
