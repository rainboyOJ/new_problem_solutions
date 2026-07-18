n=int(input())
a=list(map(int,input().split()))
best=cur=1
for i in range(1,n):
    cur = cur+1 if a[i]==a[i-1]+1 else 1
    best=max(best,cur)
print(best)
