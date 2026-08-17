/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-08-17 22:48
 */
#include <bits/stdc++.h>
using namespace std;

// 把一段路径按 '/' 拆成目录组件，依次压入 parts 这个栈。
// '.' 与连续斜杠产生的空组件直接跳过；'..' 弹出栈顶一层（栈空时根目录的上一级还是根目录，不动）。
void append_path(vector<string> &parts, const string &path) {
    int start = 0;
    for (int i = 0; i <= (int)path.size(); i++) {
        if (i != (int)path.size() && path[i] != '/') {
            continue;
        }
        string part = path.substr(start, i - start);
        if (part == "..") {
            if (!parts.empty()) {
                parts.pop_back();
            }
        } else if (!part.empty() && part != ".") {
            parts.push_back(part);
        }
        start = i + 1;
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int p;
    cin >> p;
    string current_directory;
    cin >> current_directory;
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // 丢弃当前目录一行的换行符，避免影响 getline

    // 当前目录本身是正规化绝对路径，预先拆成组件供相对路径使用
    vector<string> current_parts;
    append_path(current_parts, current_directory);

    while (p--) {
        string path;
        getline(cin, path);
        vector<string> parts;
        // 相对路径以当前目录为起点，绝对路径以根目录（空栈）为起点
        if (path.empty() || path[0] != '/') {
            parts = current_parts;
        }
        append_path(parts, path);

        if (parts.empty()) {
            cout << "/\n"; // 空栈对应根目录
        } else {
            for (int i = 0; i < (int)parts.size(); i++) {
                cout << '/' << parts[i];
            }
            cout << '\n';
        }
    }
    return 0;
}