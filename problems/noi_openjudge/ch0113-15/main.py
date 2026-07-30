import sys
from collections import Counter

tokens = sys.stdin.read().split()
numbers = [int(token) for token in tokens[1:]]
frequencies = Counter(numbers)

if len(frequencies) == 1:
    print("no")
else:
    highest_frequency = max(frequencies.values())
    for number in numbers:
        if frequencies[number] == highest_frequency:
            print(number)
            break
