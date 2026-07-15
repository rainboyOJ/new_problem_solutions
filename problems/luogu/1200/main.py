def name_value(name):
    result = 1
    for ch in name:
        result = result * (ord(ch) - ord("A") + 1) % 47
    return result


comet = input().strip()
group = input().strip()

if name_value(comet) == name_value(group):
    print("GO")
else:
    print("STAY")
