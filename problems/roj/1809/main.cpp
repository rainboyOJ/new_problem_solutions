/**
 * 题目：日食（ROJ 1809）
 * 来源：信息学奥赛一本通 · 高手训练篇
 *
 * 题意：S1=A, S2=B, Si=(X*S(i-1)+Y*S(i-2)+Z) mod P (i>=3)，P 为质数且 P<=10007。
 *       Q 次询问 [L,R]，问 L..R 中有多少天满足 Si=C。
 *
 * 核心：模数 P 很小，状态二元组 (S(i-1),S(i)) 只有 P^2 种，序列必然循环。
 *       - Y != 0 时转移可逆（Y 在模 P 下有逆元），是双射，序列为"纯周期"：
 *         周期 K <= P^2，从第 1 项就开始循环，前缀尾巴长度 offset = 0。
 *       - Y == 0 时递推退化成一阶，状态只有单项，先走一段长度 <= P 的尾巴再进圈。
 *       对每组数据把一整圈枚举出来（记为"圈上第 r 位是否等于 C"），
 *       于是前 N 天中满足 Si=C 的天数 = (N-offset)/K * 圈内个数 + 圈上前 (N-offset)%K 位个数，
 *       询问即可 O(1)（实现上用一次离线扫描求所有需要的圈上前缀数）。
 *
 * 复杂度：时间 O(T*(P^2 + Q log Q))，空间 O(P^2/64 + Q)。
 */
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXP = 10007;                 /* P 的上限 */
const int MAXBITS = MAXP * MAXP + 128;  /* 周期上限 P^2，再留冗余 */

static unsigned long long bits[(MAXBITS >> 6) + 2]; /* 圈上标记位图，约 12.5 MB */

inline void bitSet(int i) { bits[i >> 6] |= 1ULL << (i & 63); }

/* ---------------- 快速读入 ---------------- */
static char ibuf[1 << 16];
static int ilen = 0, ipos = 0;
inline int gc() {
    if (ipos == ilen) {
        ilen = (int)fread(ibuf, 1, sizeof(ibuf), stdin);
        ipos = 0;
        if (ilen <= 0) return -1;
    }
    return ibuf[ipos++];
}
inline ll readInt() {
    int c = gc();
    while (c != -1 && (c < '0' || c > '9') && c != '-') c = gc();
    bool neg = false;
    if (c == '-') { neg = true; c = gc(); }
    ll x = 0;
    while (c >= '0' && c <= '9') { x = x * 10 + (c - '0'); c = gc(); }
    return neg ? -x : x;
}

