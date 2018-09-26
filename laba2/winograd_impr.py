def winograd_impr_multi(G, H):
    a = len(G)
    b = len(H)
    c = len(H[0])

    if b != len(G[0]):
        print("Incorrect dimension of matrices")
        return
    row_factor = [0 for i in range(a)]
    col_factor = [0 for i in range(c)]
    b_div_2 = b // 2
        
    # Row Factor calc
    for i in range(a):
        for j in range(0, b_div_2 + 1, 2):
            #print(j)
            row_factor[i] += G[i][j] * G[i][j + 1]
    #print(row_factor)
        
    # Col Factor calc
    for i in range(c):
        for j in range(0, b_div_2 + 1, 2):
            col_factor[i] += H[j][i] * H[j + 1][i]
    #print(col_factor)
    
    answer = [[0 for i in range(c)] for j in range(a)]
    for i in range(a):
        for j in range(c):
            answer[i][j] = - row_factor[i] - col_factor[j]
            for k in range(0, b_div_2 + 1, 2):
                answer[i][j] += ((G[i][k] + H[k + 1][j]) * (G[i][k + 1] + H[k][j]))

    #For odd matrix
    #print(answer)
    if b % 2:
        for i in range(a):
            for j in range(c):
                answer[i][j] += G[i][b - 1] * H[b - 1][j]

    return answer


if __name__ == "__main__":
    A = [[1,2,4,3], 
        [4,5,6,2]]
        
    B = [[3,4], 
        [5,1],
        [6,-3],
        [1,0]]
        
    #print(winograd_impr_multi(A, B))
    #print("\n",classic.mult_matrix_classic(A, B))
