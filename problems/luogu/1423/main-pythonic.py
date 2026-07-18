s=float(input())
step=2.0; dist=0.0; day=0
while dist<s:
    dist+=step; step*=0.98; day+=1
print(day)
