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

void print_matr(std::vector<std::vector<int>> matr)
{
    for(int i = 0; i < matr.size(); i++)
    {
        for(int j = 0; j < matr[0].size(); j++)
        {
            printf("%d ",matr[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

#pragma optimize( "", off )
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
#pragma optimize( "", off )
std::vector<std::vector<int>> mult_matrix_win(std::vector<std::vector<int>> &G,
                                                  std::vector<std::vector<int>> &H)
{
     int a = G.size();
     int b = H.size();
     int c = H[0].size();

     if (b != G[0].size())
     {
         printf("Incorrect dimension of matrices");
         //return
     }
     std::vector<int> row_factor(a);
     std::vector<int> col_factor(c);

     //Row Factor calc
     for (int i = 0; i < a; i++)
         for (int j = 0; j < b/2; j++)
             row_factor[i] = row_factor[i] + G[i][2 * j] * G[i][2 * j + 1];
     //qDebug() << row_factor;

     //Col Factor calc
     for (int i = 0; i < c; i++)
         for (int j = 0; j < b/2; j++)
             col_factor[i] = col_factor[i] + H[2 * j][i] * H[2 * j + 1][i];
     //qDebug() << col_factor;
     std::vector<std::vector<int>> res(a);
     for (int i = 0; i < a; i++)
     {
         for (int j = 0; j < c; j++)
         {
             res[i].push_back(0);
             res[i][j] = - row_factor[i] - col_factor[j];
             for (int k = 0; k < b/2; k++)
             {

                 res[i][j] = res[i][j] +((G[i][2 * k] + H[2 * k + 1][j]) * (G[i][2 * k + 1] + H[2 * k][j]));

             }
         }
     }
     //For odd matrix
     //print(answer)

     if (b % 2)
         for (int i = 0; i < a; i++)
             for (int j = 0; j < c; j++)
                 res[i][j] = res[i][j] + G[i][b - 1] * H[b - 1][j];

     return res;
}
#pragma optimize( "", off )
std::vector<std::vector<int>> mult_matrix_win_impr(std::vector<std::vector<int>> &G,
                                                  std::vector<std::vector<int>> &H)
{
     int a = G.size();
     int b = H.size();
     int c = H[0].size();

     if (b != G[0].size())
     {
         printf("Incorrect dimension of matrices");
         //return
     }
     std::vector<int> row_factor(a);
     std::vector<int> col_factor(c);
     int b_div_2 = b / 2;
     //Row Factor calc
     for (int i = 0; i < a; i++)
         for (int j = 0; j <= b_div_2; j+=2)
             row_factor[i] += G[i][j] * G[i][j + 1];
     //qDebug() << row_factor;

     //Col Factor calc
     for (int i = 0; i < c; i++)
         for (int j = 0; j <= b_div_2; j+=2)
             col_factor[i] += H[j][i] * H[j + 1][i];
     //qDebug() << col_factor;
     std::vector<std::vector<int>> res(a);
     for (int i = 0; i < a; i++)
     {
         for (int j = 0; j < c; j++)
         {
             res[i].push_back(0);
             res[i][j] = - row_factor[i] - col_factor[j];
             for (int k = 0; k <= b_div_2; k += 2)
             {
                 res[i][j] += ((G[i][k] + H[k + 1][j]) * (G[i][k + 1] + H[k][j]));

             }
         }
     }
     //For odd matrix
     //print(answer)

     if (b % 2)
     {
         //qDebug() << "dfdfdfdfdfdfdfdf";
         for (int i = 0; i < a; i++)
         {
             for (int j = 0; j < c; j++)
                 res[i][j] = res[i][j] + G[i][b - 1] * H[b - 1][j];
         }
     }

     return res;
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}

#pragma optimize( "", off )
void test_time(void)
{
    unsigned long long tb, te, t_mid1 = 0, t_mid2 = 0, t_mid3 = 0;
    std::vector<std::vector<int>> a, b, c;

    int start;
    int end;
    int step;
    int rep;

    printf("\nOdd\n");
    printf(" size    standart     winogr    winogr_impr\n");
    start = 101;
    end = 301;
    step = 100;
    rep = 10;
    for(int i = start; i <= end; i += step)
    {
        a.clear();
        a = ret_matr(i,i);

        b.clear();
        b = ret_matr(i,i);
        t_mid1 = 0;
        t_mid2 = 0;
        t_mid3 = 0;
        c.clear();
        for(int j = 0; j < rep; j++)
        {
            tb = tick();
            c = mult_matrix_classic(a,b);
            te = tick();
            t_mid1 += (te - tb);
            c.clear();
            tb = tick();
            c = mult_matrix_win(a,b);
            te = tick();
            t_mid2 += (te - tb);
            c.clear();
            tb = tick();
            c = mult_matrix_win_impr(a,b);
            te = tick();
            t_mid3 += (te - tb);
        }
        t_mid1 /= rep;
        t_mid2 /= rep;
        t_mid3 /= rep;
        printf("%5d  %12lld %12lld %12lld\n",i, t_mid1, t_mid2, t_mid3);
    }
    start = 100;
    end = 300;
    step = 100;
    rep = 10;
    printf("Even\n");
    printf(" size    standart     winogr    winogr_impr\n");
    for(int i = start; i <= end; i += step)
    {
        a.clear();
        a = ret_matr(i,i);

        b.clear();
        b = ret_matr(i,i);
        t_mid1 = 0;
        t_mid2 = 0;
        t_mid3 = 0;
        c.clear();
        for(int j = 0; j < rep; j++)
        {
            tb = tick();
            c = mult_matrix_classic(a,b);
            te = tick();
            t_mid1 += (te - tb);
            c.clear();
            tb = tick();
            c = mult_matrix_win(a,b);
            te = tick();
            t_mid2 += (te - tb);
            c.clear();
            tb = tick();
            c = mult_matrix_win_impr(a,b);
            te = tick();
            t_mid3 += (te - tb);
        }
        t_mid1 /= rep;
        t_mid2 /= rep;
        t_mid3 /= rep;
        printf("%5d  %12lld %12lld %12lld\n",i, t_mid1, t_mid2, t_mid3);
    }

}

int main()
{
    std::vector<std::vector<int>> A = {
                   {1,2,3,3},
                   {4,5,6,6},
                   {7,8,9,9}};

    std::vector<std::vector<int>> B = {
                   {3,2,3},
                   {4,5,6},
                   {4,8,9},
                   {5,3,6}};
    /*std::vector<std::vector<int>> res = mult_matrix_classic(A, B);
    std::vector<std::vector<int>> res2 = mult_matrix_win(A, B);
    std::vector<std::vector<int>> res3 = mult_matrix_win_impr(A, B);*/
    test_time();


    return 0;
}
