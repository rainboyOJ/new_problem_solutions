a, b, c = sorted(map(int, input().split()))
order = input().strip()

out = []
for ch in order:
    match ch:
        case "A":
            out.append(a)
        case "B":
            out.append(b)
        case "C":
            out.append(c)

print(*out, end="")
