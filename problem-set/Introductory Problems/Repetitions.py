def solve(S):
    ans = 0
    last = '$'
    current = 0
    for c in S:
        if c != last:
            ans = max(ans, current)
            current = 1
            last = c
        else:
            current += 1
    return max(ans, current)


def main():
    S = input()
    print(solve(S))


main()
