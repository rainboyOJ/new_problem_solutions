// 40 = 2x4x5 ->  此时需要求8 由 [5] 以内的元素组合完成的数量
#include <algorithm>
#include <bits/stdc++.h>
#include <vector>
typedef long long ll;
const int maxn = 1e5;

int n;
const ll mod = 998244353;
ll t;

ll ans;
ll f[2][10000+5]; //上限数字1000
std::vector<ll> fac;

//得到所有的因子
void get_fac() {
    fac.clear();
    fac.push_back(1); // 因子1
    for(ll i = 2;i*i <= t ;++i ) // i: 2->t
    {
        if( t % i == 0)  {
            fac.push_back(i);
            if( t / i != i)  //放置放两遍
                fac.push_back(t / i);
        }

    }

    std::sort(fac.begin(),fac.end());
    fac.push_back(t);
    // for(auto v: fac) std::cout << v << " ";
    // std::cout  << "\n";
}

void dp() {
    memset(f,0,sizeof(f));
    f[0][0] = 1;

    //枚举物品
    int pre  =0;
    int now;

    // k =1 ,表示不从因子 1 开始
    for(int k = 1 ;k<fac.size(); k++)
    {
        int i = k+1;
        now = pre^1;
        //枚举容量
        for(int j = 0 ;j < fac.size();j++) {
            f[now][j] = f[pre][j];
            auto V = fac[j]; // 容量
            if( V >= fac[k] && V % fac[k]== 0) {
                //使用这个物品
                int pos = std::lower_bound(fac.begin(),fac.end(),V / fac[k]) - fac.begin();
                f[now][j] += f[pre][pos];
                f[now][j] %= mod;
            }
        }

        // std::cout << i << ": ";
        // for(int j = 0 ;j < fac.size();j++) 
        //     std::cout << f[now][j] << " ";
        // std::cout  << "\n";
        pre^=1;
    }
    
    // std::cout << (f[now][fac.size()-1] ) << std::endl;
    std::cout << (f[now][fac.size()-1] - 1) % mod << "\n";

}

int main (int argc, char *argv[]) {
    int T;
    std::cin >> T;
    while (T--) {
        std::cin >> t;
        get_fac();
        dp();
        
    }
    
    return 0;
}