int main() {
    int T = (int)readInt();
    string out;
    out.reserve(1 << 16);
    char tmp[24];

    for (int tc = 0; tc < T; tc++) {
        ll A = readInt(), B = readInt(), X = readInt(), Y = readInt();
        ll Z = readInt(), P = readInt(), C = readInt(), Q = readInt();
        vector<ll> ql(Q), qr(Q);
        for (int j = 0; j < Q; j++) { ql[j] = readInt(); qr[j] = readInt(); }

        if (Y == 0) {
            /* ---------- 一阶退化：S_i = (X*S_{i-1} + Z) mod P ---------- */
            vector<int> firstOcc((size_t)P, -1);   /* 每个取值首次出现的位置 */
            vector<int> seq;                       /* 第 1..offset+K 项 */
            seq.reserve((size_t)P + 2);
            seq.push_back((int)A);                 /* 第 1 项 */
            ll i = 2, offset = 0, K = 1;
            int cur = (int)B;
            while (true) {
                if (firstOcc[cur] != -1) {
                    offset = firstOcc[cur] - 1;    /* 尾巴长度（含第 1 项） */
                    K = i - firstOcc[cur];         /* 圈长 */
                    break;
                }
                firstOcc[cur] = (int)i;
                seq.push_back(cur);
                cur = (int)(((ll)X * cur + Z) % P);
                i++;
            }
            /* 前缀和：pref[t] = 前 t 项中等于 C 的个数 */
            int tot = (int)(offset + K);
            vector<int> pref((size_t)tot + 1, 0);
            for (int t = 1; t <= tot; t++) pref[t] = pref[t - 1] + (seq[t - 1] == C ? 1 : 0);
            ll cntPeriod = pref[tot] - pref[(size_t)offset];
            auto countUpTo = [&](ll N) -> ll {
                if (N <= 0) return 0;
                if (N <= (ll)tot) return pref[(size_t)N];
                ll rem = N - offset;
                ll cycles = rem / K, left = rem % K;
                return (ll)pref[(size_t)offset] + cycles * cntPeriod
                     + (pref[(size_t)(offset + left)] - pref[(size_t)offset]);
            };
            for (int j = 0; j < Q; j++) {
                ll ans = countUpTo(qr[j]) - countUpTo(ql[j] - 1);
                int len = snprintf(tmp, sizeof(tmp), "%lld\n", ans);
                out.append(tmp, len);
            }
        } else {
            /* ---------- 二阶可逆：纯周期，从第 1 项起循环 ---------- */
            int prev = (int)A, cur = (int)B;
            if (A == C) bitSet(0);      /* 第 1 项 */
            if (B == C) bitSet(1);      /* 第 2 项 */
            ll K = 1, i = 3;
            while (true) {
                int nxt = (int)(((ll)X * cur + (ll)Y * prev + Z) % P);
                if (cur == (int)A && nxt == (int)B) { K = i - 2; break; }
                if (nxt == C) bitSet((int)(i - 1));
                prev = cur; cur = nxt;
                i++;
            }
            /* 统计圈上前 K 位（位下标 0..K-1）里等于 C 的个数 */
            ll cnt = 0, fullWords = K >> 6;
            for (ll w = 0; w < fullWords; w++) cnt += __builtin_popcountll(bits[w]);
            int restBits = (int)(K & 63);
            if (restBits) cnt += __builtin_popcountll(bits[fullWords] & ((1ULL << restBits) - 1));

            /* 离线：收集所有需要的圈上前缀长度 m = N%K */
            vector<ll> need;
            need.reserve(2 * (size_t)Q);
            for (int j = 0; j < Q; j++) {
                need.push_back(qr[j] % K);
                need.push_back((ql[j] - 1) % K);
            }
            sort(need.begin(), need.end());
            need.erase(unique(need.begin(), need.end()), need.end());
            /* 升序扫描位图，得到每个 m 对应的"圈上前 m 位中等于 C 的个数" */
            vector<ll> tblVals(need.size());
            ll w = 0, acc = 0;
            for (size_t t = 0; t < need.size(); t++) {
                ll target = need[t];
                while ((w + 1) * 64 <= target) { acc += __builtin_popcountll(bits[w]); w++; }
                ll part = acc, rem = target - w * 64;
                if (rem > 0) part += __builtin_popcountll(bits[w] & ((1ULL << rem) - 1));
                tblVals[t] = part;
            }
            /* 查询圈上前 m 位的个数：在 need 里定位 m 的下标 */
            auto queryCyc = [&](ll m) -> ll {
                size_t pos = (size_t)(lower_bound(need.begin(), need.end(), m) - need.begin());
                return tblVals[pos];
            };
            for (int j = 0; j < Q; j++) {
                ll cntR = (qr[j] / K) * cnt + queryCyc(qr[j] % K);
                ll cntL = ((ql[j] - 1) / K) * cnt + queryCyc((ql[j] - 1) % K);
                ll ans = cntR - cntL;
                int len = snprintf(tmp, sizeof(tmp), "%lld\n", ans);
                out.append(tmp, len);
            }
            /* 清空本次用到的位图，供下一组数据使用 */
            ll used = (K >> 6) + 1;
            for (ll w2 = 0; w2 < used; w2++) bits[w2] = 0;
        }
    }
    fwrite(out.data(), 1, out.size(), stdout);
    return 0;
}
