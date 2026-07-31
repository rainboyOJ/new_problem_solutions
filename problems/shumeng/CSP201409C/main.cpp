/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-31 16:21
 * update_at: 2026-07-31 18:30
 */
#include <bits/stdc++.h>
using namespace std;

string lower_copy(string text) {
    for (int i = 0; i < (int)text.size(); i++) {
        if ('A' <= text[i] && text[i] <= 'Z') {
            text[i] = char(text[i] - 'A' + 'a');
        }
    }
    return text;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string pattern;
    int sensitive;
    int n;
    cin >> pattern >> sensitive >> n;

    if (!sensitive) {
        pattern = lower_copy(pattern);
    }

    for (int i = 0; i < n; i++) {
        string text;
        cin >> text;
        string target = sensitive ? text : lower_copy(text);
        if (target.find(pattern) != string::npos) {
            cout << text << '\n';
        }
    }

    return 0;
}
