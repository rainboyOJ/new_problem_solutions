#include <bits/stdc++.h>
using namespace std;

// brute.cpp：小数据精确解。
// 先把表达式解析成语法树，再把它转成关于 a 的多项式。
// 这个做法非常直观，也适合帮助读者理解“等价表达式”的本质，
// 但当表达式次数很大时会变慢，所以只适合作为小数据验证代码。

const int NODE_CONST = 1;
const int NODE_VAR = 2;
const int NODE_ADD = 3;
const int NODE_SUB = 4;
const int NODE_MUL = 5;
const int NODE_POW = 6;

const long long LIMIT = 1000000;
typedef __int128 i128;

struct Node {
    int type;
    long long value;
    int power;
    int left;
    int right;
};

struct Poly {
    vector<i128> c; // c[i] 表示 a^i 的系数
};

struct Parser {
    string s;
    int n;
    int pos;
    bool ok;
    vector<Node> nodes;

    void init(const string &str) {
        s = str;
        n = (int)s.size();
        pos = 0;
        ok = true;
        nodes.clear();
        nodes.push_back(Node());
    }

    void skip_space() {
        while (pos < n && s[pos] == ' ') {
            pos++;
        }
    }

    int new_node(int type, long long value, int power, int left, int right) {
        Node cur;
        cur.type = type;
        cur.value = value;
        cur.power = power;
        cur.left = left;
        cur.right = right;
        nodes.push_back(cur);
        return (int)nodes.size() - 1;
    }

    long long clamp_value(__int128 x) {
        if (x > LIMIT) {
            return LIMIT;
        }
        if (x < -LIMIT) {
            return -LIMIT;
        }
        return (long long)x;
    }

    long long safe_add(long long a, long long b) {
        return clamp_value((__int128)a + (__int128)b);
    }

    long long safe_sub(long long a, long long b) {
        return clamp_value((__int128)a - (__int128)b);
    }

    long long safe_mul(long long a, long long b) {
        return clamp_value((__int128)a * (__int128)b);
    }

    long long safe_pow(long long a, int b) {
        long long ans = 1;
        for (int i = 0; i < b; i++) {
            ans = safe_mul(ans, a);
        }
        return ans;
    }

    bool eval_constant(int u, long long &ret) {
        Node &cur = nodes[u];
        if (cur.type == NODE_CONST) {
            ret = cur.value;
            return true;
        }
        if (cur.type == NODE_VAR) {
            return false;
        }

        long long left_value = 0;
        long long right_value = 0;

        if (!eval_constant(cur.left, left_value)) {
            return false;
        }

        if (cur.type == NODE_POW) {
            ret = safe_pow(left_value, cur.power);
            return true;
        }

        if (!eval_constant(cur.right, right_value)) {
            return false;
        }

        if (cur.type == NODE_ADD) {
            ret = safe_add(left_value, right_value);
            return true;
        }
        if (cur.type == NODE_SUB) {
            ret = safe_sub(left_value, right_value);
            return true;
        }
        if (cur.type == NODE_MUL) {
            ret = safe_mul(left_value, right_value);
            return true;
        }

        return false;
    }

    int parse_expr() {
        int left = parse_term();
        if (!ok) {
            return 0;
        }

        while (true) {
            skip_space();
            if (pos >= n || (s[pos] != '+' && s[pos] != '-')) {
                break;
            }

            char op = s[pos];
            pos++;
            int right = parse_term();
            if (!ok || right == 0) {
                ok = false;
                return 0;
            }

            if (op == '+') {
                left = new_node(NODE_ADD, 0, 0, left, right);
            } else {
                left = new_node(NODE_SUB, 0, 0, left, right);
            }
        }

        return left;
    }

    int parse_term() {
        int left = parse_power();
        if (!ok) {
            return 0;
        }

        while (true) {
            skip_space();
            if (pos >= n || s[pos] != '*') {
                break;
            }

            pos++;
            int right = parse_power();
            if (!ok || right == 0) {
                ok = false;
                return 0;
            }

            left = new_node(NODE_MUL, 0, 0, left, right);
        }

        return left;
    }

    int parse_power() {
        int left = parse_primary();
        if (!ok) {
            return 0;
        }

        while (true) {
            skip_space();
            if (pos >= n || s[pos] != '^') {
                break;
            }

            pos++;
            int right = parse_primary();
            if (!ok || right == 0) {
                ok = false;
                return 0;
            }

            long long exponent = 0;
            if (!eval_constant(right, exponent)) {
                ok = false;
                return 0;
            }
            if (exponent < 1 || exponent > 10) {
                ok = false;
                return 0;
            }

            left = new_node(NODE_POW, 0, (int)exponent, left, 0);
        }

        return left;
    }

    int parse_number() {
        skip_space();
        if (pos >= n || !isdigit(s[pos])) {
            ok = false;
            return 0;
        }

        long long value = 0;
        while (pos < n && isdigit(s[pos])) {
            value = value * 10 + (s[pos] - '0');
            pos++;
        }

        return new_node(NODE_CONST, value, 0, 0, 0);
    }

