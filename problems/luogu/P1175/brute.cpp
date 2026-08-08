#include <bits/stdc++.h>
using namespace std;

struct Token {
    int type; // 0 表示数字，1 表示运算符
    long long value;
    char op;
};

struct Node {
    int type; // 0 表示数字，1 表示运算符
    long long value;
    char op;
    int left_son;
    int right_son;
};

string expr;
int pos = 0;
Node tree_nodes[505];
int node_cnt = 0;
vector<Token> postfix_tokens;

int new_number_node(long long value) {
    ++node_cnt;
    tree_nodes[node_cnt].type = 0;
    tree_nodes[node_cnt].value = value;
    tree_nodes[node_cnt].op = 0;
    tree_nodes[node_cnt].left_son = 0;
    tree_nodes[node_cnt].right_son = 0;
    return node_cnt;
}

int new_operator_node(char op, int left_son, int right_son) {
    ++node_cnt;
    tree_nodes[node_cnt].type = 1;
    tree_nodes[node_cnt].value = 0;
    tree_nodes[node_cnt].op = op;
    tree_nodes[node_cnt].left_son = left_son;
    tree_nodes[node_cnt].right_son = right_son;
    return node_cnt;
}

long long quick_pow(long long a, long long b) {
    long long ans = 1;
    while (b > 0) {
        if (b & 1) ans *= a;
        a *= a;
        b >>= 1;
    }
    return ans;
}

long long calc(long long a, long long b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') return a / b;
    return quick_pow(a, b);
}

int parse_expression();

int parse_primary() {
    if (expr[pos] == '(') {
        ++pos;
        int root = parse_expression();
        ++pos; // 跳过右括号
        return root;
    }

    long long value = 0;
    while (pos < static_cast<int>(expr.size()) && isdigit(expr[pos])) {
        value = value * 10 + (expr[pos] - '0');
        ++pos;
    }
    return new_number_node(value);
}

int parse_power() {
    int left_root = parse_primary();
    if (pos < static_cast<int>(expr.size()) && expr[pos] == '^') {
        ++pos;
        int right_root = parse_power();
        left_root = new_operator_node('^', left_root, right_root);
    }
    return left_root;
}

int parse_term() {
    int left_root = parse_power();
    while (pos < static_cast<int>(expr.size()) && (expr[pos] == '*' || expr[pos] == '/')) {
        char op = expr[pos];
        ++pos;
        int right_root = parse_power();
        left_root = new_operator_node(op, left_root, right_root);
    }
    return left_root;
}

int parse_expression() {
    int left_root = parse_term();
    while (pos < static_cast<int>(expr.size()) && (expr[pos] == '+' || expr[pos] == '-')) {
        char op = expr[pos];
        ++pos;
        int right_root = parse_term();
        left_root = new_operator_node(op, left_root, right_root);
    }
    return left_root;
}

void build_postfix(int root) {
    if (tree_nodes[root].type == 0) {
        postfix_tokens.push_back({0, tree_nodes[root].value, 0});
        return;
    }
    build_postfix(tree_nodes[root].left_son);
    build_postfix(tree_nodes[root].right_son);
    postfix_tokens.push_back({1, 0, tree_nodes[root].op});
}

void print_postfix_expression(const vector<Token> &tokens) {
    if (tokens.size() == 1 && tokens[0].type == 0) {
        cout << tokens[0].value << '\n';
        return;
    }

    int n = static_cast<int>(tokens.size());
    for (int i = 0; i < n; ++i) {
        if (tokens[i].type == 0) cout << tokens[i].value;
        else cout << tokens[i].op;
        cout << ' ';
    }
    cout << '\n';
}

void simulate_reduction() {
    print_postfix_expression(postfix_tokens);

    while (postfix_tokens.size() > 1) {
        int pos_op = -1;
        int n = static_cast<int>(postfix_tokens.size());
        for (int i = 0; i < n; ++i) {
            if (postfix_tokens[i].type == 1) {
                pos_op = i;
                break;
            }
        }

        long long left_value = postfix_tokens[pos_op - 2].value;
        long long right_value = postfix_tokens[pos_op - 1].value;
        char op = postfix_tokens[pos_op].op;
        long long result = calc(left_value, right_value, op);

        postfix_tokens[pos_op - 2] = {0, result, 0};
        postfix_tokens.erase(postfix_tokens.begin() + pos_op - 1, postfix_tokens.begin() + pos_op + 1);
        print_postfix_expression(postfix_tokens);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> expr;

    int root = parse_expression();
    build_postfix(root);
    simulate_reduction();

    return 0;
}
