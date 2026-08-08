#include <bits/stdc++.h>
using namespace std;

string target_word;
string article;

char to_lower_char(char ch) {
    if (ch >= 'A' && ch <= 'Z') {
        return char(ch - 'A' + 'a');
    }
    return ch;
}

bool same_word(int left, int right) {
    int len = right - left + 1;
    if (len != (int) target_word.size()) {
        return false;
    }

    for (int i = 0; i < len; i++) {
        if (to_lower_char(article[left + i]) != target_word[i]) {
            return false;
        }
    }
    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, target_word);
    getline(cin, article);

    for (int i = 0; i < (int) target_word.size(); i++) {
        target_word[i] = to_lower_char(target_word[i]);
    }

    int count_match = 0;
    int first_pos = -1;
    int n = (int) article.size();
    int i = 0;

    while (i < n) {
        while (i < n && article[i] == ' ') {
            i++;
        }
        if (i >= n) {
            break;
        }

        int left = i;
        while (i < n && article[i] != ' ') {
            i++;
        }
        int right = i - 1;

        if (same_word(left, right)) {
            count_match++;
            if (first_pos == -1) {
                first_pos = left;
            }
        }
    }

    if (count_match == 0) {
        cout << -1 << '\n';
    }
    else {
        cout << count_match << ' ' << first_pos << '\n';
    }

    return 0;
}
