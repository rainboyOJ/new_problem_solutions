/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-08-11 07:37
 * update_at: 2026-08-11 11:03
 */
#include <bits/stdc++.h>
using namespace std;

int n;
long long s, now_value;

bool has_substr(const string &word, const string &pat) {
    return word.find(pat) != string::npos;
}

bool has_substr2(const string &word, const string &pat) {
    if (pat.size() > word.size()) return false;

    // 手动枚举起点，再逐字符比较，等价于判断 pat 是否为 word 的连续子串。
    for (int i = 0; i + (int)pat.size() <= (int)word.size(); i++) {
        bool same = true;
        for (int j = 0; j < (int)pat.size(); j++) {
            if (word[i + j] != pat[j]) {
                same = false;
                break;
            }
        }
        if (same) return true;
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> s;
    now_value = s;
    for (int i = 1; i <= n; i++) {
        string word;
        cin >> word;

        // 题面规则有优先级：kirai 最高，daishuki 高于 shuki。
        if (has_substr2(word, "kirai")) {
            if (now_value >= 0) now_value = 0;
        }
        else if (has_substr2(word, "daishuki")) {
            now_value += 2;
        }
        else if (has_substr2(word, "shuki")) {
            now_value += 1;
        }
        else {
            now_value -= 1;
        }
    }

    if (now_value > 0) cout << now_value - s << '\n';
    else cout << "shuki\n";
    return 0;
}
