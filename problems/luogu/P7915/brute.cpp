/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 22:33
 * update_at: 2026-10-01 22:33
 */
// brute.cpp：小数据暴力解，按字典序 DFS 枚举 L/R 操作直到得到回文。
// 适合很小的数据（对拍生成 n <= 7），指数级复杂度。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;                 // n <= 7（对拍），int 足够
vector<int> origin;    // origin[1..2n]：给定序列，值域 1..n，int 足够
string answer;
bool found;

// 判断序列 b 是否为回文。
bool is_palindrome(const vector<int> &b) {
    for (int i = 0, j = (int)b.size() - 1; i < j; i++, j--) {
        if (b[i] != b[j]) {
            return false;
        }
    }
    return true;
}

// 递归枚举取数操作：这一层选择从左端（L）或右端（R）取数。
// 字典序要求优先尝试 L，先找到的完整方案就是字典序最小的。
void dfs(int l, int r, vector<int> &b, string &ops) {
    if (found) {
        return;
    }
    if (l > r) {
        if (is_palindrome(b)) {
            answer = ops;
            found = true;
        }
        return;
    }

    // 字典序要求优先尝试 L。
    b.push_back(origin[l]);
    ops.push_back('L');
    dfs(l + 1, r, b, ops);
    ops.pop_back();
    b.pop_back();

    b.push_back(origin[r]);
    ops.push_back('R');
    dfs(l, r - 1, b, ops);
    ops.pop_back();
    b.pop_back();
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;
    while (T--) {
        cin >> n;
        origin.assign(2 * n + 1, 0);
        for (int i = 1; i <= 2 * n; i++) {
            cin >> origin[i];
        }

        answer.clear();
        found = false;
        vector<int> b;
        string ops;
        dfs(1, 2 * n, b, ops);

        if (found) {
            cout << answer << '\n';
        } else {
            cout << -1 << '\n';
        }
    }

    return 0;
}
