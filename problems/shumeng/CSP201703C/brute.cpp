/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 19:43
 */
// brute.cpp：先按空行显式拆分区块，再按语法逐块转换。
#include <bits/stdc++.h>
using namespace std;

string convert_inline(const string &text) {
    string result;
    for (int i = 0; i < (int)text.size();) {
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
            string content = convert_inline(text.substr(i + 1, text_end - i - 1));
            string url = text.substr(text_end + 2, link_end - text_end - 2);
            result += "<a href=\"" + url + "\">" + content + "</a>";
            i = link_end + 1;
        } else {
            result += text[i++];
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

    vector<vector<string> > blocks;
    vector<string> current_block;
    string line;
    while (getline(cin, line)) {
        if (line.empty()) {
            if (!current_block.empty()) {
                blocks.push_back(current_block);
                current_block.clear();
            }
        } else {
            current_block.push_back(line);
        }
    }
    if (!current_block.empty()) {
        blocks.push_back(current_block);
    }

    for (int i = 0; i < (int)blocks.size(); i++) {
        vector<string> &block = blocks[i];
        if (is_heading(block[0])) {
            int level = 0;
            while (block[0][level] == '#') {
                level++;
            }
            int content_start = level;
            while (block[0][content_start] == ' ') {
                content_start++;
            }
            cout << "<h" << level << ">" << convert_inline(block[0].substr(content_start));
            cout << "</h" << level << ">\n";
        } else if (is_list_item(block[0])) {
            cout << "<ul>\n";
            for (int j = 0; j < (int)block.size(); j++) {
                int content_start = 1;
                while (block[j][content_start] == ' ') {
                    content_start++;
                }
                cout << "<li>" << convert_inline(block[j].substr(content_start)) << "</li>\n";
            }
            cout << "</ul>\n";
        } else {
            cout << "<p>";
            for (int j = 0; j < (int)block.size(); j++) {
                if (j > 0) {
                    cout << '\n';
                }
                cout << convert_inline(block[j]);
            }
            cout << "</p>\n";
        }
    }

    return 0;
}
