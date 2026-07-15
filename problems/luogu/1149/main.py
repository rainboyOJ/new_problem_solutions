MATCH_COUNT = [6, 2, 5, 5, 4, 5, 6, 3, 7, 6]


def match_count(number):
    return sum(MATCH_COUNT[int(digit)] for digit in str(number))


n = int(input())
target = n - 4
costs = [match_count(number) for number in range(2000)]

answer = 0
for a in range(1000):
    cost_a = costs[a]
    for b in range(1000):
        c = a + b
        if cost_a + costs[b] + costs[c] == target:
            answer += 1

print(answer)
