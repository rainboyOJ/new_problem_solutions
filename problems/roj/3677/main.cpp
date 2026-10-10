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
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n; string text; if(!(cin>>n>>text)) return 0; if((int)text.size()>n) text=text.substr(0,n); vector<ll> nodes(1,0), cnt(1,1); map<ll,int> where; int cur=0; for(int i=0;i<(int)text.size();i++){int c=(unsigned char)text[i]; if((nodes[cur]&255)==c) cur=nodes[cur]>>8; else {ll key=((ll)cur<<8)|c; int nxt; if(where.count(key)) nxt=where[key]; else {nxt=nodes.size(); where[key]=nxt; nodes.push_back(key); cnt.push_back(0);} cur=nxt;} cnt[cur]++;} ll ans=0; for(int i=0;i<(int)cnt.size();i++) ans+=cnt[i]*(cnt[i]-1)/2; cout<<ans<<'\n'; return 0;}
