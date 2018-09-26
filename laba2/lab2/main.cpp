#include <QCoreApplication>
#include <iostream>
#include <qDebug>
#include <vector>
#include <stdlib.h>
#include <time.h>

std::vector<std::vector<int>> ret_matr(int n, int m)
{
    srand(time(NULL));

    std::vector<std::vector<int>> res(n);
    for(int i = 0; i < n; i++)
    {

        for(int j = 0; j < m; j++)
        {
            res[i].push_back(rand() % 100);
            //qDebug() << res[i][j];
        }

    }
    return res;
}

std::vector<std::vector<int>> mult_matrix_classic(std::vector<std::vector<int>> &A,
                                                  std::vector<std::vector<int>> &B)
{
    // A = M x N    B = N x Q
    if (B.size() != A[0].size())
    {
        printf("Incorrect dimension of matrices");

    }

    int m = A.size();
    int q = B[0].size();
    int n = B.size();

    std::vector<std::vector<int>> res(m);
    for(int i = 0; i < m; i++)
    {
        for(int j = 0; j < q; j++)
        {
            res[i].push_back(0);
            for(int k = 0; k < n; k++)
                res[i][j] += A[i][k] * B[k][j];
        }
    }
    return res;
}

std::vector<std::vector<int>> mult_matrix_win(std::vector<std::vector<int>> &G,
                                                  std::vector<std::vector<int>> &H)
{

}


unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

int main()
{
    /*std::vector<std::vector<int>> A = {{1,2,3},
                   {4,5,6},
                   {7,8,9}};

    std::vector<std::vector<int>> B = {{3,2,3},
                   {4,5,6},
                   {4,8,9}};
    std::vector<std::vector<int>> res = mult_matrix_classic(A, B);*/
    unsigned long long tb, te, t_mid1 = 0, t_mid2 = 0;
    std::vector<std::vector<int>> a, b, c;
    /*for(int i = 0; i < 3; i++)
    {
        for(int j = 0; j < 3; j++)
        {
            printf("%d ",res[i][j]);
        }
        printf("\n");
    }*/
    int start = 100;
    int end = 1000;
    int step = 100;
    int rep = 10;

    for(int i = start; i <= end; i += step)
    {
        a.clear();
        a = ret_matr(i,i);

        b.clear();
        b = ret_matr(i,i);
        t_mid1 = 0;
        c.clear();
        for(int j = 0; j < rep; j++)
        {
            tb = tick();
            c = mult_matrix_classic(a,b);
            te = tick();
            t_mid1 += (te - tb);
        }
        t_mid1 /= rep;
        printf("%d  %lld \n",i, t_mid1);
    }

    return 0;
}
