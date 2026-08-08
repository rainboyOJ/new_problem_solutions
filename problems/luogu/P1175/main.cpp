#include <bits/stdc++.h>
using namespace std;

struct Token {
    int type; // 0 表示数字，1 表示运算符
    long long value;
    char op;
};

string expr;
vector<Token> infix_tokens;
vector<Token> postfix_tokens;
stack<char> op_stack;

int get_priority(char op) {
    if (op == '^') return 3;
    if (op == '*' || op == '/') return 2;
    if (op == '+' || op == '-') return 1;
    return 0;
}

bool is_right_associative(char op) {
    return op == '^';
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

void split_infix_tokens() {
    int n = static_cast<int>(expr.size());
    for (int i = 0; i < n;) {
        if (isdigit(expr[i])) {
            long long value = 0;
            while (i < n && isdigit(expr[i])) {
                value = value * 10 + (expr[i] - '0');
                ++i;
            }
            infix_tokens.push_back({0, value, 0});
        } else {
            infix_tokens.push_back({1, 0, expr[i]});
            ++i;
        }
    }
}

void convert_to_postfix() {
    int m = static_cast<int>(infix_tokens.size());
    for (int i = 0; i < m; ++i) {
        Token cur = infix_tokens[i];
        if (cur.type == 0) {
            postfix_tokens.push_back(cur);
            continue;
        }

        if (cur.op == '(') {
            op_stack.push(cur.op);
            continue;
        }

        if (cur.op == ')') {
            while (!op_stack.empty() && op_stack.top() != '(') {
                postfix_tokens.push_back({1, 0, op_stack.top()});
                op_stack.pop();
            }
            if (!op_stack.empty()) op_stack.pop();
            continue;
        }

        while (!op_stack.empty() && op_stack.top() != '(') {
            char top_op = op_stack.top();
            int top_pri = get_priority(top_op);
            int cur_pri = get_priority(cur.op);
            if (top_pri > cur_pri || (top_pri == cur_pri && !is_right_associative(cur.op))) {
                postfix_tokens.push_back({1, 0, top_op});
                op_stack.pop();
            } else {
                break;
            }
        }
        op_stack.push(cur.op);
    }

    while (!op_stack.empty()) {
        postfix_tokens.push_back({1, 0, op_stack.top()});
        op_stack.pop();
    }
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
        int pos = -1;
        int n = static_cast<int>(postfix_tokens.size());
        for (int i = 0; i < n; ++i) {
            if (postfix_tokens[i].type == 1) {
                pos = i;
                break;
            }
        }

        long long left_value = postfix_tokens[pos - 2].value;
        long long right_value = postfix_tokens[pos - 1].value;
        char op = postfix_tokens[pos].op;
        long long result = calc(left_value, right_value, op);

        postfix_tokens[pos - 2] = {0, result, 0};
        postfix_tokens.erase(postfix_tokens.begin() + pos - 1, postfix_tokens.begin() + pos + 1);
        print_postfix_expression(postfix_tokens);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> expr;

    split_infix_tokens();
    convert_to_postfix();
    simulate_reduction();

    return 0;
}
