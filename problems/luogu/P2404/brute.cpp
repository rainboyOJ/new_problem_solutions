/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:27
 * update_at: 2026-08-13 13:29
 */
// brute.cpp：小数据暴力解，使用 01 序列 / 选择序列递归枚举所有可能。
// 把 n 看成 n 个连着的单位与它们之间的 n-1 个间隔，
// choose[i] = 1 表示把第 i 个间隔切开，切出来的每块单位数组成一个有序拆分。
// 把所有有序拆分排序去重，得到全部非递减拆分方案，再按字典序输出。
// 只适合小数据：2^(n-1) 个 01 序列，n 稍大就爆炸。
#include <bits/stdc++.h>
using namespace std;

const int MAXN = 10;

int n;
int choose[MAXN];  // choose[i] 表示第 i 个间隔是否切开：0 不切，1 切
vector<string> ans; // 去重后的全部非递减拆分字符串

// 由当前完整的 choose[1..n-1] 生成拆分字符串，去重后放入答案。
void calc_answer() {
    vector<int> part; // 每块的长度
    int len = 1;      // 当前块长度，第 1 个间隔前已有一个单位
    for (int i = 1; i < n; i++) {
        if (choose[i] == 1) { // 在第 i 个间隔切开，一块结束
            part.push_back(len);
            len = 1;
        } else {
            len++; // 不切开，继续累计当前块
        }
    }
    part.push_back(len); // 最后一块

    if ((int)part.size() == 1)
        return; // 只有一个块 = 方案 n 本身，题目不要求

    sort(part.begin(), part.end()); // 有序拆分排序成非递减序列

    string s;
    for (int i = 0; i < (int)part.size(); i++) {
        if (i > 0)
            s += "+";
        s += to_string(part[i]);
    }
    // 同一组加数会以多种顺序出现，这里暴力去重。
    for (int i = 0; i < (int)ans.size(); i++) {
        if (ans[i] == s)
            return;
    }
    ans.push_back(s);
}

// 这一层决定第 dep 个间隔切不切，dep 从 1 到 n-1。
void dfs(int dep) {
    if (dep == n) {
        calc_answer(); // 完整 01 序列生成后统一检查
        return;
    }
    for (int i = 0; i <= 1; i++) {
        choose[dep] = i;
        dfs(dep + 1);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n;
    dfs(1);

    sort(ans.begin(), ans.end()); // 最后统一按字典序输出
    for (int i = 0; i < (int)ans.size(); i++) {
        cout << ans[i] << "\n";
    }
    return 0;
}
