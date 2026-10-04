/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:11
 * update_at: 2026-10-05 04:11
 */

#include <iostream>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;

string a, b; // 两个大整数串

// 竖式减法：从最低位起逐位相减，不够减就向高位借 1，结果长度取 max(len(a), len(b))
string subtract(const string &top, const string &bottom) {
    string out;
    ll borrow = 0;                       // 借位只可能是 0 或 1
    ll la = top.size(), lb = bottom.size();
    ll L = max(la, lb);
    for (ll i = 0; i < L; i++) {
        ll high = (i < la) ? top[la - 1 - i] - '0' : 0;     // 越界位按 0 算，省掉补零
        ll low  = (i < lb) ? bottom[lb - 1 - i] - '0' : 0;
        ll diff = high - low - borrow;
        borrow = (diff < 0) ? 1 : 0;                          // 本位不够减，向高位借 1
        out.push_back(char((diff + 10) % 10 + '0'));          // 借位后的本位数字
    }
    reverse(out.begin(), out.end());
    return out;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> a >> b;
    // 与 std.cpp 的交换判定保持一致：位数短则交换；等长且两串不同时也交换
    bool swapped = (a.size() < b.size()) || (a.size() == b.size() && a != b);
    const string &top = swapped ? b : a;
    const string &bottom = swapped ? a : b;
    string res = subtract(top, bottom);
    // 去掉前导零，但至少要保留一个零
    ll pos = 0;
    while (pos + 1 < (ll)res.size() && res[pos] == '0') pos++;
    if (swapped) cout << '-';
    cout << res.substr(pos) << '\n';
    return 0;
}
