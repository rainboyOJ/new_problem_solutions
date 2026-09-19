/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-19 18:07
 * update_at: 2026-09-19 18:07
 */
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举 X 的所有子序列。
// 每一层决定 X 的第 dep 个字符选或不选，选出来的字符按原顺序拼成 candidate；
// 到了叶子节点再检查 candidate 是否是 Y 的子序列，是就更新答案。
// 只有 n <= 20 左右才跑得动，只用来对拍和理解题意。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 25;

string x, y;

int n;              // 序列 X 的长度，递归层数就是它
int choose[MAXN];   // choose[i] 表示 X 的第 i 个字符选(1)还是不选(0)
string candidate;   // 由 X 中所有被选的字符按原顺序拼成的子序列
int ans;            // 目前找到的最长公共子序列长度

// 判断 s 是否是 y 的子序列：在 y 上顺序扫描，能依次匹配完 s 就算成功。
bool is_subsequence(const string &s) {
    int pos = 0;
    for (int i = 0; i < (int)y.size() && pos < (int)s.size(); i++) {
        if (y[i] == s[pos]) pos++;
    }
    return pos == (int)s.size();
}

void dfs(int dep) {
    if (dep > n) {
        // 完整的选择序列已经生成，检查候选子序列并统计答案
        if (is_subsequence(candidate)) {
            if (ans < (int)candidate.size()) ans = candidate.size();
        }
        return;
    }

    // 这一层选择 X 的第 dep 个字符：0 不选，1 选
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        if (i == 1) candidate.push_back(x[dep - 1]);
        dfs(dep + 1);
        if (i == 1) candidate.pop_back();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> x >> y;
    n = x.size();

    dfs(1);
    cout << ans << "\n";

    return 0;
}
