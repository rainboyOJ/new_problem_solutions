// 40 = 2x4x5 ->  此时需要求8 由 [5] 以内的元素组合完成的数量
#include <bits/stdc++.h>
#include <vector>
typedef long long ll;
const int maxn = 1e5;

int n;
const int mod = 998244353;
ll t;

ll ans;
int f[1000+5][1000+5]; //上限数字1000
std::vector<int> fac;

//得到所有的因子
void get_fac() {
    fac.clear();

    fac.clear();
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
    f[0][1] = 1;

    //枚举物品
    for(int k = 0 ;k<fac.size(); k++)
    {
        int i = k+1;
        //枚举容量
        for(int j = 1 ;j <= t;j++) {
            f[i][j] = f[i-1][j];
            if( j >= fac[k] && j % fac[k]== 0) {
                //使用这个物品
                f[i][j] += f[i-1][j / fac[k] ];
            }
        }

        // std::cout << i << ": ";
        // for(int j = 1 ;j <= t;j++) 
        //     std::cout << f[i][j] << " ";
        // std::cout  << "\n";
    }
    std::cout << (f[fac.size()][t] - 1) % mod << "\n";

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
