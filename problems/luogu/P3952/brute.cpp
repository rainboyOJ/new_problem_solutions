// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

const int MAXL = 105;

struct Node {
    int type;               // 0: 常数循环, 1: 乘一个 n, 2: 死循环, 3: 根节点
    string var;             // 当前循环变量名
    bool claimed;           // 是否成功占用变量名
    vector<int> children;   // 子循环
};

int test_cnt;
int line_cnt;
string target_complexity;

Node tree[MAXL];
int node_cnt;
int stk[MAXL];
int top_ptr;
bool used_var[256];

int parse_target_power(const string &s) {
    if (s == "O(1)") return 0;
    if (s == "O(n)") return 1;

    int pos1 = s.find('^');
    int pos2 = s.find(')');
    int value = 0;
    for (int i = pos1 + 1; i < pos2; i++) {
        value = value * 10 + (s[i] - '0');
    }
    return value;
}

bool is_n(const string &s) {
    return s == "n";
}

int to_number(const string &s) {
    int value = 0;
    for (int i = 0; i < (int)s.size(); i++) {
        value = value * 10 + (s[i] - '0');
    }
    return value;
}

int get_loop_type(const string &x, const string &y) {
    bool x_is_n = is_n(x);
    bool y_is_n = is_n(y);

    if (!x_is_n && !y_is_n) {
        int lx = to_number(x);
        int ry = to_number(y);
        if (lx > ry) return 2;
        return 0;
    }

    if (!x_is_n && y_is_n) return 1;
    if (x_is_n && !y_is_n) return 2;
    return 0;
}

int dfs_power(int u) {
    if (tree[u].type == 2) return 0;

    int best = 0;
    for (int i = 0; i < (int)tree[u].children.size(); i++) {
        int v = tree[u].children[i];
        best = max(best, dfs_power(v));
    }

    if (tree[u].type == 1) return best + 1;
    return best;
}

int solve_one_case() {
    cin >> line_cnt >> target_complexity;

    memset(used_var, 0, sizeof(used_var));
    node_cnt = 0;
    top_ptr = 1;
    stk[1] = 0;
    tree[0].type = 3;
    tree[0].var = "";
    tree[0].claimed = false;
    tree[0].children.clear();

    bool has_error = false;

    for (int i = 1; i <= line_cnt; i++) {
        string op;
        cin >> op;

        if (op == "F") {
            string var, x, y;
            cin >> var >> x >> y;

            node_cnt++;
            tree[node_cnt].type = get_loop_type(x, y);
            tree[node_cnt].var = var;
            tree[node_cnt].claimed = false;
            tree[node_cnt].children.clear();

            unsigned char name = (unsigned char)var[0];
            if (used_var[name]) {
                has_error = true;
            } else {
                used_var[name] = true;
                tree[node_cnt].claimed = true;
            }

            tree[stk[top_ptr]].children.push_back(node_cnt);
            top_ptr++;
            stk[top_ptr] = node_cnt;
        } else {
            if (top_ptr == 1) {
                has_error = true;
                continue;
            }

            int u = stk[top_ptr];
            if (tree[u].claimed) {
                unsigned char name = (unsigned char)tree[u].var[0];
                used_var[name] = false;
            }
            top_ptr--;
        }
    }

    if (top_ptr != 1) {
        has_error = true;
    }

    if (has_error) return -1;

    int target_power = parse_target_power(target_complexity);
    int real_power = dfs_power(0);
    if (real_power == target_power) return 1;
    return 0;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> test_cnt;
    while (test_cnt--) {
        int result = solve_one_case();
        if (result == -1) {
            cout << "ERR\n";
        } else if (result == 1) {
            cout << "Yes\n";
        } else {
            cout << "No\n";
        }
    }

    return 0;
}
