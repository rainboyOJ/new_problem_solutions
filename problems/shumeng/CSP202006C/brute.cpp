/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:37
 */
// brute.cpp：直接按文本块和字符折行规则模拟，供小数据核对。
#include <bits/stdc++.h>
using namespace std;

bool is_blank(const string &text) {
    for (int i = 0; i < (int)text.size(); i++) {
        if (text[i] != ' ') return false;
    }
    return true;
}

bool is_item_start(const string &text) {
    return text.size() >= 2 && text[0] == '*' && text[1] == ' ';
}

bool is_item_continuation(const string &text) {
    return text.size() >= 2 && text[0] == ' ' && text[1] == ' ' && !is_blank(text);
}

string trim(const string &text) {
    int left = 0, right = (int)text.size() - 1;
    while (left <= right && text[left] == ' ') left++;
    while (left <= right && text[right] == ' ') right--;
    return text.substr(left, right - left + 1);
}

string join_lines(const vector<string> &line) {
    string text;
    for (int i = 0; i < (int)line.size(); i++) {
        string part = trim(line[i]);
        if (part.empty()) continue;
        if (!text.empty()) text += ' ';
        text += part;
    }
    return text;
}

struct Painter {
    int width, row_count = 0, column = 0;

    void start_line(int indent) {
        row_count++;
        column = indent;
    }

    void start_block() {
        if (row_count > 0) row_count++;
    }

    void write_text(const string &text, int first_indent, int next_indent) {
        int position = 0;
        start_line(first_indent);
        while (position < (int)text.size()) {
            if (column == width) {
                while (position < (int)text.size() && text[position] == ' ') position++;
                if (position == (int)text.size()) break;
                start_line(next_indent);
            }
            column++;
            position++;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    Painter painter;
    cin >> painter.width;
    string line;
    getline(cin, line);
    vector<string> source;
    while (getline(cin, line)) source.push_back(line);

    int position = 0;
    while (position < (int)source.size()) {
        if (is_blank(source[position])) {
            position++;
            continue;
        }
        painter.start_block();
        if (!is_item_start(source[position])) {
            vector<string> paragraph;
            while (position < (int)source.size() && !is_blank(source[position])
                    && !is_item_start(source[position])) {
                paragraph.push_back(source[position++]);
            }
            painter.write_text(join_lines(paragraph), 0, 0);
            continue;
        }

        while (position < (int)source.size() && is_item_start(source[position])) {
            vector<string> item;
            item.push_back(source[position++].substr(2));
            while (position < (int)source.size() && is_item_continuation(source[position])) {
                item.push_back(source[position++].substr(2));
            }
            painter.write_text(join_lines(item), 3, 3);
        }
    }
    cout << painter.row_count << '\n';

    return 0;
}
