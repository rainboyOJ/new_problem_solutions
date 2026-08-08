#include <bits/stdc++.h>
using namespace std;

const int NODE_CONST = 1;
const int NODE_VAR = 2;
const int NODE_ADD = 3;
const int NODE_SUB = 4;
const int NODE_MUL = 5;
const int NODE_POW = 6;

const long long LIMIT = 1000000;
const int TEST_CNT = 4;
const long long MODS[TEST_CNT] = {1000000007LL, 1000000009LL, 998244353LL, 1004535809LL};
const long long VALUES[TEST_CNT] = {911382323LL, 972663749LL, 911382323LL, 97266353LL};

struct Node {
    int type;
    long long value; // 常数节点的值
    int power;       // 乘方节点的指数，保证是 1..10
    int left;
    int right;
};

struct Parser {
    string s;
    int n;
    int pos;
    bool ok;
    vector<Node> nodes;

    Parser() {
        n = 0;
        pos = 0;
        ok = true;
    }

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

    // 判断一棵子树是否是不含变量的常量表达式。
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
            if (pos >= n) {
                break;
            }

            if (s[pos] != '+' && s[pos] != '-') {
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

long long mod_pow(long long a, int b, long long mod) {
    long long ans = 1 % mod;
    long long base = a % mod;

    while (b > 0) {
        if (b & 1) {
            ans = (__int128)ans * base % mod;
        }
        base = (__int128)base * base % mod;
        b >>= 1;
    }

    return ans;
}

long long norm_mod(long long x, long long mod) {
    x %= mod;
    if (x < 0) {
        x += mod;
    }
    return x;
}

long long eval_mod(const vector<Node> &nodes, int u, long long a_value, long long mod) {
    const Node &cur = nodes[u];

    if (cur.type == NODE_CONST) {
        return norm_mod(cur.value, mod);
    }
    if (cur.type == NODE_VAR) {
        return a_value % mod;
    }
    if (cur.type == NODE_ADD) {
        long long left_value = eval_mod(nodes, cur.left, a_value, mod);
        long long right_value = eval_mod(nodes, cur.right, a_value, mod);
        return (left_value + right_value) % mod;
    }
    if (cur.type == NODE_SUB) {
        long long left_value = eval_mod(nodes, cur.left, a_value, mod);
        long long right_value = eval_mod(nodes, cur.right, a_value, mod);
        return norm_mod(left_value - right_value, mod);
    }
    if (cur.type == NODE_MUL) {
        long long left_value = eval_mod(nodes, cur.left, a_value, mod);
        long long right_value = eval_mod(nodes, cur.right, a_value, mod);
        return (__int128)left_value * right_value % mod;
    }

    long long left_value = eval_mod(nodes, cur.left, a_value, mod);
    return mod_pow(left_value, cur.power, mod);
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

    vector<long long> target_signature(TEST_CNT, 0);
    for (int i = 0; i < TEST_CNT; i++) {
        target_signature[i] = eval_mod(parser.nodes, target_root, VALUES[i], MODS[i]);
    }

    string answer = "";
    for (int i = 0; i < n; i++) {
        string expr;
        getline(cin, expr);

        int root = 0;
        if (!parser.build_tree(expr, root)) {
            continue;
        }

        bool same = true;
        for (int j = 0; j < TEST_CNT; j++) {
            long long cur_value = eval_mod(parser.nodes, root, VALUES[j], MODS[j]);
            if (cur_value != target_signature[j]) {
                same = false;
                break;
            }
        }

        if (same) {
            answer.push_back(char('A' + i));
        }
    }

    cout << answer << '\n';

    return 0;
}
