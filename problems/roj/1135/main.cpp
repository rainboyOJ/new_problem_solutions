/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:58
 * update_at: 2026-10-05 02:58
 */

#include <cstdio>

typedef long long ll;

const int MAXN = 260;

char s[MAXN]; // s 存输入的碱基链，长度不超过 255

int main() {
    scanf("%s", s);

    // 每个位置的互补碱基只由自己决定，与左右邻居无关，逐位替换即可
    for (int i = 0; s[i] != '\0'; i++) {
        if (s[i] == 'A')
            putchar('T');
        else if (s[i] == 'T')
            putchar('A');
        else if (s[i] == 'G')
            putchar('C');
        else
            putchar('G'); // 只剩 'C'，配对成 'G'
    }
    putchar('\n');

    return 0;
}
