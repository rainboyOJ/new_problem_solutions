n,x=input().split()
print(sum(str(i).count(x) for i in range(1,int(n)+1)))
