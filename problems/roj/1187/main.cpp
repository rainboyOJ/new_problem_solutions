/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:41
 * update_at: 2026-10-05 04:41
 */
#include <cstdio>

typedef long long ll;

const int ALPHA = 26; // 小写字母 a-z 的字符集大小

int cnt[ALPHA]; // cnt[i] 表示字母 ('a' + i) 在字符串中出现的次数
char s[1005];   // 输入字符串，长度不超过 1000

int main() {
    scanf("%s", s);
    for (int i = 0; s[i] != '\0'; i++) {
        cnt[s[i] - 'a']++;
    }

    // 从 'a' 到 'z' 依次比较，只在次数严格更大时更新，
    // 这样并列最大时会保留 ASCII 码最小的字符。
    int answer = 0;
    for (int i = 1; i < ALPHA; i++) {
        if (cnt[i] > cnt[answer]) {
            answer = i;
        }
    }

    printf("%c %d\n", 'a' + answer, cnt[answer]);
    return 0;
}
