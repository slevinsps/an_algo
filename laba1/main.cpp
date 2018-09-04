#include <QCoreApplication>
#include <qDebug>
#include <QString>
#include <iostream>

void free_matrix(double **res, int n)
{
    for (int i = 0; i < n;i++)
    {
        free(res[i]);
    }
    free(res);
}

double **allocate(int n, int m)
{
    double **res = (double **)calloc(n,sizeof(double*));
    if (!res)
        return NULL;
    for (int i = 0; i < n; i++ )
    {
        res[i] = (double *)malloc(m*sizeof(double));
        if (!res)
        {
            free_matrix(res,n);
            return NULL;
        }
    }
    return res;
}

void print_mat(FILE *f, double **matrix, int n,int m)
{
    for (int i = 0; i < n; i++ )
    {
        for (int j = 0; j < m; j++ )
        {
            fprintf(f, "%f ", matrix[i][j]);
        }
        fprintf(f,"\n");
    }
}
int levinshtein_fill_number(int left, int diag, int top, bool equal)
{
    int min_number = std::min(diag, std::min(left, top));
    int res = min_number;
    if (!equal || min_number != diag)
    {
            res++;
    }
    return res;
    //qDebug() << min_number;
}
int levinshtein_matrix(QString s1, QString s2)
{
    int len_s1 = s1.length();
    int len_s2 = s2.length();
    if (len_s1 == 0)
        return len_s2;
    if (len_s2 == 0)
        return len_s1;
    int *str_matrix1 = (int *)malloc((len_s2 + 1)*sizeof(int));
    int *str_matrix2 = (int *)malloc((len_s2 + 1)*sizeof(int));
    int *buf;

    for (int i = 0; i < len_s2 + 1; i++)
    {
        str_matrix2[i] = i;
    }
    for (int i = 1; i < len_s1 + 1; i++)
    {
        buf = str_matrix1;
        str_matrix1 = str_matrix2;
        str_matrix2 = buf;

        str_matrix2[0] = i;
        for (int j = 1; j < len_s2 + 1; j++)
        {
            str_matrix2[j] = levinshtein_fill_number(str_matrix2[j - 1], str_matrix1[j - 1], str_matrix1[j], s2[j - 1] == s1[i - 1]);
        }
    }
    /*for (int i = 0; i < len_s2 + 1; i++)
    {
        std::cout << str_matrix1[i] << " ";
    }
    std::cout << "\n";
    for (int i = 0; i < len_s2 + 1; i++)
    {
        std::cout << str_matrix2[i] << " ";
    }*/
    int res = str_matrix2[len_s2];
    free(str_matrix1);
    free(str_matrix2);
    return res;
}

int main()
{
    //QString s1 = "тартар"; QString s2 = "отара";
    //QString s1 = "МГТУ"; QString s2 = "МГУ";
    //QString s1 = "увлечение"; QString s2 = "развлечения";
    //QString s1 = "увлечение"; QString s2 = "";
    int res = levinshtein_matrix(s1, s2);
    std::cout << "Levenshtein Distance = " << res;
}
