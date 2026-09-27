/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-09-27 15:59
 * update_at: 2026-09-27 15:59
 */
// main2.cpp：O(C*L) 双重循环贪心，和 main.cpp 的优先队列做法形成对照。
// 思路：奶牛按 maxSPF 从小到大处理，每头牛在所有还有货的防晒霜里取 SPF 最小的那瓶。
// 为什么这样贪心安全：maxSPF 小的牛可选范围最窄，先满足它；而给它最小的可行 SPF，
// 等于把更大的 SPF 让给上限更大的牛，不会让答案变差。

#include <bits/stdc++.h>
using namespace std;

const int MAXN = 2505;

int C, L;

struct Cow {
    int min_spf;
    int max_spf;
};

struct Lotion {
    int spf;
    int cover;
};

Cow cows[MAXN];       // 奶牛的 minSPF / maxSPF
Lotion lotions[MAXN]; // 防晒霜的 SPF 和剩余瓶数

// 奶牛按 maxSPF 升序，maxSPF 相同时按 minSPF 升序，保证处理顺序确定。
bool cmp_cow(const Cow &a, const Cow &b) {
    if (a.max_spf != b.max_spf) {
        return a.max_spf < b.max_spf;
    }
    return a.min_spf < b.min_spf;
}

// 防晒霜按 SPF 升序，方便从前往后找第一瓶可用的（即 SPF 最小的可用瓶）。
bool cmp_lotion(const Lotion &a, const Lotion &b) {
    return a.spf < b.spf;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> C >> L;
    for (int i = 1; i <= C; i++) {
        cin >> cows[i].min_spf >> cows[i].max_spf;
    }
    for (int i = 1; i <= L; i++) {
        cin >> lotions[i].spf >> lotions[i].cover;
    }

    sort(cows + 1, cows + C + 1, cmp_cow);
    sort(lotions + 1, lotions + L + 1, cmp_lotion);

    int ans = 0;
    for (int i = 1; i <= C; i++) {
        int lo = cows[i].min_spf;
        int hi = cows[i].max_spf;
        // 找 SPF 最小的可用防晒霜：它最难被别的牛用掉，优先分给当前上限最小的牛。
        for (int j = 1; j <= L; j++) {
            if (lotions[j].cover > 0 && lo <= lotions[j].spf && lotions[j].spf <= hi) {
                lotions[j].cover--;
                ans++;
                break;
            }
        }
    }

    cout << ans << '\n';
    return 0;
}
