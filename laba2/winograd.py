#import classic

def winograd_multi(G, H):
    a = len(G)
    b = len(H)
    c = len(H[0])

    if b != len(G[0]):
        print("Incorrect dimension of matrices")
        return
    row_factor = [0 for i in range(a)]
    col_factor = [0 for i in range(c)]

    # Row Factor calc
    for i in range(a):
        for j in range(b // 2):
            row_factor[i] = row_factor[i] + G[i][2 * j] * G[i][2 * j + 1]
    #print(row_factor)
	
	# Col Factor calc
    for i in range(c):
        for j in range(b // 2):
            col_factor[i] = col_factor[i] + H[2 * j][i] * H[2 * j + 1][i]
    #print(col_factor)
	
    answer = [[0 for i in range(c)] for j in range(a)]
    for i in range(a):
        for j in range(c):
            answer[i][j] = - row_factor[i] - col_factor[j]
            for k in range(b // 2):
                answer[i][j] = answer[i][j] +((G[i][2 * k] + H[2 * k + 1][j]) * (G[i][2 * k + 1] + H[2 * k][j]))

    # For odd matrix
    #print(answer)
    if b % 2:
        for i in range(a):
            for j in range(c):
                answer[i][j] = answer[i][j] + G[i][b - 1] * H[b - 1][j]

    return answer


if __name__ == "__main__":
    A = [[1,2], 
		[4,5]]
		
    B = [[3,4], 
		[5,1]]
		
    #print(winograd_multi(A, B))
    #print("\n",classic.mult_matrix_classic(A, B))
