/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 12:39
 * update_at: 2026-07-11 12:40
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

int n, q;
vector<string> words;

bool eval_expression(vector<string> expr) {
    vector<string> groups;
    int i = 0;

    // 先把连续 and 段计算成一个 boolean。
    while (i < (int)expr.size()) {
        bool value = (expr[i] == "true");
        int j = i + 1;
        while (j < (int)expr.size() && expr[j] == "and") {
            bool next_value = (expr[j + 1] == "true");
            value = value && next_value;
            j += 2;
        }
        groups.push_back(value ? "true" : "false");
        i = j + 1; // 跳过当前 group 后面的 or。
    }

    // group 之间都是 or，只要有一个 true 即可。
    for (int k = 0; k < (int)groups.size(); k++) {
        if (groups[k] == "true") {
            return true;
        }
    }
    return false;
}

bool check_query(int l, int r, string want) {
    bool target = (want == "true");

    for (int value = 0; value <= 1; value++) {
        vector<string> expr;
        for (int i = 1; i < l; i++) {
            expr.push_back(words[i]);
        }
        expr.push_back(value == 1 ? "true" : "false");
        for (int i = r + 1; i <= n; i++) {
            expr.push_back(words[i]);
        }

        if (eval_expression(expr) == target) {
            return true;
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    words.assign(n + 1, "");
    for (int i = 1; i <= n; i++) {
        cin >> words[i];
    }

    for (int i = 1; i <= q; i++) {
        int l, r;
        string want;
        cin >> l >> r >> want;
        cout << (check_query(l, r, want) ? 'Y' : 'N');
    }
    cout << '\n';

    return 0;
}
