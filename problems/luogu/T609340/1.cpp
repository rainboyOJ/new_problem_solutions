/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-18 08:59:01
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,m;
int a[maxn];

void init(){
    std::cin >> n;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    } 
    std::cin >> m;

}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();
    std::sort(a+1,a+1+n);

    int ans= 0;
    //双指针
    int j = n;
    for(int i = 1;i <= n ; ) // i: 1->n
    {
        if( i > j) break; 
        if( a[i] + a[j] ==m) {
            cout << a[i] << " " << a[j] << endl;
            j--;
        }
        else if( a[i] + a[j] > m){
            j--;
        }
        else if( a[i] + a[j] < m) {
            i++;
        }
    }
    
    return 0;
}
