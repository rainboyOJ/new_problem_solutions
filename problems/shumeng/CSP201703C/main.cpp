/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:43
 */
#include <bits/stdc++.h>
using namespace std;

string convert_inline(const string &text) {
    string result;
    int length = (int)text.size();
    for (int i = 0; i < length;) {
        if (text[i] == '_') {
            int end = i + 1;
            while (text[end] != '_') {
                end++;
            }
            result += "<em>" + convert_inline(text.substr(i + 1, end - i - 1)) + "</em>";
            i = end + 1;
        } else if (text[i] == '[') {
            int text_end = i + 1;
            while (text[text_end] != ']') {
                text_end++;
            }
            int link_end = text_end + 2;
            while (text[link_end] != ')') {
                link_end++;
            }
            string link_text = convert_inline(text.substr(i + 1, text_end - i - 1));
            string link = text.substr(text_end + 2, link_end - text_end - 2);
            result += "<a href=\"" + link + "\">" + link_text + "</a>";
            i = link_end + 1;
        } else {
            result += text[i];
            i++;
        }
    }
    return result;
}

bool is_heading(const string &line) {
    return !line.empty() && line[0] == '#';
}

bool is_list_item(const string &line) {
    return !line.empty() && line[0] == '*';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    vector<string> lines;
    string line;
    while (getline(cin, line)) {
        lines.push_back(line);
    }

    int total_lines = (int)lines.size();
    for (int i = 0; i < total_lines;) {
        if (lines[i].empty()) {
            i++;
            continue;
        }

        if (is_heading(lines[i])) {
            int level = 0;
            while (lines[i][level] == '#') {
                level++;
            }
            int content_start = level;
            while (lines[i][content_start] == ' ') {
                content_start++;
            }
            string content = convert_inline(lines[i].substr(content_start));
            cout << "<h" << level << ">" << content << "</h" << level << ">\n";
            i++;
        } else if (is_list_item(lines[i])) {
            cout << "<ul>\n";
            while (i < total_lines && is_list_item(lines[i])) {
                int content_start = 1;
                while (lines[i][content_start] == ' ') {
                    content_start++;
                }
                cout << "<li>" << convert_inline(lines[i].substr(content_start)) << "</li>\n";
                i++;
            }
            cout << "</ul>\n";
        } else {
            cout << "<p>";
            bool first_line = true;
            while (i < total_lines && !lines[i].empty()) {
                if (!first_line) {
                    cout << '\n';
                }
                cout << convert_inline(lines[i]);
                first_line = false;
                i++;
            }
            cout << "</p>\n";
        }
    }

    return 0;
}
