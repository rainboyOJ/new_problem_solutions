
import sys
from itertools import accumulate

data = iter(map(int, sys.stdin.buffer.read().split()))
n = next(data)
values = [next(data) for _ in range(n)]
difference = [0] * (n + 1)

def swap(i,j):
    values[i], values[j] = values[j], values[i]


sorted = False

while not sorted:
    sorted = True
    print("moo")
    for i in range(n-1):
        if values[i] > values[i+1]:
            print(" -> ",f"{[i]}", *values,end=" -> ")
            swap(i,i+1)
            print(" -> ", *values)
    print(" -> ", *values)

    for i in range(n-2, -1, -1):
        if values[i] > values[i+1]:
            print(" <- ",f"{[i]}", *values,end=" -> ")
            swap(i,i+1)
            print(" -> ", *values)
    # debug
    print(" <- ", *values)
    print()

    for i in range(n-1):
        if values[i] > values[i+1]:
            sorted = False
