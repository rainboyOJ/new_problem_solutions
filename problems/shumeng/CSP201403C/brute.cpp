/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:51
 */
// brute.cpp：直接按格式字符串查找选项类型并模拟扫描。
#include <bits/stdc++.h>
using namespace std;

int option_position(const string &format, char option) {
    for (int i = 0; i < (int)format.size(); i++) {
        if (format[i] == option) {
            return i;
        }
    }
    return -1;
}

bool is_option_token(const string &token) {
    return token.size() == 2 && token[0] == '-' && token[1] >= 'a' && token[1] <= 'z';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string format;
    cin >> format;

    int n;
    cin >> n;
    string line;
    getline(cin, line);

    for (int case_id = 1; case_id <= n; case_id++) {
        getline(cin, line);
        stringstream input(line);
        string program_name, token;
        input >> program_name;

        bool used[26] = {0};
        string value[26];
        while (input >> token) {
            if (!is_option_token(token)) {
                break;
            }

            int position = option_position(format, token[1]);
            if (position == -1) {
                break;
            }

            int id = token[1] - 'a';
            bool need_value = position + 1 < (int)format.size() && format[position + 1] == ':';
            if (need_value) {
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
            int position = option_position(format, char('a' + id));
            if (position + 1 < (int)format.size() && format[position + 1] == ':') {
                cout << ' ' << value[id];
            }
        }
        cout << '\n';
    }

    return 0;
}
