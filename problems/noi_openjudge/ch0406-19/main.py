while True:
    one, two, three, four, five, six = map(int, input().split())
    if one == two == three == four == five == six == 0:
        break
    boxes = six
    boxes += five
    one = max(0, one - five * 11)
    boxes += four
    needed_two = four * 5
    used_two = min(two, needed_two)
    two -= used_two
    one = max(0, one - (needed_two - used_two) * 4)
    boxes += (three + 3) // 4
    remainder = three % 4
    if remainder:
        required_two = (0, 5, 3, 1)[remainder]
        used_two = min(two, required_two)
        two -= used_two
        one = max(0, one - ((0, 7, 6, 5)[remainder] + (required_two - used_two) * 4))
    boxes += (two + 8) // 9
    remainder = two % 9
    if remainder:
        one = max(0, one - (36 - remainder * 4))
    boxes += (one + 35) // 36
    print(boxes)
