/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:33
 */
// brute.cpp：反复寻找下一处标记并构造替换后的行。
#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int m, n;
    cin >> m >> n;
    string line;
    getline(cin, line);
    vector<string> templ(m);
    for (int i = 0; i < m; i++) getline(cin, templ[i]);
    map<string, string> values;
    for (int i = 0; i < n; i++) {
        getline(cin, line);
        int split = line.find(' ');
        values[line.substr(0, split)] = line.substr(split + 2, line.size() - split - 3);
    }
    for (int i = 0; i < m; i++) {
        string answer;
        int start = 0, mark;
        while ((mark = templ[i].find("{{ ", start)) != (int)string::npos) {
            answer += templ[i].substr(start, mark - start);
            int end = templ[i].find(" }}", mark + 3);
            answer += values[templ[i].substr(mark + 3, end - mark - 3)];
            start = end + 3;
        }
        answer += templ[i].substr(start);
        cout << answer << '\n';
    }
    return 0;
}
