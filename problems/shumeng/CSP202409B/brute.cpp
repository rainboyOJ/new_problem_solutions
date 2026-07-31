/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-01 01:17
 */
// brute.cpp：小数据暴力解，直接重复执行字符替换。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string line;
    getline(cin, line);
    string initial = line.substr(1, line.size() - 2);

    int n;
    cin >> n;
    getline(cin, line);
    int next_char[128];
    for (int i = 0; i < 128; i++) next_char[i] = i;
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        next_char[(unsigned char)line[1]] = (unsigned char)line[2];
    }

    int m;
    cin >> m;
    for (int query = 0; query < m; query++) {
        int k;
        cin >> k;
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
