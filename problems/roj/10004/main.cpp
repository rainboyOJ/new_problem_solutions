/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 21:37
 * update_at: 2026-10-04 21:37
 */
// main.cpp：按三条规则判定每名面试者的四轮评分结果。
#include <iostream>
#include <string>
using namespace std;

typedef long long ll;

ll T;
string score; // 当前面试者长度为 4 的评分串

// 判定一个人的结果：先判淘汰（有 D 或 C 至少两次），再判无 D 且 A 至少三个。
string judge(const string &s) {
    ll cnt_c = 0;             // C 的个数，用于淘汰判断
    ll cnt_a = 0;             // A 的个数，用于判断 special offer
    bool has_d = false;       // 四轮中是否出现过 D
    ll len = s.size();
    for (ll i = 0; i < len; i++) {
        if (s[i] == 'D') has_d = true;
        if (s[i] == 'C') cnt_c++;
        if (s[i] == 'A') cnt_a++;
    }

    if (has_d || cnt_c >= 2) return "failed";
    if (cnt_a >= 3) return "sp offer"; // 中间的空格是官方输出的一部分
    return "offer";
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> T;
    for (ll i = 1; i <= T; i++) {
        cin >> score;
        cout << judge(score) << '\n';
    }

    return 0;
}
