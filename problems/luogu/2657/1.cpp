#include <bits/stdc++.h>
using namespace std;

/**
* dp[i]
 * Write me later
 */

int dp[15][20]; 
// dp 方程 dp[pos][last] 表示长度为pos+1 且 第pos+1高位数字为last的情况下,所有的可能


int num[15]; // 数字的拆分

// 在num 从高位到低位 在 dp上走
// pos 当前的位, 还代表层
// last 是上一个数字

int dfs(int pos,int last,bool limit, bool lead) {
    // lead 全是0, 就返回0, 否则能到达这个位置 就是1
    if( pos ==0 ) return lead ? 0 : 1;
    if( !limit && !lead  && dp[pos][last] != -1)
    {
        return dp[pos][last];
    }

    int up = limit ? num[pos] : 9; //上界
    
    int res = 0;

    for(int i = 0; i<= up;i++)
    {
        if( lead ) {
            res += dfs(pos-1,i,limit && (i == num[pos]), lead && (i == 0) );
        }
        else {
            if( abs(i - last) >=2)
                res += dfs(pos-1,i,limit && (i == num[pos]), lead && (i==0));
              //  这里 lead && (i==0) 一定是 false
        }

    }

    if( !limit && !lead)
        dp[pos][last] = res;
    return res;


}

int solve(int x) {
    if( x == 0) return 0;
    int len = 0;
    while(x) {
        num[++len] = x % 10;
        x /= 10;
    }
    return dfs(len,0,true,true);
}

int main (int argc, char *argv[]) {

    memset(dp,-1,sizeof(dp));

        int l ,r;
        cin >> l >> r;
        cout << solve(r) - solve(l-1) << endl;
        

    
    return 0;
}
