/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-09 22:30
 * update_at: 2026-10-10 00:05
 */
// main.cpp：时间。
//   比赛时长固定 3 小时 30 分 = 210 分钟。把开始时刻换算成「距当天 00:00 的分钟数」，
//   加上 210 分钟后对一天的总分钟数 1440 取模（跨日回卷），再换算回 hh:mm 并补前导零。
//   ★ 冒号兼容：题面 PDF 的样例里冒号是全角「：」(U+FF1A，advance 1.0 em)，
//     而官方参考实现 std.cpp 用的是半角 ':'（scanf("%d:%d")）。此处不区分冒号形式 ——
//     只认数字字符，分隔符一律跳过，故两种冒号下都与 std.cpp 语义一致。
#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

typedef long long ll;

const ll MATCH_MINUTES = 3 * 60 + 30;   // 比赛时长 210 分钟
const ll DAY_MINUTES = 24 * 60;         // 一天的总分钟数 1440

// 从一行里取出小时和分钟：连续的数字段就是这两个数，中间的分隔符直接跳过。
// 结果通过引用带出，避免为一对返回值引入额外的结构。
void read_time(ll &hour, ll &minute) {
    string line;
    getline(cin, line);
    bool in_hour = true;     // 当前数字归小时（false 表示归分钟）
    bool seen_digit = false; // 本段是否已读到数字，用来判断「分隔符是否已出现」
    for (ll i = 0, len = line.size(); i < len; i++) {
        char ch = line[i];
        if ('0' <= ch && ch <= '9') {
            if (in_hour) hour = hour * 10 + (ch - '0');
            else         minute = minute * 10 + (ch - '0');
            seen_digit = true;
        } else if (seen_digit && in_hour) {
            in_hour = false;    // 小时那段读完 ⇒ 后面的数字都归分钟
            seen_digit = false;
        }
    }
}

void solve() {
    ll hour = 0, minute = 0;
    read_time(hour, minute);
    ll total = (hour * 60 + minute + MATCH_MINUTES) % DAY_MINUTES;  // 跨日对 1440 取模
    cout << setfill('0') << setw(2) << total / 60 << ":"
         << setfill('0') << setw(2) << total % 60 << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    solve();
    return 0;
}
