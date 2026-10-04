/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-05 04:26
 * update_at: 2026-10-05 04:26
 */
#include <cstdio>
#include <algorithm>
using namespace std;

typedef long long ll;

const int MAXN = 105;

// 学号可能带前导零（如 092），用字符串原样读入、原样输出
struct Student {
    char id[20];
    double score;
};

Student stu[MAXN]; // stu[i] 表示第 i 个学生的（学号, 成绩）

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%s %lf", stu[i].id, &stu[i].score);

    // 成绩互不相同，按成绩从大到小排序，排好后第 k 个就是第 k 名
    for (int i = 1; i <= n; ++i)
        for (int j = i + 1; j <= n; ++j)
            if (stu[j].score > stu[i].score)
                swap(stu[i], stu[j]);

    // 成绩按 %g 输出：68.4 不带尾零，61.0 输出成 61
    printf("%s %g\n", stu[k].id, stu[k].score);
    return 0;
}
