usage = int(input())

match usage:
    case u if u <= 150:
        fee = u * 0.4463
    case u if u <= 400:
        fee = 150 * 0.4463 + (u - 150) * 0.4663
    case u:
        fee = 150 * 0.4463 + 250 * 0.4663 + (u - 400) * 0.5663

print(f"{fee:.1f}", end="")
