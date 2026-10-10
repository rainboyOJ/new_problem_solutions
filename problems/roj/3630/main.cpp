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
struct Split{int s,p,t,b;};
vector<Split> splits[4]; map<array<int,5>, int> memo_plain; int best_ans; map<string,int> seen;
int slot_of(int value,int suit){ if(value==0) return 12+suit; if(value==2) return 12; return value==1?11:value-3; }
int absorb(int single,int pairc,int triple,int bomb){ int bare=single+pairc+triple+bomb,best=bare; for(int ts=0;ts<=min(triple,single);ts++) for(int tp=0;tp<=min(triple-ts,pairc);tp++){int fs=single-ts, fp=pairc-tp; int carried=2*min(bomb, fs/2+fp/2); best=min(best,bare-ts-tp-carried);} return best; }
int min_plain(int c1,int c2,int c3,int c4,int jokers){ array<int,5> key={c1,c2,c3,c4,jokers}; if(memo_plain.count(key)) return memo_plain[key]; vector<array<int,4> > states; states.push_back({0,0,0,0}); int nums[4]={c1,c2,c3,c4}; for(int size=1;size<=4;size++){ for(int rep=0;rep<nums[size-1];rep++){ vector<array<int,4> > nxt; for(int i=0;i<(int)states.size();i++) for(int j=0;j<(int)splits[size-1].size();j++){Split sp=splits[size-1][j]; array<int,4> a={states[i][0]+sp.s,states[i][1]+sp.p,states[i][2]+sp.t,states[i][3]+sp.b}; nxt.push_back(a);} states.swap(nxt); } } int plain=100; for(int i=0;i<(int)states.size();i++) plain=min(plain,absorb(states[i][0]+jokers,states[i][1],states[i][2],states[i][3])); if(jokers==2){int tmp=100; for(int i=0;i<(int)states.size();i++) tmp=min(tmp,absorb(states[i][0],states[i][1],states[i][2],states[i][3])); plain=min(plain,tmp+1);} memo_plain[key]=plain; return plain; }
int plain_of(vector<int>&cnt){int hist[4]={0,0,0,0}; for(int i=0;i<13;i++) if(cnt[i]) hist[cnt[i]-1]++; return min_plain(hist[0],hist[1],hist[2],hist[3],cnt[13]+cnt[14]);}
string enc_state(int i, vector<int>&cnt){string s=to_string(i)+":"; for(int j=0;j<15;j++){s.push_back(char('0'+cnt[j]));} return s;}
vector<vector<int> > cuts(vector<int>&cnt,int start){ vector<vector<int> > res; int needs[3]={1,2,3}, lens[3]={5,3,2}; for(int a=0;a<3;a++){int need=needs[a], minlen=lens[a]; for(int len=minlen; len<13-start; len++){bool ok=true; for(int k=0;k<len;k++) if(cnt[start+k]<need){ok=false; break;} if(!ok) break; vector<int> nxt=cnt; for(int k=0;k<len;k++) nxt[start+k]-=need; res.push_back(nxt);}} return res;}
int sum_cnt(const vector<int>&v){int s=0; for(int i=0;i<(int)v.size();i++) s+=v[i]; return s;}
bool cmp_cut(const vector<int>&a,const vector<int>&b){return sum_cnt(a)<sum_cnt(b);} 
void dfs(int i,int steps,vector<int>&cnt){int value=steps+plain_of(cnt); if(value<best_ans) best_ans=value; if(i==12 || steps+1>=best_ans) return; string key=enc_state(i,cnt); if(seen.count(key) && seen[key]<=steps) return; seen[key]=steps; if(cnt[i]==0){dfs(i+1,steps,cnt);return;} vector<vector<int> > all=cuts(cnt,i); sort(all.begin(),all.end(),cmp_cut); for(int z=0;z<(int)all.size();z++) dfs(i,steps+1,all[z]); dfs(i+1,steps,cnt);}
int min_rounds(vector<int> cards){best_ans=plain_of(cards); seen.clear(); dfs(0,0,cards); return best_ans;}
int main(){ios::sync_with_stdio(false); cin.tie(nullptr); splits[0].push_back({1,0,0,0}); splits[1].push_back({0,1,0,0}); splits[1].push_back({2,0,0,0}); splits[2].push_back({0,0,1,0}); splits[2].push_back({1,1,0,0}); splits[2].push_back({3,0,0,0}); splits[3].push_back({0,0,0,1}); splits[3].push_back({1,0,1,0}); splits[3].push_back({0,2,0,0}); splits[3].push_back({2,1,0,0}); splits[3].push_back({4,0,0,0}); int T,n; if(!(cin>>T>>n)) return 0; while(T--){vector<int> cards(15); for(int i=0;i<n;i++){int v,s;cin>>v>>s; cards[slot_of(v,s)]++;} cout<<min_rounds(cards)<<'\n';} return 0;}
