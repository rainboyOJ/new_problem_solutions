n = int(input())
times = list(map(int, input().split()))

people = [(times[index], index + 1) for index in range(n)]
people.sort()

order = [person_id for _, person_id in people]

total_wait = 0
elapsed = 0
for time, _ in people:
    total_wait += elapsed
    elapsed += time

print(*order)
print(f"{total_wait / n:.2f}")
