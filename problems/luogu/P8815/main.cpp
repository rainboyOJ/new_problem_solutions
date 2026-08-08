#include <bits/stdc++.h>
using namespace std;

const int MAXL = 1000000 + 5;

static int left_son[MAXL];
static int right_son[MAXL];
static char node_type[MAXL];
static unsigned char node_value[MAXL];
static int node_cnt;

static int value_stack[MAXL];
static char op_stack[MAXL];
static int eval_node_stack[MAXL];
static unsigned char eval_state_stack[MAXL];

int priority_of(char ch) {
    if (ch == '|') {
        return 1;
    }
    if (ch == '&') {
        return 2;
    }
    return 0;
}

int new_node(char ch, int left_id, int right_id) {
    ++node_cnt;
    node_type[node_cnt] = ch;
    left_son[node_cnt] = left_id;
    right_son[node_cnt] = right_id;
    return node_cnt;
}

void apply_once(int &value_top, int &op_top) {
    char op = op_stack[op_top--];
    int right_id = value_stack[value_top--];
    int left_id = value_stack[value_top--];
    value_stack[++value_top] = new_node(op, left_id, right_id);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string s;
    cin >> s;

    int value_top = 0;
    int op_top = 0;

    for (char ch : s) {
        if (ch == '0' || ch == '1') {
            value_stack[++value_top] = new_node(ch, 0, 0);
        } else if (ch == '(') {
            op_stack[++op_top] = ch;
        } else if (ch == ')') {
            while (op_top > 0 && op_stack[op_top] != '(') {
                apply_once(value_top, op_top);
            }
            --op_top;
        } else {
            while (op_top > 0 && op_stack[op_top] != '(' &&
                   priority_of(op_stack[op_top]) >= priority_of(ch)) {
                apply_once(value_top, op_top);
            }
            op_stack[++op_top] = ch;
        }
    }

    while (op_top > 0) {
        apply_once(value_top, op_top);
    }

    int root = value_stack[value_top];
    long long short_and = 0;
    long long short_or = 0;

    int eval_top = 1;
    eval_node_stack[1] = root;
    eval_state_stack[1] = 0;

    // 迭代模拟递归求值，只在真正访问到的子树里统计短路次数。
    while (eval_top > 0) {
        int u = eval_node_stack[eval_top];
        char ch = node_type[u];

        if (ch == '0' || ch == '1') {
            node_value[u] = (ch == '1');
            --eval_top;
            continue;
        }

        if (eval_state_stack[eval_top] == 0) {
            eval_state_stack[eval_top] = 1;
            eval_node_stack[++eval_top] = left_son[u];
            eval_state_stack[eval_top] = 0;
            continue;
        }

        if (eval_state_stack[eval_top] == 1) {
            if (ch == '&' && node_value[left_son[u]] == 0) {
                ++short_and;
                node_value[u] = 0;
                --eval_top;
                continue;
            }
            if (ch == '|' && node_value[left_son[u]] == 1) {
                ++short_or;
                node_value[u] = 1;
                --eval_top;
                continue;
            }

            eval_state_stack[eval_top] = 2;
            eval_node_stack[++eval_top] = right_son[u];
            eval_state_stack[eval_top] = 0;
            continue;
        }

        if (ch == '&') {
            node_value[u] = node_value[left_son[u]] & node_value[right_son[u]];
        } else {
            node_value[u] = node_value[left_son[u]] | node_value[right_son[u]];
        }
        --eval_top;
    }

    cout << (int)node_value[root] << '\n';
    cout << short_and << ' ' << short_or << '\n';
    return 0;
}
