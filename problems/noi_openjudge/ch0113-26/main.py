from collections import Counter

length = int(input())
text = input()
substrings = [text[index : index + length] for index in range(len(text) - length + 1)]
counts = Counter(substrings)
highest = max(counts.values())

if highest == 1:
    print("NO")
else:
    print(highest)
    printed = set()
    for substring in substrings:
        if counts[substring] == highest and substring not in printed:
            print(substring)
            printed.add(substring)
