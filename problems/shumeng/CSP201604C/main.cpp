/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 20:10
 */
#include <bits/stdc++.h>
using namespace std;

void append_path(vector<string> &parts, const string &path) {
    int start = 0;
    for (int i = 0; i <= (int)path.size(); i++) {
        if (i != (int)path.size() && path[i] != '/') continue;
        string part = path.substr(start, i - start);
        if (part == "..") {
            if (!parts.empty()) parts.pop_back();
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
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    vector<string> current_parts;
    append_path(current_parts, current_directory);
    while (p--) {
        string path;
        getline(cin, path);
        vector<string> parts;
        if (path.empty() || path[0] != '/') parts = current_parts;
        append_path(parts, path);
        if (parts.empty()) {
            cout << "/\n";
        } else {
            for (int i = 0; i < (int)parts.size(); i++) cout << '/' << parts[i];
            cout << '\n';
        }
    }
    return 0;
}
