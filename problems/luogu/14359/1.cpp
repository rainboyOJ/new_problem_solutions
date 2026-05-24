/**
 * Author by Rainboy blog: https://rainboylv.com github : https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * date: 2026-02-04 09:00:18
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 2e6+5;
int n,k;
int a[maxn];

void init(){
    std::cin >> n; 
    std::cin >> k;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i];
    }

}

int xor_sum(int l,int r){
    int ans = 0;
    for(int i = l;i <= r ;++i ) // i: l->r
    {
        ans = ans ^ a[i];
    }
    return ans;
}

signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    init();

    int tot = 0;
    int start = 1;

    // 结尾
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        bool flag = 0;
        int ans = 0;
        for(int j = start;j<=i;j++) {
            ans = ans ^ a[j];
            if( ans == k) {
                flag = 1;
                start = i+1;
                break;
            }
        }

        if( flag == 1) {
            tot++;
        }
    }
    std::cout << tot << "\n";
    
    return 0;
}
