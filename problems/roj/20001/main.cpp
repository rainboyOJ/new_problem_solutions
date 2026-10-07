/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 02:11
 * update_at: 2026-10-06 02:11
 */
#include <iostream>
#include <string>
#include <algorithm>
typedef long long ll;
using namespace std;

string s; // 输入的数字串，最长 250 位，装不进整数，按字符串处理

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    cin >> s;
    // 先把整个串反转：数位倒序不产生进位借位，只需换位置
    reverse(s.begin(), s.end());
    // 反转后开头的 0 就是原串末尾的 0，全部删掉；中间和末尾的 0 保留
    ll pos = 0;
    while (pos + 1 < (ll)s.size() && s[pos] == '0') pos++; // 至少留一位，全 0 时输出 0
    cout << s.substr(pos) << "\n";
    return 0;
}
