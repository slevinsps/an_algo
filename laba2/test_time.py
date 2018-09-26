from classic import * 
from winograd import *
from winograd_impr import *
import random
from time import *
def ret_table(n, m):
    res = [[random.randrange(50) for i in range(m)] for j in range(n)]
    return res
    #print (res)
    
def test_time():
    start = 100
    end = 1000
    step = 100
    repeat = 10
    print("size classic winograd winograd_impr")
    for i in range (start, end + 1, step):
        A = ret_table(i, i)
        B = ret_table(i, i)
        t1 = t2 = t3 = 0
        for j in range(repeat):
            start = clock()
            mult_matrix_classic(A, B)
            stop = clock()
            t1 += (stop - start)
            
            '''start = clock()
            winograd_multi(A, B)
            stop = clock()
            t2 += (stop - start)
            
            start = clock()
            winograd_impr_multi(A, B)
            stop = clock()
            t3 += (stop - start)'''
        t1 /= repeat
        t2 /= repeat
        t3 /= repeat
        print( "{0:<.5f} | {1:<.5f} | {2:<.5f} | {3:<.5f}\n".format(i, t1, t2,  t3))
    
   
def main():
    test_time()
    
main()
    