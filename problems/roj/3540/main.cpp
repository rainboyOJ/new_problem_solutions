/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 13:36
 * update_at: 2026-10-06 13:36
 */
#include <cstdio>
#include <cstring>
using namespace std;
typedef long long ll;

char name[25];          // 当前学生姓名
ll n;                   // 学生总数
ll avg, cls, papers;    // 当前学生的三个数值属性
char cadre, western;    // 当前学生是否干部 / 是否西部省份
ll best_bonus = -1;     // 当前最大个人奖金
char best_name[25];     // 当前奖金最多学生的姓名
ll total = 0;           // 全体奖金总和

// 按题面五条规则计算单个学生的奖金总数
ll calc(ll a, ll c, char is_cadre, char is_western, ll p) {
    ll res = 0;
    if (a > 80 && p >= 1) res += 8000;          // 院士奖学金
    if (a > 85 && c > 80) res += 4000;          // 五四奖学金
    if (a > 90) res += 2000;                    // 成绩优秀奖
    if (a > 85 && is_western == 'Y') res += 1000; // 西部奖学金
    if (c > 80 && is_cadre == 'Y') res += 850;    // 班级贡献奖
    return res;
}

int main() {
    scanf("%lld", &n);
    for (ll i = 1; i <= n; i++) {
        scanf("%s %lld %lld %c %c %lld", name, &avg, &cls, &cadre, &western, &papers);
        ll bonus = calc(avg, cls, cadre, western, papers);
        total += bonus;
        // 严格大于才更新，保证并列时取最先出现的学生
        if (bonus > best_bonus) {
            best_bonus = bonus;
            strcpy(best_name, name);
        }
    }
    printf("%s\n%lld\n%lld\n", best_name, best_bonus, total);
    return 0;
}
