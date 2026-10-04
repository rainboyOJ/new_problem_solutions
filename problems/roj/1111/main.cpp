/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 02:16
 * update_at: 2026-10-05 02:16
 */

#include <cstdio>

// 一周最多 7 天，天数下标从 1 开始和题面（周一~周日）对应
const int MAXN = 10;

int school[MAXN]; // school[i] 表示第 i 天在学校上课的小时数
int extra[MAXN];  // extra[i]  表示第 i 天妈妈安排的课外班小时数

int main() {
    // 逐天读入，第 i 行是第 i 天（周一~周日）的两个时间
    for (int i = 1; i <= 7; ++i) {
        scanf("%d %d", &school[i], &extra[i]);
    }

    int longest = 8; // 把阈值 8 当作最大值初值：没被更新过就说明没有一天超过 8
    int day = 0;     // day = 0 表示不会不高兴，否则记录最不高兴的是周几

    for (int i = 1; i <= 7; ++i) {
        int total = school[i] + extra[i]; // 第 i 天的上课总时间
        // 只有严格大于才更新：并列时保留最靠前的一天，恰好等于 8 也不算不高兴
        if (total > longest) {
            longest = total;
            day = i;
        }
    }

    printf("%d\n", day);
    return 0;
}
