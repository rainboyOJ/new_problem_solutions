/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:42
 * update_at: 2026-10-07 15:42
 */
// ROJ 1692 字符串编码
// 题意：选若干对互不相交的小写字母对（每个字母至多出现在一对里），把串中选中字母换成
// 它的配对字母，未选中的字母保持不变——这正好是一个"对合"映射 f（f(f(a)) = a）。
// 求 S 有多少个子串能编码成 T，按升序输出起点（1 起）。
//
// 子串 U 能编码成 T 当且仅当下面两条同时成立：
//   (A) 模式同构：存在字母间的双射 g 使 g(U[j]) = T[j]。等价于 U 与 T 的 prev 编码逐位相等
//       （prev 编码：某位字符与它上一次出现的距离，首次出现记 0）。
//   (B) 对合律：若字母 a 出现在 U 中、g(a) = b 且 b 也出现在 U 中，则必须 g(b) = a。
//       若 b 不出现在 U 中，直接把 a 与 b 配成一对即可，没有额外约束。
// 判定 (A) 用"比较规则换成 prev 编码"的 KMP；判定 (B) 逐字母 O(26) 检查。
#include <cstdio>
#include <vector>
using namespace std;

typedef long long ll;

const int MAXN = 200005;

ll n, m;
char S[MAXN], T[MAXN]; // 1-based，S 是文本串，T 是模式串
ll pvS[MAXN];          // pvS[i] = S[i] 与它上一次出现的距离，首次出现记 0
ll pvT[MAXN];          // pvT[j] 同理，对应 T
ll failArr[MAXN];      // failArr[j] = 模式串前 j 位的"模式同构"最长 border 长度

// 一个字母在 S 中的出现位置，以及一个随窗口左端单调右移的扫描指针
struct LetterPos {
    vector<ll> positions; // 升序的出现位置
    ll cursor;            // positions[cursor] 是该字母在"当前窗口左端及之后"的首次出现
};
LetterPos letterPos[26];

int tLetter[26];   // T 中出现的所有字母（去重，按字母序）
ll tLetterCnt;
ll firstOccT[26];  // T 中每个字母首次出现的位置（1-based），0 表示 T 中不出现

ll ans[MAXN];      // 所有合法子串的起点（升序）
ll ansCnt;

// 模式串第 k+1 位能否与"窗口内相对下标 k+1"的文本位对齐。
// 文本位原始 prev 值为 textPrev：它上一次出现若还在窗口内（textPrev <= k），
// 编码就是 textPrev；否则说明上一次出现在窗口之外，该位在窗口内是首次出现，编码为 0。
bool canAlign(ll patVal, ll textPrev, ll k) {
    ll windowCode = textPrev <= k ? textPrev : 0;
    return patVal == windowCode;
}

// 判定窗口 [p, p+m-1] 是否满足对合律。
// 模式同构把"窗口字母 -> T 字母"的双射 g 定死了：若字母 b 在 T 中首次出现在第 q 位，
// 则 g(S[p+q-1]) = b（因为 T 第 q 位就是 b）。于是对合律要求：当 b 也出现在窗口内时，
// 窗口内 b 的首次出现位置 jb 必须满足 g(b) = T[jb] 等于 S[p+q-1]。
bool checkInvolve(ll p) {
    ll right = p + m - 1;
    for (ll idx = 0; idx < tLetterCnt; idx++) {
        ll b = tLetter[idx];
        vector<ll>& positions = letterPos[b].positions;
        ll& cursor = letterPos[b].cursor;
        ll cnt = positions.size(); // 出现位置表长度；用 ll 与游标同类型，避免有符号/无符号混比
        // 窗口左端单调右移，cursor 只增不减，每个位置最多被跳过一次，均摊 O(n)
        while (cursor < cnt && positions[cursor] < p) cursor++;
        if (cursor < cnt && positions[cursor] <= right) {
            ll jb = positions[cursor] - p + 1; // 字母 b 在窗口内首次出现的位置
            if (T[jb] - 'a' != S[p + firstOccT[b] - 1] - 'a') return false;
        }
    }
    return true;
}

int main() {
    scanf("%lld %lld", &n, &m);
    scanf("%s %s", S + 1, T + 1);

    // 建立两个串的 prev 编码，同时把 S 的每个字母的出现位置按字母分桶
    ll last[26];
    for (int c = 0; c < 26; c++) {
        last[c] = 0;
        letterPos[c].cursor = 0;
    }
    for (ll i = 1; i <= n; i++) {
        int c = S[i] - 'a';
        pvS[i] = last[c] ? i - last[c] : 0;
        last[c] = i;
        letterPos[c].positions.push_back(i);
    }
    for (int c = 0; c < 26; c++) last[c] = 0;
    for (ll j = 1; j <= m; j++) {
        int c = T[j] - 'a';
        pvT[j] = last[c] ? j - last[c] : 0;
        last[c] = j;
    }
    // T 中出现的字母表与每个字母的首次出现位置（逆序赋值，留下的就是最小位置）
    for (int c = 0; c < 26; c++) firstOccT[c] = 0;
    for (ll j = m; j >= 1; j--) firstOccT[T[j] - 'a'] = j;
    tLetterCnt = 0;
    for (int c = 0; c < 26; c++)
        if (firstOccT[c]) tLetter[tLetterCnt++] = c;

    // 模式串的 KMP 失配表：比较规则换成 canAlign，因为这里判定的是"模式同构"
    failArr[1] = 0;
    ll k = 0;
    for (ll j = 2; j <= m; j++) {
        while (k > 0 && !canAlign(pvT[k + 1], pvT[j], k)) k = failArr[k];
        if (canAlign(pvT[k + 1], pvT[j], k)) k++;
        failArr[j] = k;
    }

    // 在 S 上跑 KMP：每匹配到一个长度 m 的窗口，再用对合律筛一次
    k = 0;
    for (ll i = 1; i <= n; i++) {
        while (k > 0 && !canAlign(pvT[k + 1], pvS[i], k)) k = failArr[k];
        if (canAlign(pvT[k + 1], pvS[i], k)) k++;
        if (k == m) {
            ll p = i - m + 1; // 窗口起点
            if (checkInvolve(p)) ans[++ansCnt] = p;
            k = failArr[m];
        }
    }

    printf("%lld\n", ansCnt);
    for (ll i = 1; i <= ansCnt; i++)
        printf("%lld%c", ans[i], i == ansCnt ? '\n' : ' ');
    return 0;
}
