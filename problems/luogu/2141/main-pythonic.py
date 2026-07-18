n=int(input())
a=list(map(int,input().split()))
s=set(a)
print(len({a[i]+a[j] for i in range(n) for j in range(i+1,n) if a[i]+a[j] in s}))
