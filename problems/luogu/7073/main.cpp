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

#include <cstdio>
#include <cstring>
using namespace std;

const int MAXN = 1e6+5;
char expr[MAXN];
int n, q;
int init_val[MAXN];

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
int stk[MAXN];
int top = 0;

char tokens[MAXN][20]; // 存储解析出的后缀表达式的各个词
int token_cnt = 0;

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

int main() {
    // 读取表达式字符串
    fgets(expr, MAXN, stdin);
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        scanf("%d", &init_val[i]);
    }
    
    // 解析字符串
    int len = strlen(expr);
    int i = 0, j;
    while (i < len) {
        // 跳过空格和换行符
        while (i < len && (expr[i] == ' ' || expr[i] == '\n' || expr[i] == '\r')) i++;
        if (i >= len) break;
        j = 0;
        // 提取连续的非空白字符
        while (i < len && expr[i] != ' ' && expr[i] != '\n' && expr[i] != '\r') {
            tokens[token_cnt][j++] = expr[i++];
        }
        tokens[token_cnt][j] = '\0';
        token_cnt++;
    }
    
    // 建立表达式树
    for (int t = 0; t < token_cnt; t++) {
        if (tokens[t][0] == 'x') { // 变量
            int id = 0;
            for (int k = 1; tokens[t][k]; k++) {
                id = id * 10 + tokens[t][k] - '0';
            }
            node[++node_cnt] = {0, 0, 0, id, 0};
            var_pos[id] = node_cnt; // 记录 x_id 对应的节点编号
            stk[top++] = node_cnt;  // 节点入栈
        } else if (tokens[t][0] == '!') { // 非门（一元操作）
            int child = stk[--top];
            node[++node_cnt] = {1, child, 0, 0, 0};
            stk[top++] = node_cnt;
        } else { // 与门或或门（二元操作）
            int right = stk[--top];
            int left = stk[--top];
            if (tokens[t][0] == '&') {
                node[++node_cnt] = {2, left, right, 0, 0};
            } else {
                node[++node_cnt] = {3, left, right, 0, 0};
            }
            stk[top++] = node_cnt;
        }
    }
    
    int root = stk[0];
    
    // 第一次 dfs，计算所有节点的初始值
    dfs1(root);
    // 第二次 dfs，计算哪些节点的状态改变会影响最终结果（根节点默认受影响）
    dfs2(root, 1);
    
    scanf("%d", &q);
    int root_val = node[root].val;
    while (q--) {
        int x;
        scanf("%d", &x);
        // 如果该变量可以影响最终结果，则最终结果取反，否则结果不变
        if (can_affect[var_pos[x]]) {
            printf("%d\n", root_val ^ 1);
        } else {
            printf("%d\n", root_val);
        }
    }
    return 0;
}
