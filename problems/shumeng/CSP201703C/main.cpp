/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:48
 */
#include <bits/stdc++.h>
using namespace std;

// 转换一行文字里的行内结构：_Text_ -> <em>Text</em>，
// [Text](Link) -> <a href="Link">Text</a>。两种结构可以互相嵌套。
// 递归处理内部文字，保证嵌套（链接在强调内、强调在链接文字内）也能正确转换。
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
            i++; // 空行只分隔区块，不输出任何内容
            continue;
        }

        if (is_heading(lines[i])) {
            // 标题：统计开头的 # 个数得到等级，跳过后面的空格得到标题内容
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
            // 列表：连续以 * 开头的行属于同一个列表
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
            // 段落：连续非空行构成一个段落，内部换行原样保留
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