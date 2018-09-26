def mult_matrix_classic(A, B):
	# A = M x N    B = N x Q
    if len(B) != len(A[0]):
        print("Incorrect dimension of matrices")
        return

    m = len(A)
    q = len(B[0])
    n = len(B)

    res = [[0 for i in range(q)] for j in range(m)]
    for i in range(m):
        for j in range(q):
            for k in range(n):
                res[i][j] += A[i][k] * B[k][j]
    return res


if __name__ == "__main__":
    A = [[1, 2, 3, 4], [2, 3, 4, 5], [3, 4, 5, 6]]
    B = [[1, 2, 3, 4, 5], [2, 3, 4, 5, 6], [3, 4, 5, 6, 7], [4, 5, 6, 7, 8]]
    #print(mult_matrix_classic(A, B))