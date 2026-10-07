/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-06 16:30
 * update_at: 2026-10-06 16:30
 */
#include <cstdio>
#include <cmath>
using namespace std;

typedef long long ll;

const int MAXN = 100005;

ll n;                 // 加油站个数，路线共 n+1 段
double capacity;      // 满箱油能跑的公里数 = 油箱容量（1 升跑 1 公里）
double d[MAXN];       // d[i] 为第 i-1 站到第 i 站的距离，i = 1..n+1

// 输出一个数值：整值去掉小数点，非整值原样输出（与样例的整数格式一致）
void print_value(double v) {
    double rounded = floor(v + 0.5);
    if (fabs(v - rounded) < 1e-9) {
        printf("%.0f", rounded);
    } else {
        printf("%g", v);
    }
}

int main() {
    while (scanf("%lld", &n) == 1) {
        scanf("%lf", &capacity);
        for (ll i = 1; i <= n + 1; i++) {
            scanf("%lf", &d[i]);
        }

        // 贪心扫每段路：油够就开，不够就在当前站补满（补入量 = 满箱 - 当前油量）
        double tank = capacity;   // 出发时满箱，这一箱不计入次数与总量
        ll cnt = 0;               // 加油次数
        double total = 0;         // 加油总量
        for (ll i = 1; i <= n + 1; i++) {
            if (tank >= d[i]) {
                tank -= d[i];
            } else {
                total += capacity - tank;  // 补满：加了多少 = 缺了多少
                tank = capacity - d[i];    // 加满后立刻开过这一段
                cnt++;
            }
        }

        printf("%lld ", cnt);
        print_value(total);
        printf("\n");
    }
    return 0;
}
