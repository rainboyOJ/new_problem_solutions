/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-04 23:13
 * update_at: 2026-10-04 23:13
 */

// 判断一个整数的正负：三分支直接比较输出对应单词。
#include <cstdio>

typedef long long ll;

ll n; // 题目给的整数，范围 [-1e9, 1e9]，int 也够，按惯例用 ll

int main() {
    scanf("%lld", &n);
    if (n > 0)      printf("positive\n");
    else if (n < 0) printf("negative\n");
    else            printf("zero\n");
    return 0;
}
