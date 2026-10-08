/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-08 23:30
 * update_at: 2026-10-08 23:30
 */
#include <iostream>
#include <string>

using namespace std;

typedef long long ll;

string s; // 整行输入（含结尾的终止符 '.'）

void solve() {
    // 题面说「一行字符串」，用 getline 读整行，避免 cin >> s 在空格处截断
    if (!getline(cin, s)) {
        return; // 空输入：无数据可判，静默退出
    }

    // 先剥行尾的 '\r'（CRLF 容错）与 '\n'，再剥终止符 '.'
    while (!s.empty() && (s.back() == '\r' || s.back() == '\n')) {
        s.pop_back();
    }

    // '.' 是行尾终止符，不参与回文判断；数据末尾可能没有 '.'（如样例 abccb），故需判断
    if (!s.empty() && s.back() == '.') {
        s.pop_back();
    }

    // 双指针：左指针从左端、右指针从右端相向比较，任一对不同即非回文
    // 注意判断区分大小写（'a' 与 'A' 视为不同字符）
    ll len = s.size();
    ll left = 0;
    ll right = len - 1;
    bool is_palindrome = true;
    while (left < right) {
        if (s[left] != s[right]) {
            is_palindrome = false;
            break;
        }
        left++;
        right--;
    }

    cout << (is_palindrome ? "Yes" : "No") << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    solve();

    return 0;
}
