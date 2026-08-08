#include <bits/stdc++.h>
using namespace std;

struct Operation {
    int type;
    int rail;
    string key;
};

int n;
string s;
vector<Operation> ops;

char qwe_inv_upper[26];

void build_qwe_inverse() {
    string keyboard = "QWERTYUIOPASDFGHJKLZXCVBNM";
    for (int i = 0; i < 26; i++) {
        qwe_inv_upper[keyboard[i] - 'A'] = char('A' + i);
    }
}

int letter_value(char ch) {
    if ('A' <= ch && ch <= 'Z') {
        return ch - 'A';
    }
    if ('a' <= ch && ch <= 'z') {
        return ch - 'a';
    }
    return 0;
}

char decode_vigenere_char(char ch, int shift) {
    if ('A' <= ch && ch <= 'Z') {
        int x = ch - 'A';
        x = (x - shift + 26) % 26;
        return char('A' + x);
    }
    if ('a' <= ch && ch <= 'z') {
        int x = ch - 'a';
        x = (x - shift + 26) % 26;
        return char('a' + x);
    }
    return ch;
}

char decode_qwe_char(char ch) {
    if ('A' <= ch && ch <= 'Z') {
        return qwe_inv_upper[ch - 'A'];
    }
    if ('a' <= ch && ch <= 'z') {
        char up = char(ch - 'a' + 'A');
        char plain = qwe_inv_upper[up - 'A'];
        return char(plain - 'A' + 'a');
    }
    return ch;
}

string decode_vigenere(const string &cipher, const string &key) {
    string plain = cipher;
    int key_len = (int) key.size();
    for (int i = 0; i < (int) plain.size(); i++) {
        int shift = letter_value(key[i % key_len]);
        plain[i] = decode_vigenere_char(plain[i], shift);
    }
    return plain;
}

string decode_qwe(const string &cipher) {
    string plain = cipher;
    for (int i = 0; i < (int) plain.size(); i++) {
        plain[i] = decode_qwe_char(plain[i]);
    }
    return plain;
}

// brute.cpp：更直观的栅栏密码逆变换。
// 直接把每一列的字符回填到每一组对应的位置，再顺序读出所有分组。
string decode_rail_bruteforce(const string &cipher, int width) {
    int len = (int) cipher.size();
    int groups = (len + width - 1) / width;

    vector<int> row_len(groups, 0);
    for (int i = 0; i < groups; i++) {
        row_len[i] = min(width, len - i * width);
    }

    vector<string> rows(groups);
    for (int i = 0; i < groups; i++) {
        rows[i] = string(row_len[i], '?');
    }

    int pos = 0;
    for (int col = 0; col < width; col++) {
        for (int row = 0; row < groups; row++) {
            if (col < row_len[row]) {
                rows[row][col] = cipher[pos];
                pos++;
            }
        }
    }

    string plain;
    plain.reserve(len);
    for (int row = 0; row < groups; row++) {
        plain += rows[row];
    }
    return plain;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    build_qwe_inverse();

    cin >> n;
    cin >> s;

    ops.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> ops[i].type;
        ops[i].rail = 0;
        ops[i].key.clear();
        if (ops[i].type == 1) {
            cin >> ops[i].rail;
        } else if (ops[i].type == 2) {
            cin >> ops[i].key;
        }
    }

    for (int i = n - 1; i >= 0; i--) {
        if (ops[i].type == 1) {
            s = decode_rail_bruteforce(s, ops[i].rail);
        } else if (ops[i].type == 2) {
            s = decode_vigenere(s, ops[i].key);
        } else {
            s = decode_qwe(s);
        }
    }

    cout << s << '\n';
    return 0;
}
