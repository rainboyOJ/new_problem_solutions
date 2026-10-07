/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:02
 * update_at: 2026-10-06 13:02
 */

#include <cstdio>
#include <string>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 2505 * 25 + 5; // 每行至多 25 个字母，最多 2500 行

char buf[100];   // 读入的每一行
char rec[MAXN];  // 拼接后的完整比分记录（截断于 E 之前）
ll len = 0;      // 有效记录的长度

// 按 n 分制对记录从头到尾扫一遍，输出每局比分（含末尾残局）
void play(int n) {
    ll a = 0, b = 0; // a: 华华(W)得分, b: 对手(L)得分
    for (ll i = 0; i < len; ++i) {
        if (rec[i] == 'W') a++;
        else b++;
        // 一局结束：某方达到局分 n 且分差至少 2，两者缺一不可
        if (max(a, b) >= n && llabs(a - b) >= 2) {
            printf("%lld:%lld\n", a, b);
            a = 0;
            b = 0;
        }
    }
    // 末尾未打完的一局（可能 0:0）也要输出
    printf("%lld:%lld\n", a, b);
}

int main() {
    // 把所有行拼成一条记录，读到 E 就停止，E 之后内容全部忽略
    while (scanf("%s", buf) == 1) {
        for (ll i = 0; buf[i] != '\0'; ++i) {
            if (buf[i] == 'E') {
                rec[len] = '\0';
                play(11);
                printf("\n");
                play(21);
                return 0;
            }
            rec[len++] = buf[i];
        }
    }
    // 没有 E 也能结束：整条输入都是比分
    rec[len] = '\0';
    play(11);
    printf("\n");
    play(21);
    return 0;
}