    int parse_primary() {
        skip_space();
        if (pos >= n) {
            ok = false;
            return 0;
        }

        if (s[pos] == 'a') {
            pos++;
            return new_node(NODE_VAR, 0, 0, 0, 0);
        }
        if (isdigit(s[pos])) {
            return parse_number();
        }
        if (s[pos] == '(') {
            pos++;
            int inside = parse_expr();
            skip_space();
            if (!ok || pos >= n || s[pos] != ')') {
                ok = false;
                return 0;
            }
            pos++;
            return inside;
        }

        ok = false;
        return 0;
    }

    bool build_tree(const string &str, int &root) {
        init(str);
        root = parse_expr();
        skip_space();
        if (!ok || root == 0 || pos != n) {
            return false;
        }
        return true;
    }
};

void trim_poly(Poly &p) {
    while (!p.c.empty() && p.c.back() == 0) {
        p.c.pop_back();
    }
}

Poly make_const(long long x) {
    Poly p;
    p.c.resize(1);
    p.c[0] = (i128)x;
    trim_poly(p);
    return p;
}

Poly make_var() {
    Poly p;
    p.c.resize(2);
    p.c[0] = 0;
    p.c[1] = 1;
    trim_poly(p);
    return p;
}

Poly poly_add(const Poly &a, const Poly &b) {
    Poly c;
    int size_a = (int)a.c.size();
    int size_b = (int)b.c.size();
    int size_c = max(size_a, size_b);

    c.c.assign(size_c, 0);
    for (int i = 0; i < size_a; i++) {
        c.c[i] += a.c[i];
    }
    for (int i = 0; i < size_b; i++) {
        c.c[i] += b.c[i];
    }

    trim_poly(c);
    return c;
}

Poly poly_sub(const Poly &a, const Poly &b) {
    Poly c;
    int size_a = (int)a.c.size();
    int size_b = (int)b.c.size();
    int size_c = max(size_a, size_b);

    c.c.assign(size_c, 0);
    for (int i = 0; i < size_a; i++) {
        c.c[i] += a.c[i];
    }
    for (int i = 0; i < size_b; i++) {
        c.c[i] -= b.c[i];
    }

    trim_poly(c);
    return c;
}

Poly poly_mul(const Poly &a, const Poly &b) {
    Poly c;
    if (a.c.empty() || b.c.empty()) {
        return c;
    }

    int deg_a = (int)a.c.size() - 1;
    int deg_b = (int)b.c.size() - 1;
    c.c.assign(deg_a + deg_b + 1, 0);

    for (int i = 0; i <= deg_a; i++) {
        for (int j = 0; j <= deg_b; j++) {
            c.c[i + j] += a.c[i] * b.c[j];
        }
    }

    trim_poly(c);
    return c;
}

Poly poly_pow(Poly base, int exponent) {
    Poly ans = make_const(1);
    while (exponent > 0) {
        if (exponent & 1) {
            ans = poly_mul(ans, base);
        }
        exponent >>= 1;
        if (exponent > 0) {
            base = poly_mul(base, base);
        }
    }
    trim_poly(ans);
    return ans;
}

Poly build_poly(const vector<Node> &nodes, int u) {
    const Node &cur = nodes[u];

    if (cur.type == NODE_CONST) {
        return make_const(cur.value);
    }
    if (cur.type == NODE_VAR) {
        return make_var();
    }
    if (cur.type == NODE_ADD) {
        return poly_add(build_poly(nodes, cur.left), build_poly(nodes, cur.right));
    }
    if (cur.type == NODE_SUB) {
        return poly_sub(build_poly(nodes, cur.left), build_poly(nodes, cur.right));
    }
    if (cur.type == NODE_MUL) {
        return poly_mul(build_poly(nodes, cur.left), build_poly(nodes, cur.right));
    }

    return poly_pow(build_poly(nodes, cur.left), cur.power);
}

bool same_poly(const Poly &a, const Poly &b) {
    int size_a = (int)a.c.size();
    int size_b = (int)b.c.size();
    int size_c = max(size_a, size_b);

    for (int i = 0; i < size_c; i++) {
        i128 x = 0;
        i128 y = 0;
        if (i < size_a) {
            x = a.c[i];
        }
        if (i < size_b) {
            y = b.c[i];
        }
        if (x != y) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string target_expr;
    getline(cin, target_expr);

    int n;
    cin >> n;
    string useless;
    getline(cin, useless);

    Parser parser;
    int target_root = 0;
    parser.build_tree(target_expr, target_root);
    Poly target_poly = build_poly(parser.nodes, target_root);

    string answer = "";
    for (int i = 0; i < n; i++) {
        string expr;
        getline(cin, expr);

        int root = 0;
        if (!parser.build_tree(expr, root)) {
            continue;
        }

        Poly cur_poly = build_poly(parser.nodes, root);
        if (same_poly(target_poly, cur_poly)) {
            answer.push_back(char('A' + i));
        }
    }

    cout << answer << '\n';

    return 0;
}
