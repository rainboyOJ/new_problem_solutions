// brute.cpp：直接按可见连续片段计数，用来帮助理解题意并辅助对拍。
#include <bits/stdc++.h>
using namespace std;

string s;

int count_boy_words() {
    int cnt = 0;
    for (int i = 0; i < (int) s.size(); i++) {
        if (s[i] != 'b' && s[i] != 'o' && s[i] != 'y') {
            continue;
        }

        if (i == 0) {
            cnt++;
        }
        else if (s[i] == 'b') {
            cnt++;
        }
        else if (s[i] == 'o' && s[i - 1] != 'b') {
            cnt++;
        }
        else if (s[i] == 'y' && s[i - 1] != 'o') {
            cnt++;
        }
    }
    return cnt;
}

int count_girl_words() {
    int cnt = 0;
    for (int i = 0; i < (int) s.size(); i++) {
        if (s[i] != 'g' && s[i] != 'i' && s[i] != 'r' && s[i] != 'l') {
            continue;
        }

        if (i == 0) {
            cnt++;
        }
        else if (s[i] == 'g') {
            cnt++;
        }
        else if (s[i] == 'i' && s[i - 1] != 'g') {
            cnt++;
        }
        else if (s[i] == 'r' && s[i - 1] != 'i') {
            cnt++;
        }
        else if (s[i] == 'l' && s[i - 1] != 'r') {
            cnt++;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> s;
    cout << count_boy_words() << '\n';
    cout << count_girl_words() << '\n';

    return 0;
}
