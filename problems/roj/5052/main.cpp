/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 00:01
 * update_at: 2026-10-09 00:09
 */
// main.cpp：字串包含 —— 长者作母串，倍增后查找短串。
//
// 一次循环移位 = 把首字符移到末尾。字符串 X 的任一循环移位长度恒为 |X|，
// 所以 |Y| > |X| 时 Y 绝不可能是 X 某个循环移位的子串；此时只可能是
// 「短的 X 是长的 Y 移位后的子串」。于是先令 s1 = 长者(母串)、s2 = 短者(子串候选)，
// 问题化为「s2 是否为 s1 某个循环移位的子串」。
//
// 而 s1 的所有循环移位串拼起来就是 s1+s1 的前 |s1|+|s1| 个字符，故
// |s2| <= |s1| 时「s2 是某个循环移位的子串」等价于「s2 是 s1+s1 的子串」。
//
// 注意不能省掉这个长度守卫、改判 (s1 ⊂ s2+s2) || (s2 ⊂ s1+s1)：
// 当 |s1| < |s2| 时 s2+s2 会引入跨越周期的、比 |s2| 更长的非法子串，
// 例如 s1="aba"、s2="baab" 时 "aba" ⊂ "baab"+"baab" 成立，
// 但 |aba| > |baab| 中任何一个长度为 3 的移位串，正确答案是 false（见 problem4）。

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

typedef long long ll;

// 判定「s1 经过若干次循环移位后，是否包含 s2」；调用前不要求 |s1| >= |s2|。
bool contains_after_shift(string s1, string s2) {
    if (s1.length() < s2.length()) {
        swap(s1, s2);   // 长度守卫：长者作母串，短者作子串候选
    }
    string doubled = s1 + s1;   // 环形展开，一次枚举 s1 的全部循环移位
    return doubled.find(s2) != string::npos;
}

void solve() {
    string s1, s2;
    if (!(cin >> s1 >> s2)) return;   // 无输入或缺参数：安静退出
    if (contains_after_shift(s1, s2)) {
        cout << "true\n";
    } else {
        cout << "false\n";
    }
}

int main() {
    solve();
    return 0;
}
