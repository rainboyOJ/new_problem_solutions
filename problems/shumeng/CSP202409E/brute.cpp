/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，直接保存每块木板上的原始段编号，每步扫描整块木板。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, k;
    cin >> n >> m >> k;
    vector<int> color(n + 1);
    for (int i = 1; i <= n; i++) cin >> color[i];

    vector<vector<int> > board(k + 2); // board[i] 保存第 i 块木板上的段编号序列
    for (int i = 1; i <= n; i++) board[1].push_back(i);
    for (int operation = 1; operation <= k; operation++) {
        int source, left_key, right_key;
        cin >> source >> left_key >> right_key;
        // 扫描整块木板，按编号范围拆成选中段与剩余段
        vector<int> selected;
        vector<int> remaining;
        for (int i = 0; i < (int)board[source].size(); i++) {
            int position = board[source][i];
            if (left_key <= position && position <= right_key) selected.push_back(position);
            else remaining.push_back(position);
        }
        board[source] = remaining;
        board[operation + 1] = selected;

        // 统计新木板的不同颜色数与颜色段数（连续同色计为一段）
        vector<char> appeared(m + 1, 0);
        int distinct = 0;
        int runs = 0;
        int previous_color = -1;
        for (int i = 0; i < (int)selected.size(); i++) {
            int current_color = color[selected[i]];
            if (!appeared[current_color]) {
                appeared[current_color] = 1;
                distinct++;
            }
            if (i == 0 || current_color != previous_color) runs++;
            previous_color = current_color;
        }
        cout << distinct << ' ' << runs << '\n';
    }
    return 0;
}
