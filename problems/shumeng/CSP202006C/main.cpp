/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:39
 */
#include <bits/stdc++.h>
using namespace std;

// 判断一行是否只由空格组成（空白行分隔段落和项目列表）
bool is_blank(const string &text) {
    for (int i = 0; i < (int)text.size(); i++) {
        if (text[i] != ' ') return false;
    }
    return true;
}

// 判断一行是否是项目首行：以 "* " 开头
bool is_item_start(const string &text) {
    return text.size() >= 2 && text[0] == '*' && text[1] == ' ';
}

// 判断一行是否是项目续行：以两个空格开头且非空白行
bool is_item_continuation(const string &text) {
    return text.size() >= 2 && text[0] == ' ' && text[1] == ' ' && !is_blank(text);
}

// 去掉一行首尾的连续空格
string trim(const string &text) {
    int left = 0, right = (int)text.size() - 1;
    while (left <= right && text[left] == ' ') left++;
    while (left <= right && text[right] == ' ') right--;
    return text.substr(left, right - left + 1);
}

// 把一个块的所有文本行去首尾空格后，用单个空格连接成一段文本
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

// 终端输出器：维护当前行已写列数和总行数，负责折行与缩进
struct Painter {
    int width, row_count = 0, column = 0;

    // 另起一行，行首缩进 indent 个列
    void start_line(int indent) {
        row_count++;
        column = indent;
    }

    // 每个新块与之前的块之间空一行
    void start_block() {
        if (row_count > 0) row_count++;
    }

    // 逐字符写入文本，写满宽度时先删除待写开头空格，再折行
    void write_text(const string &text, int first_indent, int next_indent) {
        int position = 0;
        start_line(first_indent);
        while (position < (int)text.size()) {
            if (column == width) {
                // 折行前删除待写文本开头的连续空格
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
    getline(cin, line);   // 读掉宽度数字后的换行
    vector<string> source;
    while (getline(cin, line)) source.push_back(line);

    int position = 0;
    while (position < (int)source.size()) {
        if (is_blank(source[position])) {
            position++;
            continue;
        }
        painter.start_block();
        // 普通段落：连续的、非空白、非项目首行的行
        if (!is_item_start(source[position])) {
            vector<string> paragraph;
            while (position < (int)source.size() && !is_blank(source[position])
                    && !is_item_start(source[position])) {
                paragraph.push_back(source[position++]);
            }
            painter.write_text(join_lines(paragraph), 0, 0);
            continue;
        }

        // 项目列表：连续的 "* " 开头行，各自跟随两个空格开头的续行
        while (position < (int)source.size() && is_item_start(source[position])) {
            vector<string> item;
            item.push_back(source[position++].substr(2));   // 去掉行首的 "* "
            while (position < (int)source.size() && is_item_continuation(source[position])) {
                item.push_back(source[position++].substr(2));   // 去掉开头的两个空格
            }
            painter.write_text(join_lines(item), 3, 3);
        }
    }
    cout << painter.row_count << '\n';

    return 0;
}