/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 13:40
 * update_at: 2026-07-11 13:44
 */
#include <bits/stdc++.h>
using namespace std;

int pos[26]; // pos[c] 表示字母 c 在牛文字母表中的位置。

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    string alphabet, heard;
    cin >> alphabet >> heard;

    for (int i = 0; i < 26; i++) {
        pos[alphabet[i] - 'a'] = i;
    }

    int answer = 1;
    for (int i = 1; i < (int)heard.size(); i++) {
        int last_pos = pos[heard[i - 1] - 'a'];
        int now_pos = pos[heard[i] - 'a'];

        // 当前字母没有出现在上一字母之后，必须开始下一遍字母歌。
        if (now_pos <= last_pos) {
            answer++;
        }
    }

    cout << answer << '\n';

    return 0;
}
