/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 14:14
 * update_at: 2026-10-06 14:14
 */
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

string cipher_text; // 第 1 行：已掌握的加密信息
string plain_text;  // 第 2 行：加密信息对应的原信息
string telegram;    // 第 3 行：待破译的电报

int to_cipher[26]; // to_cipher[x] 表示原字母 x 的密字，-1 表示还没确定
int to_plain[26];  // to_plain[y] 表示密字 y 对应的原字母，破译时使用

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> cipher_text >> plain_text >> telegram;

    for (int i = 0; i < 26; i++) {
        to_cipher[i] = -1;
        to_plain[i] = -1;
    }

    ll len = plain_text.size();
    for (ll i = 0; i < len; i++) {
        int x = plain_text[i] - 'A';   // 原字母
        int y = cipher_text[i] - 'A';  // 对应的密字

        // 同一个原字母给出了两个不同密字，规则自相矛盾
        if (to_cipher[x] != -1 && to_cipher[x] != y) {
            cout << "Failed" << '\n';
            return 0;
        }
        // 两个不同原字母共用了同一个密字
        if (to_plain[y] != -1 && to_plain[y] != x) {
            cout << "Failed" << '\n';
            return 0;
        }

        to_cipher[x] = y;
        to_plain[y] = x;
    }

    // 26 个字母必须全部出现，密码表才是 26 个字母上的双射
    for (int i = 0; i < 26; i++) {
        if (to_cipher[i] == -1) {
            cout << "Failed" << '\n';
            return 0;
        }
    }

    // 双射成立时逆表对所有密字都有定义，逐字符翻译电报
    ll m = telegram.size();
    for (ll i = 0; i < m; i++) {
        int y = telegram[i] - 'A';
        char original = 'A' + to_plain[y]; // 由逆表得到原字母
        cout << original;
    }
    cout << '\n';

    return 0;
}
