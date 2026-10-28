/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-28 21:25
 * update_at: 2026-10-28 21:29
 */
// brute.cpp：最朴素的模拟。当前串不是回文时，在每个空隙插入一个可能用到的字符，
// 用「限制插入次数的深搜 + 逐层加深」求最少插入数。指数级，只用来观察重复求解。
#include <bits/stdc++.h>
using namespace std;

string s;
string alphabet;   // 原串里出现过的字符（插原串没有的字符不可能更优）
int limit_depth;   // 本轮允许的插入次数上限

bool is_palindrome(const string &t) {
    int i = 0, j = (int)t.size() - 1;
    while (i < j) {
        if (t[i] != t[j]) return false;
        ++i;
        --j;
    }
    return true;
}

// cur 是当前串，depth 是已经插入的字符数；返回能否在 limit_depth 次内变成回文
bool dfs(const string &cur, int depth) {
    if (is_palindrome(cur)) return true;
    if (depth == limit_depth) return false;

    for (int pos = 0; pos <= (int)cur.size(); ++pos) {
        for (char c : alphabet) {
            string nxt = cur;
            nxt.insert(nxt.begin() + pos, c);   // 在第 pos 个空隙插入 c
            if (dfs(nxt, depth + 1)) return true;
        }
    }
    return false;
}

int main() {
    cin >> s;

    bool seen[256] = {false};
    for (char c : s) {
        if (!seen[(unsigned char)c]) {
            seen[(unsigned char)c] = true;
            alphabet += c;
        }
    }

    // 插入次数从 0 往上试：第一次成功就是最少次数
    for (limit_depth = 0; limit_depth <= (int)s.size(); ++limit_depth) {
        if (dfs(s, 0)) {
            cout << limit_depth << "\n";
            break;
        }
    }
    return 0;
}
