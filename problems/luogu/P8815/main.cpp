/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-09 06:46
 * update_at: 2026-10-05 14:46
 */
// main.cpp：P8815 逻辑表达式，正式解。
// 分三步完成：
//   1. 用调度场算法把中缀表达式转成后缀表达式（后缀里没有括号）
//   2. 扫描后缀表达式，用一个栈建出表达式树
//   3. 在表达式树上 dfs 后根遍历，按短路语义求值，同时统计短路次数
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MAXL = 1000000 + 5;

string s;                 // 输入的中缀表达式
string postfix;           // 转换得到的后缀表达式

char op_stack[MAXL];      // 调度场算法的运算符栈，存放运算符和 '('
ll node_stack[MAXL];      // 建树时的节点栈，存放还没有被合并的子树根编号

// 表达式树节点，struct 只放数据，一个节点的信息聚合在一起
struct Node {
    char type;   // 叶子是 '0'/'1'，内部节点是 '&'/'|'（只有 4 种，用 char 省内存）
    ll left;     // 左儿子编号，叶子为 0
    ll right;    // 右儿子编号，叶子为 0
    ll value;    // 节点的值，只会是 0 或 1
};

// 动态化静态：不用指针，用静态大数组 + node_cnt 当分配指针，
// new_node 每次“开点”就把 node_cnt 加一，返回新节点编号。
Node node[MAXL];          // 表达式树，节点 u 就是 node[u]
ll node_cnt;              // 已经创建的节点个数，最后一个节点是 node[node_cnt]

ll short_and;             // '&' 的短路次数
ll short_or;              // '|' 的短路次数

// 判断是不是运算符（本题只有两种）
bool is_op(char ch) {
    return ch == '&' || ch == '|';
}

// 运算符优先级，数字越大越先算；'(' 不参与比较，固定返回 0
ll priority_of(char ch) {
    if (ch == '|') {
        return 1;
    }
    if (ch == '&') {
        return 2;
    }
    return 0;
}

// 第一步：调度场算法，中缀表达式 -> 后缀表达式。
// 数字直接追加到结果里；运算符要入栈时，先把栈顶那些“应该先算”的弹出来。
// 因为本题同级都是从左到右算，所以栈顶优先级 >= 当前优先级时就要弹出。
string infix_to_postfix() {
    string result;
    ll op_top = 0;

    for (ll i = 0; i < (ll)s.size(); i++) {
        char ch = s[i];

        if (!is_op(ch) && ch != '(' && ch != ')') {
            result.push_back(ch);  // 操作数直接输出
        } else if (ch == '(') {
            op_stack[++op_top] = ch;
        } else if (ch == ')') {
            // 把这对括号内部的运算符全部弹出，最后丢掉 '('
            while (op_stack[op_top] != '(') {
                result.push_back(op_stack[op_top--]);
            }
            op_top--;
        } else {
            while (op_top > 0 && op_stack[op_top] != '(' &&
                   priority_of(op_stack[op_top]) >= priority_of(ch)) {
                result.push_back(op_stack[op_top--]);
            }
            op_stack[++op_top] = ch;
        }
    }

    // 扫描结束后，栈里剩下的运算符按顺序弹出
    while (op_top > 0) {
        result.push_back(op_stack[op_top--]);
    }
    return result;
}

// 新建一个表达式树节点（动态开点），返回编号
ll new_node(char ch, ll left_id, ll right_id) {
    node_cnt++;
    node[node_cnt].type = ch;
    node[node_cnt].left = left_id;
    node[node_cnt].right = right_id;
    return node_cnt;
}

// 第二步：扫描后缀表达式建表达式树，返回根节点编号。
// 后缀里是「左操作数 右操作数 运算符」，所以弹栈时先弹出的是右儿子。
ll build_expr_tree() {
    ll top = 0;

    for (ll i = 0; i < (ll)postfix.size(); i++) {
        char ch = postfix[i];

        if (!is_op(ch)) {
            node_stack[++top] = new_node(ch, 0, 0);  // 操作数建成叶子
        } else {
            ll right_id = node_stack[top--];
            ll left_id = node_stack[top--];
            node_stack[++top] = new_node(ch, left_id, right_id);
        }
    }

    return node_stack[1];  // 栈里最后剩下的就是整棵树的根
}

// 第三步：dfs 后根遍历表达式树，把求值和短路统计合在一起做。
// 后根遍历：先递归算完左子树，拿到它的值后才能判断要不要短路。
// 短路时整棵右子树都不递归，所以右子树内部的短路也就不会被统计。
void dfs_calc_value(ll u) {
    if (!is_op(node[u].type)) {
        node[u].value = node[u].type - '0';  // 叶子：值就是 '0'/'1' 本身
        return;
    }

    dfs_calc_value(node[u].left);  // 先递归算左子树

    // a&b 中 a 为 0，或 a|b 中 a 为 1：短路，右子树不用求值
    if (node[u].type == '&' && node[node[u].left].value == 0) {
        short_and++;
        node[u].value = 0;
        return;
    }
    if (node[u].type == '|' && node[node[u].left].value == 1) {
        short_or++;
        node[u].value = 1;
        return;
    }

    // 不短路：右子树也要递归求值，最后算自己
    dfs_calc_value(node[u].right);
    if (node[u].type == '&') {
        node[u].value = node[node[u].left].value & node[node[u].right].value;
    } else {
        node[u].value = node[node[u].left].value | node[node[u].right].value;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    postfix = infix_to_postfix();
    ll root = build_expr_tree();
    dfs_calc_value(root);

    cout << node[root].value << '\n';
    cout << short_and << ' ' << short_or << '\n';
    return 0;
}
