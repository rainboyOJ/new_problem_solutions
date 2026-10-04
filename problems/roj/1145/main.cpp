/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 03:27
 * update_at: 2026-10-05 03:27
 */

#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

string s; // 输入的数字字符串
string ans; // p 型编码结果

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    cin >> s;

    ll n = s.size(); // 字符串长度
    ll i = 0; // 当前段的起点
    while (i < n) {
        ll j = i;
        // 向右扩展，直到字符不同或到达末尾
        while (j < n && s[j] == s[i]) {
            j++;
        }
        ll len = j - i; // 当前段长度
        // 输出段长和段字符
        ans += to_string(len);
        ans.push_back(s[i]);
        i = j; // 跳到下一个段的起点
    }

    cout << ans << '\n';
    return 0;
}
