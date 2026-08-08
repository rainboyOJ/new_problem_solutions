#include <bits/stdc++.h>
using namespace std;
int n,m;
int a[100][2];

int rcd[100];

int calc_candy(int i,int cnt) {
    int ret = 0;
    ret = (cnt /2) * (a[i][0] + a[i][1]);
    if( cnt % 2== 1)
        ret += a[i][0];
    return ret;
}

int dfs(int money,int dep) {

    if( dep == 1) {

        int tot = 0;

        tot = (money / (a[dep][0] + a[dep][1]));
        int left = money - tot * (a[dep][0] + a[dep][1]);
        tot*=2;
        if( left >= a[dep][0])
            tot++;

        rcd[dep] = tot;

        int ans = 0;
        for(int i =1;i<=n;i++)
        {
            cout << rcd[i] << " ";
            ans += rcd[i];
        }
        cout << "-->> "  << ans << endl;

        return tot;
    }

    int tot = 0;
    for(int i = 0; 1 ;i++) {
        int spend = calc_candy(dep, i);
        if(  spend > money) break;
        rcd[dep] = i;
        int t = dfs(money - spend,dep-1);
        if( t + i > tot) tot = t+i;
    }
    return tot;
}

int main (int argc, char *argv[]) {
    std::cin >> n >> m;
    for(int i = 1;i <= n ;++i ) // i: 1->n
    {
        std::cin >> a[i][0] >> a[i][1];
    }

    int ans = dfs(m,n);
    cout  << "ans = " << ans  << endl;

    
    return 0;
}
