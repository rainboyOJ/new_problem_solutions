#include <bits/stdc++.h>
using namespace std;

struct Operation {
    int type;     // 1=栅栏密码，2=维吉尼亚密码，3=QWE 键盘码
    int rail;     // 栅栏密码分组长度
    string key;   // 维吉尼亚密码密钥
};

int n;
string s;
vector<Operation> ops;

char qwe_inv_upper[26];

// 建立 QWE 键盘码的逆映射：密文字母 -> 原文字母。
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

// 逆向还原维吉尼亚密码。
string decode_vigenere(const string &cipher, const string &key) {
    string plain = cipher;
    int key_len = (int) key.size();
    for (int i = 0; i < (int) plain.size(); i++) {
        int shift = letter_value(key[i % key_len]);
        plain[i] = decode_vigenere_char(plain[i], shift);
    }
    return plain;
}

// 逆向还原 QWE 键盘码。
string decode_qwe(const string &cipher) {
    string plain = cipher;
    for (int i = 0; i < (int) plain.size(); i++) {
        plain[i] = decode_qwe_char(plain[i]);
    }
    return plain;
}

// 栅栏密码逆变换：
// 已知加密结果是“按列依次取出”，这里按每一列的长度把字符串切开，再按行拼回去。
string decode_rail(const string &cipher, int width) {
    int len = (int) cipher.size();
    int groups = (len + width - 1) / width;
    int rem = len % width;

    vector<int> column_len(width, groups);
    if (rem != 0) {
        for (int col = rem; col < width; col++) {
            column_len[col]--;
        }
    }

    vector<int> start(width, 0);
    int pos = 0;
    for (int col = 0; col < width; col++) {
        start[col] = pos;
        pos += column_len[col];
    }

    string plain;
    plain.reserve(len);

    for (int row = 0; row < groups; row++) {
        for (int col = 0; col < width; col++) {
            if (row < column_len[col]) {
                plain.push_back(cipher[start[col] + row]);
            }
        }
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

    // 输入给出的是正向加密顺序，所以解密时要倒着撤销。
    for (int i = n - 1; i >= 0; i--) {
        if (ops[i].type == 1) {
            s = decode_rail(s, ops[i].rail);
        } else if (ops[i].type == 2) {
            s = decode_vigenere(s, ops[i].key);
        } else {
            s = decode_qwe(s);
        }
    }

    cout << s << '\n';
    return 0;
}
