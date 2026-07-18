n, m = map(int, input().split())
people = []

for _ in range(n):
    direction, name = input().split()
    people.append((int(direction), name))

position = 0

for _ in range(m):
    turn, step = map(int, input().split())
    facing = people[position][0]
    if facing == turn:
        position = (position - step) % n
    else:
        position = (position + step) % n

print(people[position][1])
