/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 09:42
 * update_at: 2026-10-05 09:42
 */

#include <cstdio>
#include <cstring>

typedef long long ll;

const int MAXL = 250; // n 不超过 240 位

char num[MAXL]; // 输入的数字串
char stk[MAXL]; // 单调不减栈：stk[0..top-1] 是当前确定保留的前缀
ll top;         // 栈顶指针（栈内元素个数）
ll s;           // 还能删多少个数字（删除名额）

int main() {
    scanf("%s", num);
    scanf("%lld", &s);

    ll len = strlen(num);

    // 贪心：读入新数字 c 时，栈顶比 c 大说明栈顶那位靠左却更大，
    // 删掉它一定更优，弹出并消耗一个删除名额，直到栈顶不大于 c 或名额用完
    top = 0;
    for (ll i = 0; i < len; i++) {
        char c = num[i];
        while (s > 0 && top > 0 && stk[top - 1] > c) {
            top--; // 弹出栈顶 = 删掉一个数字
            s--;
        }
        stk[top] = c;
        top++;
    }

    // 扫描结束后串已单调不减，名额没用完就从末尾（最大的几位）继续删
    top -= s;
    s = 0;

    // 剥掉前导零；剩下的字符全是 0 时输出 0
    ll start = 0;
    while (start < top - 1 && stk[start] == '0')
        start++;

    for (ll i = start; i < top; i++)
        putchar(stk[i]);
    putchar('\n');

    return 0;
}
