/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 */
#include <cstdio>
#include <cmath>
#include <algorithm> // 包含 std::max
using namespace std;

// POJ 3122 Pie
// 只需要 cstdio 和 cmath，不需要 iostream 和 iomanip

const int maxn = 10005; 
int n, f;
double area[maxn]; // 直接存储体积(面积)

// const double PI = 3.1415926535897932; 
// 精度建议更高一点，或者使用 acos(-1.0)
const double PI = acos(-1.0);

bool check(double val) {
    int count = 0;
    // 总人数是 f + 1 (朋友 + 自己)
    int target = f + 1;
    
    // 注意：这里使用 0 到 n (左闭右开)
    for(int i = 0; i < n; i++) {
        count += (int)(area[i] / val);
        if (count >= target) return true;
    }
    return false;
}

double bs_find(double l, double r) {
    // 循环100次通常比 while(r-l > eps) 更稳定且更快
    for(int i = 0; i < 100; i++){
        double mid = (l + r) / 2.0;
        if(check(mid)) {
            l = mid; 
        } else {
            r = mid;
        }
    }
    return l; 
}

void solve() {
    // 1. 使用 scanf
    scanf("%d %d", &n, &f);
    
    double max_vol = 0;
    
    // 2. 修正循环：从 0 到 n-1，与 check 函数保持一致
    for(int i = 0; i < n; i++) {
        int r;
        scanf("%d", &r);
        
        // 计算面积
        area[i] = PI * r * r;
        
        // 3. 修正最大值的获取逻辑 (二分的右边界)
        if(area[i] > max_vol) max_vol = area[i];
    }

    // 二分范围：0 到 最大那块派的体积
    double ans = bs_find(0, max_vol);
    
    // 4. 使用 printf 输出，保留4位小数
    printf("%.4f\n", ans);
}

int main () {
    int t;
    scanf("%d", &t); // 使用 scanf
    while(t--) {
        solve();
    }
    return 0;
}
