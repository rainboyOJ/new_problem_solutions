/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:59
 * update_at: 2026-10-05 02:59
 */
// main.cpp：判断字符串是否为合法的 C 标识符。
// 规则：保留字由题面保证不出现；
//       首字符必须是字母或下划线，其余每个字符必须是字母、数字或下划线。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

char s[32]; // 输入串长度 <= 20，留 32 足够

// 判断字符 ch 是否属于"字母/数字/下划线"。
int is_id_char(char ch) {
    return (ch >= 'a' && ch <= 'z')
        || (ch >= 'A' && ch <= 'Z')
        || (ch >= '0' && ch <= '9')
        || ch == '_';
}

// 判断字符 ch 是否属于"字母/下划线"（首字符允许集合）。
int is_id_head(char ch) {
    return (ch >= 'a' && ch <= 'z')
        || (ch >= 'A' && ch <= 'Z')
        || ch == '_';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // 一行字符串，不含空白，用 >> 自动跳过行首空白并读到下一个空白为止。
    if (!(cin >> s)) return 0;

    ll ok = 1;
    ll n = (ll)strlen(s);

    if (n == 0) ok = 0; // 空串直接判否
    else if (!is_id_head(s[0])) ok = 0; // 首字符必须是字母/下划线
    else {
        // 其余每一位都必须是字母/数字/下划线。
        for (ll i = 1; i < n; i++) {
            if (!is_id_char(s[i])) {
                ok = 0;
                break;
            }
        }
    }

    cout << (ok ? "yes" : "no") << "\n";
    return 0;
}