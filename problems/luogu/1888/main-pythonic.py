import math
a,b,c=sorted(map(int,input().split()))
g=math.gcd(a,c)
print(f"{a//g}/{c//g}")
