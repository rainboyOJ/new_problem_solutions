/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:46
 * update_at: 2026-07-11 17:47
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

string block_letters[4];
string target_word;
bool used_block[4];

bool block_has_char(int block_id, char c) {
    for (int i = 0; i < 6; i++) {
        if (block_letters[block_id][i] == c) {
            return true;
        }
    }
    return false;
}

// 第 pos 层为单词第 pos 个字母选择一块尚未使用的积木。
bool dfs_match(int pos) {
    if (pos == (int)target_word.size()) {
        return true;
    }

    for (int i = 0; i < 4; i++) {
        if (used_block[i]) {
            continue;
        }
        if (!block_has_char(i, target_word[pos])) {
            continue;
        }

        used_block[i] = true;
        if (dfs_match(pos + 1)) {
            return true;
        }
        used_block[i] = false;
    }

    return false;
}

bool can_spell(string word) {
    target_word = word;
    for (int i = 0; i < 4; i++) {
        used_block[i] = false;
    }
    return dfs_match(0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < 4; i++) {
        cin >> block_letters[i];
    }

    for (int i = 1; i <= n; i++) {
        string word;
        cin >> word;
        if (can_spell(word)) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
