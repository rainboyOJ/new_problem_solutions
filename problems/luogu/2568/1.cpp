#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll n;
const ll maxn = 1e7+5;

ll phi[maxn]; // 欧拉函数
bool st[maxn]; // st[i] = 1 表示被删除,不是素数
std::vector<ll> primes; //存素数
ll sum[maxn]; // 欧拉函数的前缀和
ll ans; // 最终答案

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



int main (int argc, char *argv[]) {
    scanf("%lld",&n);

    get_phi_line();

    // 求phi前缀和

    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        sum[i] = sum[i-1] + phi[i];
    }

    // 枚举素数
    for( auto p : primes) {
        ans += ( 2 * sum[n/p] - 1);
    }
    std::cout << ans << "\n";
    
    return 0;
}
