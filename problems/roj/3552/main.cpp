/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:43
 * update_at: 2026-10-06 13:45
 */
#include <cstdio>
#include <algorithm>

using namespace std;

typedef long long ll;

const int MAXN = 305; // 学生人数上限

struct Student {
    int id;      // 学号
    int total;   // 三科总分
    int chinese; // 语文成绩
} a[MAXN];

int n;

// 排序规则：总分降序，语文降序，学号升序
bool cmp(const Student &x, const Student &y) {
    if (x.total != y.total) return x.total > y.total;
    if (x.chinese != y.chinese) return x.chinese > y.chinese;
    return x.id < y.id;
}

int main() {
    scanf("%d", &n);
    for (int i = 1; i <= n; i++) {
        int c, m, e;
        scanf("%d%d%d", &c, &m, &e);
        a[i].id = i;
        a[i].chinese = c;
        a[i].total = c + m + e;
    }
    sort(a + 1, a + n + 1, cmp);
    int k = n < 5 ? n : 5; // 输出前 5 名，不足 5 名则全部输出
    for (int i = 1; i <= k; i++) {
        printf("%d %d\n", a[i].id, a[i].total);
    }
    return 0;
}
