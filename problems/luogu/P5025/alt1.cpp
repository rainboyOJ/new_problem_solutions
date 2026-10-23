/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-23 16:31
 * update_at: 2026-10-23 16:53
 */
// alt1.cpp：不建图的双向扫描，O(n) 时间 / O(n) 空间。
//
// 主解用线段树优化建图 + Tarjan 缩点把「点向区间连边」压到 O(n log n)；
// 本解完全不走图论：直接利用「引爆集合必为连续下标区间」这一性质，
// 对每个炸弹维护它最终能引爆的区间端点，先做一遍只向左的闭包，再做一遍向右的吸收。
// 关键在于向左闭包时空闲出来的「右向射程」在第二趟依然有效（不是漏更新），
// 以及两趟的内层 while 总次数都不超过 n-1，因此整体线性。
#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int MAXN = 500005;  // 炸弹个数上限
const ll MOD = 1000000007;

int n;                // 炸弹个数
ll x[MAXN];           // x[i]：第 i 个炸弹的坐标（严格递增）
ll r[MAXN];           // r[i]：第 i 个炸弹的爆炸半径
int left_end[MAXN];   // left_end[i]：当前 i 所在闭包块的左端点
int right_end[MAXN];  // right_end[i]：当前 i 所在闭包块的右端点
ll reach[MAXN];       // reach[i]：该块从 x[i] 往右最远能炸到 x[i] + reach[i]

// 输入最多 1e6 个 64 位整数（坐标、半径都可到 10^18 量级，约 20MB 文本），
// 用 fread 整块读入再手工解析，避免 iostream / scanf 在大输入上耗时过多。
// 缓冲区按实际长度动态增长，不能写死大小，否则大输入会被截断成错答案。
vector<char> inbuf;
size_t inlen = 0;
size_t inpos = 0;

void load_all() {
    inbuf.resize(1 << 20);
    inlen = 0;
    while (true) {
        if (inlen == inbuf.size()) inbuf.resize(inbuf.size() * 2);
        size_t got = fread(inbuf.data() + inlen, 1, inbuf.size() - inlen, stdin);
        if (got == 0) break;
        inlen += got;
    }
}

// 读下一个整数（可能带负号）；读到末尾之后一律返回 0
ll read_int() {
    while (inpos < inlen && (inbuf[inpos] < '0' || inbuf[inpos] > '9') && inbuf[inpos] != '-') {
        inpos++;
    }
    bool negative = false;
    if (inpos < inlen && inbuf[inpos] == '-') {
        negative = true;
        inpos++;
    }
    ll value = 0;
    while (inpos < inlen && inbuf[inpos] >= '0' && inbuf[inpos] <= '9') {
        value = value * 10 + (inbuf[inpos] - '0');
        inpos++;
    }
    return negative ? -value : value;
}

void read_input() {
    load_all();
    n = int(read_int());
    for (int i = 1; i <= n; i++) {
        x[i] = read_int();
        r[i] = read_int();
        left_end[i] = i;
        right_end[i] = i;
        reach[i] = r[i];
    }
}

// 第一趟：i 从小到大，只往左扩展。
// 队列尾指针 left_end[i] 每跳一次就变成 left_end[left_end[i] - 1]，
// 也就是把左边那一整块闭包合并进来；合并时同步取两块的右向射程较大者。
// 因为 x 严格递增且左块在 i 左边，新的右向射程写成
// 「左块射程 - 两点距离」，再与自己的射程取 max。
void sweep_left() {
    for (int i = 2; i <= n; i++) {
        while (left_end[i] > 1 && x[i] - x[left_end[i] - 1] <= reach[i]) {
            int prev = left_end[i] - 1;
            ll spread = reach[prev] - (x[i] - x[prev]);
            if (spread > reach[i]) reach[i] = spread;
            left_end[i] = left_end[prev];
        }
    }
}

// 第二趟：i 从大到小，只往右吸收。
// 判断标准仍然是第一趟留下的 reach[i]（这里刻意不更新，理由见正文）：
// 越过当前块右端之后还能继续够到的东西，只可能由初始块 [left_end[i], i] 里的炸弹直接炸到，
// 而初始块的右向射程已经固化成 reach[i]。
// 吸收进来的是 right_end[i] + 1 那一整块的最终答案区间，所以左端点取 min、右端点直接接上。
void sweep_right() {
    for (int i = n - 1; i >= 1; i--) {
        while (right_end[i] < n && x[right_end[i] + 1] - x[i] <= reach[i]) {
            int next = right_end[i] + 1;
            if (left_end[next] < left_end[i]) left_end[i] = left_end[next];
            right_end[i] = right_end[next];
        }
    }
}

int main() {
    read_input();
    sweep_left();
    sweep_right();

    ll answer = 0;
    for (int i = 1; i <= n; i++) {
        ll count = right_end[i] - left_end[i] + 1;
        answer = (answer + (ll)i % MOD * (count % MOD)) % MOD;
    }
    printf("%lld\n", answer);
    return 0;
}
