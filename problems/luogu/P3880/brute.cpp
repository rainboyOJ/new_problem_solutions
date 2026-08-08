// brute.cpp：按题面三步规则逐步生成三个提示，作为教学版和对拍基准程序。
#include <bits/stdc++.h>
using namespace std;

string s;
string hint1, hint2, hint3;

bool is_letter(char ch) {
    return (ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z');
}

bool is_vowel(char ch) {
    return ch == 'a' || ch == 'e' || ch == 'i' || ch == 'o' || ch == 'u' ||
           ch == 'A' || ch == 'E' || ch == 'I' || ch == 'O' || ch == 'U';
}

int round_nearest(int x, int y) {
    return (x + y / 2) / y;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    getline(cin, s);

    hint1 = s;
    int letter_cnt = 0;
    for (int i = 0; i < (int) s.size(); i++) {
        if (is_letter(s[i])) {
            hint1[i] = '.';
            letter_cnt++;
        }
    }

    hint2 = hint1;
    int show_first = round_nearest(letter_cnt, 3);
    int passed_letters = 0;
    for (int i = 0; i < (int) s.size(); i++) {
        if (is_letter(s[i])) {
            passed_letters++;
            if (passed_letters <= show_first) {
                hint2[i] = s[i];
            }
        }
    }

    hint3 = hint2;
    bool has_hidden_vowel = false;
    passed_letters = 0;
    for (int i = 0; i < (int) s.size(); i++) {
        if (is_letter(s[i])) {
            passed_letters++;
            if (passed_letters > show_first && is_vowel(s[i])) {
                hint3[i] = s[i];
                has_hidden_vowel = true;
            }
        }
    }

    if (!has_hidden_vowel) {
        hint3 = hint1;
        int show_two_third = round_nearest(letter_cnt * 2, 3);
        passed_letters = 0;
        for (int i = 0; i < (int) s.size(); i++) {
            if (is_letter(s[i])) {
                passed_letters++;
                if (passed_letters <= show_two_third) {
                    hint3[i] = s[i];
                }
            }
        }
    }

    cout << hint1 << '\n';
    cout << hint2 << '\n';
    cout << hint3 << '\n';
    return 0;
}
