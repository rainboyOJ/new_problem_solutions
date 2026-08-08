// brute.cpp：小数据暴力解，逐个构造根到节点的括号串，再枚举所有子串检查是否合法。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 105;

int n;
string bracket_string;
int parent_node[MAXN];

bool is_valid(const string &s, int l, int r) {
    int balance = 0;
    for (int i = l; i <= r; i++) {
        if (s[i] == '(') {
            balance++;
        } else {
            balance--;
        }
        if (balance < 0) {
            return false;
        }
    }
    return balance == 0;
}

string build_path_string(int u) {
    vector<int> nodes;
    while (u != 0) {
        nodes.push_back(u);
        u = parent_node[u];
    }
    reverse(nodes.begin(), nodes.end());

    string s;
    for (int i = 0; i < (int)nodes.size(); i++) {
        s.push_back(bracket_string[nodes[i] - 1]);
    }
    return s;
}

long long count_valid_substrings(const string &s) {
    long long count_answer = 0;
    int len = (int)s.size();
    for (int l = 0; l < len; l++) {
        for (int r = l; r < len; r++) {
            if (is_valid(s, l, r)) {
                count_answer++;
            }
        }
    }
    return count_answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    cin >> bracket_string;
    for (int i = 2; i <= n; i++) {
        cin >> parent_node[i];
    }

    long long answer = 0;
    for (int i = 1; i <= n; i++) {
        string path_string = build_path_string(i);
        long long k_i = count_valid_substrings(path_string);
        answer ^= 1LL * i * k_i;
    }

    cout << answer << '\n';
    return 0;
}
