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
const int MOD=99999997;
void add(vector<int>&tr,int x){int n=tr.size()-1; while(x<=n){tr[x]++; x+=x&-x;}}
int sumq(vector<int>&tr,int x){int s=0; while(x){s+=tr[x]; x-=x&-x;} return s;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n; if(!(cin>>n)) return 0; vector<ll>a(n),b(n),sa,sb; for(int i=0;i<n;i++) cin>>a[i]; for(int i=0;i<n;i++) cin>>b[i]; sa=a; sb=b; sort(sa.begin(),sa.end()); sort(sb.begin(),sb.end()); map<ll,int> ra,rb; for(int i=0;i<n;i++){ra[sa[i]]=i+1; rb[sb[i]]=i+1;} vector<int> pos(n+1); for(int i=0;i<n;i++) pos[ra[a[i]]]=i; vector<int> tr(n+1); ll inv=0; for(int i=0;i<n;i++){int v=pos[rb[b[i]]]+1; int le=sumq(tr,v); inv += i - le; add(tr,v);} cout << inv%MOD << '\n'; return 0;}
