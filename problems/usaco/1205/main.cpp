/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-07-11 17:46
 * update_at: 2026-07-11 17:47
 */
#include <bits/stdc++.h>
using namespace std;

string block_letters[4];
set<string> can_make_words;

void dfs_build(int used_mask, string word) {
    if (!word.empty()) {
        can_make_words.insert(word);
    }
    if ((int)word.size() == 4) {
        return;
    }

    for (int i = 0; i < 4; i++) {
        if ((used_mask & (1 << i)) != 0) {
            continue;
        }
        for (int j = 0; j < 6; j++) {
            dfs_build(used_mask | (1 << i), word + block_letters[i][j]);
        }
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;

    for (int i = 0; i < 4; i++) {
        cin >> block_letters[i];
    }

    dfs_build(0, "");

    for (int i = 1; i <= n; i++) {
        string word;
        cin >> word;
        if (can_make_words.find(word) != can_make_words.end()) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
    }

    return 0;
}
