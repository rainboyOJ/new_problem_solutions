n=int(input())
s=f=1
for i in range(2,n+1):
    f*=i; s+=f
print(s)
