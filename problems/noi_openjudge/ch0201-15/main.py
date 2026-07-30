case_count = int(input())

for _ in range(case_count):
    weighings = [input().split() for _ in range(3)]
    for coin in "ABCDEFGHIJKL":
        for label, weight in (("light", -1), ("heavy", 1)):
            valid = True
            for left, right, result in weighings:
                difference = weight * (left.count(coin) - right.count(coin))
                observed = "even" if difference == 0 else "up" if difference > 0 else "down"
                if observed != result:
                    valid = False
                    break
            if valid:
                print(f"{coin} is the counterfeit coin and it is {label}.")
                break
        else:
            continue
        break
