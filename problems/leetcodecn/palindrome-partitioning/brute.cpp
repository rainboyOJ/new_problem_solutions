// brute.cpp：小数据暴力解，枚举每段终点只递归回文前缀，与 main.cpp 同序。
#include <bits/stdc++.h>
using namespace std;

string s;
int n;
vector<vector<string>> ans;
vector<string> cur;

bool is_pal(int l, int r) {
    while (l < r) {
        if (s[l] != s[r])
            return false;
        l++;
        r--;
    }
    return true;
}

void dfs(int i) {
    if (i == n) {
        ans.push_back(cur);
        return;
    }
    for (int j = i; j < n; j++) {
        if (is_pal(i, j)) {
            cur.push_back(s.substr(i, j - i + 1));
            dfs(j + 1);
            cur.pop_back();
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> s;
    n = s.size();
    dfs(0);
    for (auto &v : ans) {
        for (auto &x : v)
            cout << x << ' ';
        cout << '\n';
    }
    return 0;
}
