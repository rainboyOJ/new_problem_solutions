/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-13 13:29
 * update_at: 2026-08-13 13:35
 */
/* P1032 字串变换 */
/* brute.cpp：小数据暴力解，把每一步操作看成选择序列来递归枚举。 */
/* 每层递归选择一个决策：(用哪条规则, 替换哪个出现位置)，深度限制在 10 步。 */

#include <bits/stdc++.h>
using namespace std;

const int MAX_STEP = 10; // 题目要求十步以内（含十步）

string start_str, target_str; // 起始串与目标串
string from[10], to[10];      // 变换规则
int rule_cnt;                 // 规则数量

int best = MAX_STEP + 1; // best 记录当前找到的最少步数，MAX_STEP+1 表示无解

int choose_step[MAX_STEP + 1]; // 第 dep 步选择用哪条规则
int choose_pos[MAX_STEP + 1];  // 第 dep 步替换的是哪个出现位置

set<pair<string, int> > vis; // 判重：(当前串, 已用步数) 相同就无需再搜

// dfs(dep, s)：当前已经变换了 dep 步，当前串是 s。
// 这一层在枚举第 dep+1 步的决策：某条规则 + 它在 s 中的一个出现位置。
void dfs(int dep, string s) {
    if (s == target_str) {
        if (dep < best) best = dep; // 到达目标，记录所用步数
        return;
    }
    if (dep == MAX_STEP || dep >= best)
        return; // 达到步数上限或不可能更优

    // 同样步数下到达同一个串，之前已经搜过，直接跳过
    pair<string, int> key = make_pair(s, dep);
    if (vis.find(key) != vis.end())
        return;
    vis.insert(key);

    // 枚举第 dep+1 步的决策
    for (int r = 0; r < rule_cnt; r++) {
        int flen = from[r].size();

        // 枚举规则 r 在当前串 s 中的所有出现位置
        size_t pos = s.find(from[r]);
        while (pos != string::npos) {
            choose_step[dep + 1] = r;
            choose_pos[dep + 1] = (int)pos;

            string next_s = s.substr(0, pos) + to[r]
                          + s.substr(pos + flen);
            dfs(dep + 1, next_s);

            // 从下一个位置继续找，覆盖重叠出现
            pos = s.find(from[r], pos + 1);
        }
    }
}

int main() {
    cin >> start_str >> target_str;

    // 规则行读到 EOF 结束
    string a, b;
    while (cin >> a >> b) {
        from[rule_cnt] = a;
        to[rule_cnt] = b;
        rule_cnt++;
    }

    dfs(0, start_str);

    if (best == MAX_STEP + 1)
        cout << "NO ANSWER!\n";
    else
        cout << best << "\n";

    return 0;
}
