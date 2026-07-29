// brute.cpp：小数据暴力解，01 序列递归枚举所有括号序列，叶子节点检查合法性。
#include <bits/stdc++.h>
using namespace std;

int n;
int choose[20]; // 0 = '(' , 1 = ')'
vector<string> ans;

bool check() {
    int bal = 0;
    for (int i = 1; i <= 2 * n; i++) {
        if (choose[i] == 0)
            bal++;
        else
            bal--;
        if (bal < 0)
            return false;
    }
    return bal == 0;
}

void dfs(int dep) {
    if (dep == 2 * n + 1) {
        if (check()) {
            string s;
            for (int i = 1; i <= 2 * n; i++)
                s += (choose[i] == 0 ? '(' : ')');
            ans.push_back(s);
        }
        return;
    }
    choose[dep] = 0;
    dfs(dep + 1);
    choose[dep] = 1;
    dfs(dep + 1);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cin >> n;
    dfs(1);
    for (auto &s : ans)
        cout << s << '\n';
    return 0;
}
