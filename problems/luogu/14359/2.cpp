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
int b[(1<<20)+1]; //桶

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
    b[0] = 1;
    int pre_sum = 0;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        pre_sum = pre_sum ^ a[i];
        int s1 = pre_sum ^ k;
        if( b[s1] == 1) {
            // cout << "ok ---> \n";
            // cout << "i: " << i << endl;
            pre_sum = 0;
            memset(b,0,sizeof(b));
            b[0]=1;
            tot++;
        }
        else b[pre_sum] = 1;
    }
    std::cout << tot << "\n";
    
    return 0;
}
