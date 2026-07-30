threshold = int(input())
total = 0.0
term = 0

while total <= threshold:
    term += 1
    total += 1 / term

print(term)
