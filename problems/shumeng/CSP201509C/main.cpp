/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:33
 */
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
    for (int row = 0; row < m; row++) {
        string answer;
        for (int i = 0; i < (int)templ[row].size();) {
            if (i + 2 < (int)templ[row].size() && templ[row].substr(i, 3) == "{{ ") {
                int end = templ[row].find(" }}", i + 3);
                string name = templ[row].substr(i + 3, end - i - 3);
                answer += values[name];
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
