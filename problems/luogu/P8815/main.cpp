/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-09 06:46
 * update_at: 2026-10-03 15:20
 */
// main.cpp：P8815 逻辑表达式，正式解。
// 分三步完成：
//   1. 用调度场算法把中缀表达式转成后缀表达式（后缀里没有括号）
//   2. 扫描后缀表达式，用一个栈建出表达式树
//   3. 在表达式树上按短路语义求值，只统计真正访问到的子树
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const ll MAXL = 1000000 + 5;

string s;                 // 输入的中缀表达式
string postfix;           // 转换得到的后缀表达式

char op_stack[MAXL];      // 调度场算法的运算符栈，存放运算符和 '('
ll node_stack[MAXL];      // 建树时的节点栈，存放还没有被合并的子树根编号

ll node_cnt;              // 已经创建的表达式树节点个数
char node_type[MAXL];     // node_type[u]：叶子是 '0'/'1'，内部节点是 '&'/'|'
ll left_son[MAXL];        // 左儿子编号，叶子为 0
ll right_son[MAXL];       // 右儿子编号，叶子为 0
char node_value[MAXL];    // 节点的值，只会是 0 或 1

ll eval_stack[MAXL];      // 求值时的显式栈，存放还没算完的节点编号
ll eval_top;

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

// 新建一个表达式树节点，返回编号
ll new_node(char ch, ll left_id, ll right_id) {
    node_cnt++;
    node_type[node_cnt] = ch;
    left_son[node_cnt] = left_id;
    right_son[node_cnt] = right_id;
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

// 先算出所有节点的值：父亲编号一定大于儿子编号，从小到大枚举就能先算完儿子
void calc_all_value(ll root) {
    for (ll u = 1; u <= root; u++) {
        char ch = node_type[u];
        if (ch == '0' || ch == '1') {
            node_value[u] = ch - '0';
        } else if (ch == '&') {
            node_value[u] = node_value[left_son[u]] & node_value[right_son[u]];
        } else {
            node_value[u] = node_value[left_son[u]] | node_value[right_son[u]];
        }
    }
}

// 第三步：从根开始遍历表达式树，按短路语义统计短路次数。
// 每个入栈的节点都只做一件事：判断它自己会不会短路。
//   - 会短路：整棵右子树都不会被求值，所以只把左子树入栈
//   - 不短路：左右子树都会被求值，两个都入栈
// 这样被短路挡住的右子树永远不会入栈，它内部的短路也就不会被统计。
void evaluate(ll root) {
    eval_top = 0;
    eval_stack[++eval_top] = root;

    while (eval_top > 0) {
        ll u = eval_stack[eval_top--];
        char ch = node_type[u];

        if (!is_op(ch)) {
            continue;  // 叶子，没有短路可统计
        }

        if (ch == '&' && node_value[left_son[u]] == 0) {
            // a&b 中 a 为 0，整棵树结果为 0，b 这整棵子树都不需要求值
            short_and++;
            eval_stack[++eval_top] = left_son[u];
        } else if (ch == '|' && node_value[left_son[u]] == 1) {
            // a|b 中 a 为 1，整棵树结果为 1，b 这整棵子树都不需要求值
            short_or++;
            eval_stack[++eval_top] = left_son[u];
        } else {
            // 没有短路，左右子树都要继续访问
            eval_stack[++eval_top] = left_son[u];
            eval_stack[++eval_top] = right_son[u];
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;

    postfix = infix_to_postfix();
    ll root = build_expr_tree();
    calc_all_value(root);
    evaluate(root);

    cout << (int)node_value[root] << '\n';
    cout << short_and << ' ' << short_or << '\n';
    return 0;
}
