import sys

data = sys.stdin.read().split()
test_count = int(data[0])
queries = []
max_n = 0

index = 1
for _ in range(test_count):
    n = int(data[index])
    digit = data[index + 1]
    queries.append((n, digit))
    max_n = max(max_n, n)
    index += 2

factorials = [1] * (max_n + 1)
for number in range(1, max_n + 1):
    factorials[number] = factorials[number - 1] * number

answers = []
for n, digit in queries:
    answers.append(str(str(factorials[n]).count(digit)))

print("\n".join(answers))
