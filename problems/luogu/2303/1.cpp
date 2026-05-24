/**
 * Author by Rainboy blog: https://blog.roj.ac.cn github : https://github.com/rainboylvx
 * date: 2025-12-17 17:10:30
 */
#include <bits/stdc++.h>
using namespace std;
typedef  long long ll;
typedef  unsigned long long ull;

const int maxn = 1e7+5;
int n,m;
ll ans;


int phi[maxn]; // 欧拉函数
bool st[maxn]; // st[i] = 1 表示被删除,不是素数
std::vector<int> primes; //存素数

void get_phi_line(){
    phi[1] = 1;
    for(int i = 2;i <= n ;++i ) // i: 2->n
    {

        if( !st[i])
        {
            primes.push_back(i);
            phi[i] = i - 1;
        }

        //枚举前面的素数
        for(auto p : primes) {

            if( i * p > n) break;
            st[i * p ] = 1;

            if( i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            }
            else {
                phi[p * i] = phi[i] * (p-1); 
            }

        }
    }
}


signed main () {
    ios::sync_with_stdio(false); cin.tie(0);
    std::cin >> n;

    get_phi_line();

    for(ll i = 1 ;i*i <= n; i++) {
        if( n % i == 0) {
            // i 是d的因子
            ans += i * phi[n/i];

            // 不能重复的计算
            if( i *i != n) {
                ans += (n /i) * phi[i];
            }
        }
    }

    std::cout << ans << "\n";
    
    return 0;
}
