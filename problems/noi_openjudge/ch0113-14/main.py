from math import isqrt

rank = int(input())
answers = []

for number in range(100, 1000):
    root = isqrt(number)
    if root * root == number and len(set(str(number))) < 3:
        answers.append(number)

print(answers[rank - 1])
