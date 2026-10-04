/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:58
 * update_at: 2026-10-05 02:58
 */
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

char s[105]; // 输入字符串
char ans[105]; // 亲朋字符串

int main() {
    scanf("%s", s);
    int n = strlen(s);
    // 第 i 位由 s[i] 与环形下一位 s[(i+1)%n] 的 ASCII 之和得到
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        ans[i] = s[i] + s[j];
    }
    ans[n] = '\0';
    printf("%s\n", ans);
    return 0;
}
