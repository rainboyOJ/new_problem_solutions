// 背包
#include <bits/stdc++.h>
using namespace std;
const int maxn = 1e6+5;

typedef long long ll ;
ll f[maxn][maxn];

ll n,m;

char v[maxn][2];

void init(){
    std::cin >> n;
    std::cin >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> v[i][0];
        std::cin >> v[i][1];
    }
}

// 第i个物品在 tot 个的情况下 花多少钱
int spend_val(int i,int tot) {
    int sum = v[i][0] + v[i][1];
    int spen1 = ( tot / 2) * sum ;
    if( tot % 2 == 1)
        spen1 += v[i][0];
    return spen1;
}

// money, 在买前i个物品的多少个
int dfs(int money,int i) {

    if( i == 0) return 0;
    int sum = v[i][0] + v[i][1];
    int tot = money / sum;
    if( money - tot >= v[i][0] ) tot++;
    for(int k = 1;k )

}

int main (int argc, char *argv[]) {
    init();
    
    return 0;
}
