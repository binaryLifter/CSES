def solve(N):
    if N == 1:
        return [1]
    if N == 2 or N == 3:
        return None
    even = [i for i in range(2, N + 1, 2)]
    odd = [i for i in range(1, N + 1, 2)]
    return even + odd


def main():
    N = int(input())
    ans = solve(N)
    if ans == None:
        print('NO SOLUTION')
    else:
        ans = [str(i) for i in ans]
        print(' '.join(ans))


main()
