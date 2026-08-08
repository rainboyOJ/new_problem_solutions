import sys


input = sys.stdin.buffer.readline
n, m = map(int, input().split())
people = [input().decode().split() for _ in range(n)]

position = 0
for _ in range(m):
    turn, step = map(int, input().split())
    facing = int(people[position][0])
    position = (position - step) % n if facing == turn else (position + step) % n

print(people[position][1])
