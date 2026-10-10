/**
 * Author by Rainboy blog: https://rainboylv.com github: https://github.com/rainboylvx
 * rbook: -> https://rbook.roj.ac.cn  https://rbook2.roj.ac.cn
 * rainboy的学习导航网站: https://idx.roj.ac.cn
 * create_at: 2026-10-10 11:30
 * update_at: 2026-10-10 11:30
 */

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int T; if(!(cin>>T)) return 0; while(T--){int n;cin>>n; vector<int> coins(n); for(int i=0;i<n;i++) cin>>coins[i]; sort(coins.begin(),coins.end()); int top=coins.back(), basis=0; vector<char> reach(top+1); reach[0]=1; for(int i=0;i<n;i++){int coin=coins[i]; if(!reach[coin]){basis++; for(int x=coin;x<=top;x++) if(reach[x-coin]) reach[x]=1;}} cout<<basis<<'\n';} return 0;}
