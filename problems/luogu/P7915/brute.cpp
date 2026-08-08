// brute.cpp：小数据暴力解，按字典序 DFS 枚举 L/R 操作直到得到回文。
#include <bits/stdc++.h>
using namespace std;

int n;
vector<int> origin;
string answer;
bool found;

bool is_palindrome(const vector<int> &b) {
    for (int i = 0, j = (int)b.size() - 1; i < j; i++, j--) {
        if (b[i] != b[j]) {
            return false;
        }
    }
    return true;
}

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
