import math
def is_prime(x):
    return x>1 and all(x%d for d in range(2,int(math.isqrt(x))+1))
def is_pal(x):
    s=str(x); return s==s[::-1]
a,b=map(int,input().split())
# odd digits only except 11 for large ranges optimization optional
for x in range(a,b+1):
    if is_pal(x) and is_prime(x):
        print(x)
