#include <iostream>
using namespace std;
const int maxn =2e5;  // 数组最大长度
int a[maxn];          // 存储正整数序列
long long n ,s;       // n: 序列长度, s: 目标和

int main (int argc, char *argv[]) {
    int T;  // 测试用例数量
    std::cin >> T;
    while (T--) {
        std::cin >> n >> s;  // 读取序列长度n和目标和s
        
        // 读取序列中的每个正整数
        for(int i = 1;i <= n ;++i ) // i: 1->n
        {
            std::cin >> a[i];
        }
        
        int ans = n+1;    // 答案初始化为不可能的值(n+1)，表示还没找到解
        int i = 1 ,j = 1; // 滑动窗口的左右指针，初始都指向第一个元素

        long long sum = a[1];  // 当前窗口的和，初始为第一个元素
        
        // 滑动窗口主循环，右指针不超过数组边界
        while( j <= n)
        {
            if( sum >=s) {
                // 当前窗口和>=目标值，尝试更新答案
                if(ans > j-i+1) ans = j-i+1;  // 更新最小长度
                
                // 收缩窗口：移除左边界元素，左指针右移
                sum -=a[i];
                i++;
            }
            else if( sum < s) {
                // 当前窗口和<目标值，需要扩展窗口
                j++;                    // 右指针右移
                sum +=a[j];            // 加入新元素到窗口和
            }
        }
        
        // 如果答案还是初始值，说明没找到满足条件的子序列，输出0
        if( ans == n +1) ans = 0;
        std::cout << ans << "\n";
    }
    return 0;
}

