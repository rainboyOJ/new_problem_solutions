/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-01 20:28
 * update_at: 2026-10-01 20:28
 */
// subtask_50.cpp：50% 数据 n <= 10，按题意逐层生成完整的 2^n 个格雷码串。
// 从 1 位格雷码开始，每一层把上一层的串按原顺序补前缀 0、按逆序补前缀 1，
// 一直推到 n 位，再直接输出第 k 个。只有 n 很小、2^n 装得下时才可行。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int n;             // 编码位数，本文件只处理 n <= 10
ll k;              // 编号，50% 数据里 k < 2^10
vector<string> gray; // gray[i] = 当前这一层的第 i 个格雷码串

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    // 第 1 层：只有 "0" 和 "1"。
    gray.push_back("0");
    gray.push_back("1");

    // 每推一层，串的数量翻倍：前半段保持原顺序补 0，后半段逆序补 1。
    for (int len = 2; len <= n; len++) {
        int cnt = gray.size(); // 上一层共有 2^(len-1) 个串
        vector<string> cur;
        for (int i = 0; i < cnt; i++) {
            cur.push_back("0" + gray[i]); // 前半段：原顺序补 0
        }
        for (int i = cnt - 1; i >= 0; i--) {
            cur.push_back("1" + gray[i]); // 后半段：逆序补 1
        }
        gray = cur;
    }

    cout << gray[k] << '\n';

    return 0;
}
