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
const int N=129;
int main(){ios::sync_with_stdio(false); cin.tie(nullptr); int d,n; if(!(cin>>d>>n)) return 0; vector<vector<int> > g(N+1, vector<int>(N+1)); for(int i=0;i<n;i++){int x,y,k;cin>>x>>y>>k; g[x][y]=k;} vector<vector<int> > P(N+1, vector<int>(N+1)); for(int i=0;i<N;i++) for(int j=0;j<N;j++) P[i+1][j+1]=g[i][j]+P[i][j+1]+P[i+1][j]-P[i][j]; int best=0,cnt=0; for(int cx=0;cx<N;cx++) for(int cy=0;cy<N;cy++){int x1=max(cx-d,0),x2=min(cx+d,N-1),y1=max(cy-d,0),y2=min(cy+d,N-1); int s=P[x2+1][y2+1]-P[x1][y2+1]-P[x2+1][y1]+P[x1][y1]; if(s>best){best=s;cnt=1;} else if(s==best) cnt++;} cout<<cnt<<' '<<best<<'\n'; return 0;}
