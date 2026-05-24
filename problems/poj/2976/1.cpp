/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-01-05 15:28:43
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,k;
int a[maxn];
int b[maxn];
double v[maxn]; // v[i] = a[i] - x * b[i] 

double _sum(double x) {
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        v[i] = a[i] -  x * b[i];
    }
    std::sort(v+1,v+1+n);

    // 这里是贪心, 选的越少越好, 哪就选 n-k个
    double s = 0;
    for(int i = n;i >k;--i ) // i: 1->n
        s+= v[i];
    return s;
}

//检查pos位置的值是否符合要求
bool check(double mid){
    return _sum(mid) >= 0;
}



signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    while (1) {
        std::cin >> n >> k;
        if( n == 0 &&k == 0) break;
        for(int i = 1;i <= n ;++i ) // i: 1->n
            std::cin >> a[i];
        for(int i = 1;i <= n ;++i ) // i: 1->n
            std::cin >> b[i];

        // 枚举分数
        double l = 0 , r = 1;

        //100 次 应该可以了
        for(int i = 0 ;i < 100 ;i++)
        {
            double mid = (l+r) / 2;
            if( check(mid)) 
                l = mid;
            else
                r = mid;

        }
        std::cout << (int)(l*100 + 0.5) << "\n";
        
    }
    
    return 0;
}
