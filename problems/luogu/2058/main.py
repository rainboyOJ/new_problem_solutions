import sys
from collections import Counter, deque


input = sys.stdin.buffer.readline
passengers = deque()
country_count = Counter()
answers = []

for _ in range(int(input())):
    data = list(map(int, input().split()))
    time, count = data[:2]

    while passengers and passengers[0][0] <= time - 86400:
        _, country = passengers.popleft()
        country_count[country] -= 1
        if country_count[country] == 0:
            del country_count[country]

    for country in data[2:2 + count]:
        passengers.append((time, country))
        country_count[country] += 1

    answers.append(str(len(country_count)))

print("\n".join(answers))
