def solve(v):
    number_set = set()
    for i in v:
        number_set.add(i)
    i = 1
    while True:
        if i not in number_set:
            return i
        i += 1
    return -1


def main():
    input()
    v = list(map(int, input().split()))
    print(solve(v))


main()
