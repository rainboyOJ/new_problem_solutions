/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
// brute.cpp：小数据暴力解，直接重复执行 k 次字符替换，只适合 k 很小的数据。
#include <bits/stdc++.h>
using namespace std;

const int MAXC = 128;

int next_char[MAXC]; // 每个字符经过一次替换后的字符

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 输入行形如 #Hello World#，需要整行读取
    string line;
    getline(cin, line);
    string initial = line.substr(1, line.size() - 2); // 去掉两侧的 # 得到初始字符串

    int n;
    cin >> n;
    getline(cin, line);
    // 未定义的字符替换为自身
    for (int i = 0; i < MAXC; i++) next_char[i] = i;
    for (int i = 0; i < n; i++) {
        getline(cin, line); // 形如 #a b# 或 #x y#
        next_char[(unsigned char)line[1]] = (unsigned char)line[2];
    }

    int m;
    cin >> m;
    for (int query = 0; query < m; query++) {
        int k;
        cin >> k;
        // 每轮把整串字符同时替换一次
        string result = initial;
        for (int step = 0; step < k; step++) {
            for (int i = 0; i < (int)result.size(); i++) {
                result[i] = (char)next_char[(unsigned char)result[i]];
            }
        }
        cout << '#' << result << "#\n";
    }

    return 0;
}
