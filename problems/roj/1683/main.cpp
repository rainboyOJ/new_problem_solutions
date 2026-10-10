/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-07 15:17
 * update_at: 2026-10-07 15:17
 */
// main.cpp：稗田阿求。
// 每一组"文字段 + 数列"给出一个 字母->数字 的部分单射（题面保证组内合法），
// 两组能同时成立就连一条边，答案就是这张相容图上的最大团。
// M <= 40，用 64 位掩码表示"还能选哪些组"，再做分支限界 DFS。与 main.py 同一算法。

#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAXM = 45;   // 组数上限 40，留一点余量
const int ALPHA = 26;  // 字母表大小，A..Z

// 一组数据：既存它给出的部分单射，也存它在相容图上的邻接掩码
struct Group {
    ll value[ALPHA];           // value[c]：本组里字母 c 对应的数字，0 表示该字母没出现
    unsigned long long compat; // 第 j 位为 1 <=> 本组与第 j 组能同时成立（不含自己）
};

ll n, m;             // n：数字与字母的个数（只限定值域，算法本身不需要）；m：组的个数
Group group[MAXM];   // group[i] 就是第 i 组，下标从 1 开始和题面一致
ll best_answer;      // 目前搜到的最大团大小

// 两组能否同时成立：公共字母必须对应同一个数字，且合并后不同字母不共用数字。
bool compatible(ll a, ll b) {
    bool used_number[ALPHA + 1] = {false}; // used_number[v]：数字 v 已被合并后的某个字母占用
    for (int c = 0; c < ALPHA; c++) {
        ll va = group[a].value[c];
        ll vb = group[b].value[c];
        if (va != 0 && vb != 0 && va != vb) return false; // 同一个字母被赋了两个数字
        ll v = va != 0 ? va : vb;
        if (v == 0) continue;              // 两组都没出现这个字母
        if (used_number[v]) return false;  // 两个不同字母挤到了同一个数字上
        used_number[v] = true;
    }
    return true;
}

// 分支限界求最大团：决定第 idx 组选不选，cnt 是已经选了几组，
// candidates 中为 1 的位是"与已选集合全部相容、还能继续选"的那些组。
void dfs(ll idx, ll cnt, unsigned long long candidates) {
    if (cnt + (m - idx + 1) <= best_answer) return; // 剩下的组全选也追不平，直接剪掉
    if (idx > m) {
        best_answer = max(best_answer, cnt);
        return;
    }
    if ((candidates >> (idx - 1)) & 1ULL) {
        dfs(idx + 1, cnt + 1, candidates & group[idx].compat); // 选第 idx 组，候选集同步收窄
    }
    dfs(idx + 1, cnt, candidates); // 不选第 idx 组
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> m;
    for (int i = 1; i <= m; i++) {
        string word;
        cin >> word;              // 第 i 组的文字段
        ll length = word.size();  // 数列长度，题面保证等于文字段的字符数
        for (ll j = 0; j < length; j++) {
            ll value;
            cin >> value;
            group[i].value[word[j] - 'A'] = value; // 组内合法，同一字母重复出现时数字相同
        }
    }

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= m; j++) {
            if (i != j && compatible(i, j)) group[i].compat |= 1ULL << (j - 1);
        }
    }

    dfs(1, 0, ~0ULL); // 一开始所有组都在候选集里
    cout << best_answer << "\n";

    return 0;
}
