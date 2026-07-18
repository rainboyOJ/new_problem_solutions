n,m=map(int,input().split())
a=[int(input()) for _ in range(n)]
w=sum(a[:m]); ans=w
for i in range(m,n):
    w+=a[i]-a[i-m]; ans=min(ans,w)
print(ans)
