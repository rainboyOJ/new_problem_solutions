n,k=map(int,input().split())
a=[i for i in range(1,n+1) if i%k==0]
b=[i for i in range(1,n+1) if i%k!=0]
print(f"{sum(a)/len(a):.1f} {sum(b)/len(b):.1f}")
