/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:56
 */
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    string line;
    getline(cin, line); // 吃掉第一行末尾的换行符
    vector<string> templ(m); // 模板的每一行
    for (int i = 0; i < m; i++) getline(cin, templ[i]);

    // 变量表：变量名 -> 变量值（值形如 "xxx"，去掉两侧双引号）。
    map<string, string> values;
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        int split = line.find(' ');
        values[line.substr(0, split)] = line.substr(split + 2, line.size() - split - 3);
    }

    // 逐行扫描模板：普通字符直接复制，遇到 {{ 标记则替换为变量值。
    for (int row = 0; row < m; row++) {
        string answer;
        for (int i = 0; i < (int)templ[row].size();) {
            if (i + 2 < (int)templ[row].size() && templ[row].substr(i, 3) == "{{ ") {
                int end = templ[row].find(" }}", i + 3);
                string name = templ[row].substr(i + 3, end - i - 3);
                answer += values[name]; // 未定义变量自动得到空串
                i = end + 3;
            } else {
                answer += templ[row][i];
                i++;
            }
        }
        cout << answer << '\n';
    }
    return 0;
}
