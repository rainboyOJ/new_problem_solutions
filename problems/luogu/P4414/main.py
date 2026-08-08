values = sorted(map(int, input().split()))
order = input()

named = {
    "A": values[0],
    "B": values[1],
    "C": values[2],
}

print(*(named[ch] for ch in order), end="")
