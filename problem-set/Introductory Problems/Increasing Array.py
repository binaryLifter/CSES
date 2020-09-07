def solve(v):
    ans = 0
    for i in range(1, len(v)):
        ans += max(0, v[i - 1] - v[i])
        v[i] = max(v[i], v[i - 1])
    return ans


def main():
    input()
    v = list(map(int, input().split()))
    print(solve(v))


main()
