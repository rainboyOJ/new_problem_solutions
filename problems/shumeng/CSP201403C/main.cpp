/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:51
 */
#include <bits/stdc++.h>
using namespace std;

bool accepted[26], need_value[26], used[26];
string value[26];

bool is_valid_option(const string &token) {
    return token.size() == 2 && token[0] == '-' && token[1] >= 'a' && token[1] <= 'z' && accepted[token[1] - 'a'];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string format;
    cin >> format;
    for (int i = 0; i < (int)format.size(); i++) {
        if (format[i] >= 'a' && format[i] <= 'z') {
            int id = format[i] - 'a';
            accepted[id] = true;
            need_value[id] = i + 1 < (int)format.size() && format[i + 1] == ':';
        }
    }

    int n;
    cin >> n;
    string line;
    getline(cin, line);

    for (int case_id = 1; case_id <= n; case_id++) {
        getline(cin, line);
        stringstream input(line);
        string program_name;
        input >> program_name;

        string token;
        while (input >> token) {
            if (!is_valid_option(token)) {
                break;
            }

            int id = token[1] - 'a';
            if (need_value[id]) {
                string parameter;
                if (!(input >> parameter)) {
                    break;
                }
                used[id] = true;
                value[id] = parameter;
            } else {
                used[id] = true;
            }
        }

        cout << "Case " << case_id << ':';
        for (int id = 0; id < 26; id++) {
            if (!used[id]) {
                continue;
            }
            cout << " -" << char('a' + id);
            if (need_value[id]) {
                cout << ' ' << value[id];
            }
        }
        cout << '\n';

        memset(used, 0, sizeof(used));
        for (int id = 0; id < 26; id++) {
            value[id].clear();
        }
    }

    return 0;
}
