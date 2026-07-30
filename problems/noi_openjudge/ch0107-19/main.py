first, second = input().split()
longer, shorter = (first, second) if len(first) >= len(second) else (second, first)
print("true" if shorter in longer + longer else "false")
