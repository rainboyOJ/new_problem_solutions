// brute.cpp：小数据暴力解，枚举每个数字对应的所有字母选择。
#include <bits/stdc++.h>
using namespace std;

const string m[] = {"", "", "abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

int n;
string digits;
string cur;
vector<string> ans;

void dfs(int i) {
    if (i == n) {
        ans.push_back(cur);
        return;
    }
    for (char ch : m[digits[i] - '0']) {
        cur.push_back(ch);
        dfs(i + 1);
        cur.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> digits;
    n = digits.size();
    if (n == 0)
        return 0;
    dfs(0);
    for (auto &s : ans)
        cout << s << ' ';
    return 0;
}
