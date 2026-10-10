/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:18
 * update_at: 2026-10-07 15:33
 */
// main.cpp：把含 '?' 的模式串补成字典序最小的合法整数序列（',' 的 ASCII 小于所有数字）。
// 做法是"逐位贪心 + 可达性判定"：每位 '?' 依次试 ',' 与 '0'..'9'，取第一个还能补全的字符；
// 判定用一趟按"上一个逗号位置"的状态 DP 完成，每个位置只留"左侧最后一个数最小"的那条路径。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXLEN = 55;                  // 串长上界 50，留一点余量

// 贪心时每个 '?' 的尝试顺序：','（ASCII 44）小于所有数字（ASCII 48~57）
const string TRY_ORDER = ",0123456789";

// 逗号位置 c 上的状态：逗号落在位置 c 时，它左侧最后一个数的最小可能取值是多少。
// c = -1 是虚拟起点（还没有任何数字），value 为空串表示"无下界"。
struct State {
    bool reach;   // 这个逗号位置是否可达
    string value; // 可达时，左侧最后一个数的最小取值
};
State state[MAXLEN + 2];

string pat; // 当前模式串，'?' 表示这一位还没定
string ans; // 本组数据的答案
ll n;       // 模式串长度

// 比较两个无前导 0 的十进制数字串：先比位数，再比字典序。
ll cmpNumber(const string &a, const string &b) {
    if (a.size() != b.size()) return a.size() < b.size() ? -1 : 1;
    if (a == b) return 0;
    return a < b ? -1 : 1;
}

// 在 pat[start, stop) 上填出一个数字（首位非 0）并让它尽可能小；
// lower 为空串表示没有下界，否则要求数值严格大于 lower。填不出数字时返回空串。
string minNumber(ll start, ll stop, const string &lower) {
    ll length = stop - start;
    if (length <= 0) return "";

    string base(length, '0'); // base：忽略下界时的最小匹配数字
    for (ll i = 0; i < length; i++) {
        char c = pat[start + i];
        if (c == '?') {
            base[i] = (i == 0) ? '1' : '0';
        } else if (c == ',') {
            return ""; // 这一段中间被固定逗号截断，放不下一个数字
        } else {
            if (i == 0 && c == '0') return ""; // 前导 0，非法
            base[i] = c;
        }
    }

    ll lowerLen = lower.size();  // size() 是 size_t，赋给 ll 即可，不需要强制转换
    if (lower.empty() || length > lowerLen) return base; // 位数更多必然更大
    if (length < lowerLen) return "";                    // 位数更少不可能更大
    if (cmpNumber(base, lower) > 0) return base;

    // 同位数且 base <= lower：枚举"第一个超过 lower 的位置 j"，前缀与 lower 相同、
    // 第 j 位放大、后面取最小。j 越靠右得到的数越小，所以从右往左找第一个可行位置。
    for (ll j = length - 1; j >= 0; j--) {
        bool prefixOk = true;
        for (ll i = 0; i < j; i++) {
            if (pat[start + i] != '?' && pat[start + i] != lower[i]) {
                prefixOk = false;
                break;
            }
        }
        if (!prefixOk) continue;

        ll pick = -1;
        for (ll d = (lower[j] - '0') + 1; d <= 9; d++) {
            if (j == 0 && d == 0) continue; // 首位不能是 0
            if (pat[start + j] != '?' && pat[start + j] - '0' != d) continue;
            pick = d;
            break;
        }
        if (pick < 0) continue;

        string t = lower.substr(0, j);
        t += "0123456789"[pick]; // 直接取数字字符，省掉整型到字符的转换
        for (ll i = j + 1; i < length; i++) t += (pat[start + i] == '?') ? '0' : pat[start + i];
        return t;
    }
    return "";
}

// 当前 pat（前缀已固定）还能不能补全成合法串。
// 按逗号位置从左往右推进：同一位置只保留"左侧最后一个数最小"的路径，
// 因为上界更小对后面只会更宽松，丢掉别的路径不会丢解。
bool feasible() {
    for (ll i = 0; i <= n + 1; i++) {
        state[i].reach = false;
        state[i].value.clear();
    }
    state[0].reach = true; // 虚拟逗号位置 -1：还没有数字，无下界

    for (ll c = -1; c < n; c++) {
        if (!state[c + 1].reach) continue;
        ll start = c + 1; // 当前这一段数字从 start 开始
        for (ll stop = start + 1; stop <= n; stop++) {
            if (stop < n && pat[stop] != '?' && pat[stop] != ',') continue; // 段后要能放逗号
            string value = minNumber(start, stop, state[c + 1].value);
            if (value.empty()) continue;
            if (stop == n) return true; // 最后一段也填出了数字，整体可行
            ll nxt = stop + 1;          // 新逗号落在位置 stop
            if (!state[nxt].reach || cmpNumber(value, state[nxt].value) < 0) {
                state[nxt].reach = true;
                state[nxt].value = value;
            }
        }
    }
    return false;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    ll T;
    if (!(cin >> T)) return 0;

    while (T--) {
        cin >> pat;
        n = pat.size();

        if (!feasible()) {
            cout << "impossible\n";
            continue;
        }

        ans = pat;
        ll orderLen = TRY_ORDER.size();
        for (ll i = 0; i < n; i++) {
            if (pat[i] != '?') continue; // 题目固定给出的字符必须原样保留
            for (ll k = 0; k < orderLen; k++) {
                pat[i] = TRY_ORDER[k];
                if (feasible()) {        // 这一位取 TRY_ORDER[k] 后仍能补全
                    ans[i] = TRY_ORDER[k];
                    break;               // 留下这个字符继续处理后面的 '?'
                }
                pat[i] = '?';
            }
        }
        cout << ans << "\n";
    }
    return 0;
}
