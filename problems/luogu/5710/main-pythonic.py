x=int(input())
a=x%2==0
b=4<x<=12
print(int(a and b), int(a or b), int(a ^ b), int(not a and not b))
