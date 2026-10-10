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

const int BASE = 1000000000;
struct BigInt {
    vector<int> d;
    int sign;
    BigInt(ll x = 0) { sign = 1; if (x < 0) { sign = -1; x = -x; } if (x == 0) sign = 0; while (x) { d.push_back(x % BASE); x /= BASE; } }
};
void trim(BigInt &a) { while (!a.d.empty() && a.d.back() == 0) a.d.pop_back(); if (a.d.empty()) a.sign = 0; }
BigInt read_big(string s) { BigInt a; a.d.clear(); a.sign = 1; int pos = 0; if (s[0] == '-') { a.sign = -1; pos = 1; } for (int i = s.size(); i > pos; i -= 9) { int l = max(pos, i - 9); int x = 0; for (int j = l; j < i; j++) x = x * 10 + s[j] - '0'; a.d.push_back(x); } trim(a); return a; }
int cmp_abs(const BigInt &a, const BigInt &b) { if (a.d.size() != b.d.size()) return a.d.size() < b.d.size() ? -1 : 1; for (int i = (int)a.d.size() - 1; i >= 0; i--) if (a.d[i] != b.d[i]) return a.d[i] < b.d[i] ? -1 : 1; return 0; }
BigInt add_abs(const BigInt &a, const BigInt &b) { BigInt c; c.sign = 1; int n = max(a.d.size(), b.d.size()); c.d.assign(n, 0); ll carry = 0; for (int i = 0; i < n; i++) { ll v = carry; if (i < (int)a.d.size()) v += a.d[i]; if (i < (int)b.d.size()) v += b.d[i]; c.d[i] = v % BASE; carry = v / BASE; } if (carry) c.d.push_back(carry); trim(c); return c; }
BigInt sub_abs(const BigInt &a, const BigInt &b) { BigInt c; c.sign = 1; c.d.assign(a.d.size(), 0); ll borrow = 0; for (int i = 0; i < (int)a.d.size(); i++) { ll v = (ll)a.d[i] - borrow - (i < (int)b.d.size() ? b.d[i] : 0); if (v < 0) { v += BASE; borrow = 1; } else borrow = 0; c.d[i] = v; } trim(c); return c; }
BigInt add_big(BigInt a, BigInt b) { if (a.sign == 0) return b; if (b.sign == 0) return a; if (a.sign == b.sign) { BigInt c = add_abs(a, b); c.sign = a.sign; return c; } int cmp = cmp_abs(a, b); if (cmp == 0) return BigInt(0); if (cmp > 0) { BigInt c = sub_abs(a, b); c.sign = a.sign; return c; } BigInt c = sub_abs(b, a); c.sign = b.sign; return c; }
BigInt mul_int(BigInt a, ll m) { if (a.sign == 0 || m == 0) return BigInt(0); if (m < 0) { a.sign = -a.sign; m = -m; } BigInt c; c.sign = a.sign; c.d.assign(a.d.size(), 0); ll carry = 0; for (int i = 0; i < (int)a.d.size(); i++) { __int128 v = (__int128)a.d[i] * m + carry; c.d[i] = (ll)(v % BASE); carry = (ll)(v / BASE); } while (carry) { c.d.push_back(carry % BASE); carry /= BASE; } trim(c); return c; }
BigInt div_int(BigInt a, ll m) { BigInt c; c.sign = a.sign; c.d.assign(a.d.size(), 0); ll rem = 0; for (int i = (int)a.d.size() - 1; i >= 0; i--) { __int128 cur = (__int128)rem * BASE + a.d[i]; c.d[i] = (ll)(cur / m); rem = (ll)(cur % m); } trim(c); return c; }
bool less_big(const BigInt &a, const BigInt &b) { if (a.sign != b.sign) return a.sign < b.sign; if (a.sign == 0) return false; int cmp = cmp_abs(a, b); return a.sign > 0 ? cmp < 0 : cmp > 0; }
bool is_zero(const BigInt &a) { return a.sign == 0; }
ostream& operator<<(ostream &os, const BigInt &a) { if (a.sign == 0) { os << 0; return os; } if (a.sign < 0) os << '-'; int n = a.d.size(); os << a.d[n - 1]; for (int i = n - 2; i >= 0; i--) os << setw(9) << setfill('0') << a.d[i]; return os; }

const ll P=2147483647LL;
ll str_mod(string s){int i=0,neg=0; if(s[0]=='-'){neg=1;i=1;} ll v=0; for(;i<(int)s.size();i++) v=((__int128)v*10+s[i]-'0')%P; if(neg && v) v=P-v; return v;}
ll mod_horner(vector<ll>&rev,ll x){ll v=0; for(int i=0;i<(int)rev.size();i++) v=((__int128)v*x+rev[i])%P; return v;}
BigInt horner(vector<BigInt>&c,int x){BigInt v(0); for(int i=(int)c.size()-1;i>=0;i--) v=add_big(mul_int(v,x), c[i]); return v;}
int main(){ios::sync_with_stdio(false);cin.tie(nullptr); int n,m; if(!(cin>>n>>m)) return 0; vector<BigInt> coeff(n+1); vector<ll> rev(n+1); for(int i=0;i<=n;i++){string s;cin>>s; coeff[i]=read_big(s); rev[n-i]=str_mod(s);} vector<int> roots; for(int x=1;x<=m;x++) if(mod_horner(rev,x)==0 && is_zero(horner(coeff,x))) roots.push_back(x); cout<<roots.size()<<'\n'; for(int i=0;i<(int)roots.size();i++) cout<<roots[i]<<'\n'; return 0;}
