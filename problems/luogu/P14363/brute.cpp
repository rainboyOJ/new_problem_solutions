/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-06-22 19:52
 * update_at: 2026-10-15 11:26
 */
// brute.cpp：小数据暴力解，用来帮助理解题意并辅助对拍。
// 枚举每条规则和每个起点，检查替换后是否等于目标串，只适合很小的数据。
//
// ==================== 教学导读 ====================
// 【题目在问什么】给定 n 条规则 (s1, s2)（等长），每次询问给两个不等的等长串
// t1、t2，问有多少种「方案」把 t1 变成 t2。一个方案 = (规则编号 id, 替换起点 start)，
// 即把 t1[start .. start+|s1|-1] 换成 s2。不同 id 或不同 start 都算不同方案。
//
// 【暴力思路】不放过任何可能性：双重循环枚举所有 (id, start) 对，对每一对
// 模拟这次替换，看结果是否恰好等于 t2。因为题目要求“恰好一次替换”，
// 所以 (id, start) 就是方案的完整描述，枚举它们就等于枚举了所有方案。
//
// 【为什么正确】can_replace_at 做了两件完整的事：
//   ① 确认 t1 的 [start, start+len) 真的等于规则左串（否则这次替换根本不合法）；
//   ② 把区间换成规则右串后，整个结果串逐位和 t2 比较。
// 只要有一对 (id, start) 通过检查，答案就 +1，不多不少。
//
// 【复杂度】O(q * n * m * len)，m 是询问串长。只够测试点 1、2 的小数据，
// 但它是最容易看懂的版本，也是后面所有优化的正确性参照（对拍用）。
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXN = 105; // 只服务测试点 1、2 的小数据

int n, q;
string left_part[MAXN];  // 规则 i 的替换前串 s1
string right_part[MAXN]; // 规则 i 的替换后串 s2

// 检查把 a 的 [start, start+len) 子串用规则 id 替换后是否恰好等于 b。
// 先验证被替换区间与规则左串逐位相同，再验证替换后的整串与 b 逐位相同。
// 返回 true 就代表 (id, start) 是一个合法方案。
bool can_replace_at(const string &a, const string &b, int id, int start) {
    int len = left_part[id].size();
    int alen = a.size();
    if (start + len > alen) {
        return false; // 替换区间越出串尾，不合法
    }

    // 被替换区间必须与规则的替换前串完全相同
    for (int i = 0; i < len; i++) {
        if (a[start + i] != left_part[id][i]) {
            return false;
        }
    }

    // 替换区间外保持原样，区间内换成替换后串，逐位和 b 比较
    for (int i = 0; i < alen; i++) {
        char after_char = a[i];
        if (start <= i && i < start + len) {
            after_char = right_part[id][i - start];
        }
        if (after_char != b[i]) {
            return false;
        }
    }

    return true;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> q;
    // 规则编号从 1 开始，和题面一致
    for (int i = 1; i <= n; i++) {
        cin >> left_part[i] >> right_part[i];
    }

    // 每个询问独立枚举「规则编号 + 替换起点」这一对，复杂度 O(q * n * len^2)。
    // 这一层枚举规则，里层枚举起点：两层合起来就是枚举所有可能的方案。
    while (q--) {
        string a, b;
        cin >> a >> b;

        ll ans = 0;
        // 替换不改变长度，长度不同必然无解
        if (a.size() == b.size()) {
            int alen = a.size();
            for (int id = 1; id <= n; id++) {
                int plen = left_part[id].size();
                for (int start = 0; start + plen <= alen; start++) {
                    if (can_replace_at(a, b, id, start)) {
                        ans++;
                    }
                }
            }
        }
        cout << ans << '\n';
    }

    return 0;
}
