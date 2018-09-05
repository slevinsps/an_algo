#include <QCoreApplication>
#include <qDebug>
#include <QString>
#include <iostream>
#include <time.h>

void swap_int_poiter(int **pointer1, int **pointer2)
{
    int *buf = *pointer1;
    *pointer1 = *pointer2;
    *pointer2 = buf;
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

bool possible_transpos(QCharRef s1_1, QCharRef s1_2, QCharRef s2_1, QCharRef s2_2)
{
    bool ans = (s1_1 == s2_2 && s1_2 == s2_1 && s1_1 != s1_2);
    //qDebug() << ans << s1_1 << s1_2<< s2_1 << s2_2 << "\n";
    if (ans)
        return true;
    return false;
}

int levinshtein_damerau_fill_number(int left, int diag, int top, int dual_diag, bool equal, bool transp)
{
    int min_number = std::min(diag, std::min(left, top));
    int res = min_number;
    if (!equal || min_number != diag)
    {
            res++;
    }
    if (transp)
        res = std::min(res, dual_diag + 1);
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

    for (int i = 0; i < len_s2 + 1; i++)
    {
        str_matrix2[i] = i;
    }
    for (int i = 1; i < len_s1 + 1; i++)
    {

        swap_int_poiter(&str_matrix1, &str_matrix2);
        /*for (int i = 0; i < len_s2 + 1; i++)
            {
                std::cout << str_matrix1[i] << " ";
            }
            std::cout << "\n";*/
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
    std::cout << "\n";*/
    /*for (int i = 0; i < len_s2 + 1; i++)
    {
        std::cout << str_matrix2[i] << " ";
    }*/
    int res = str_matrix2[len_s2];
    free(str_matrix1);
    free(str_matrix2);
    return res;
}

int levinshtein_damerau_matrix(QString s1, QString s2)
{
    int len_s1 = s1.length();
    int len_s2 = s2.length();
    if (len_s1 == 0)
        return len_s2;
    if (len_s2 == 0)
        return len_s1;
    int *str_matrix1 = (int *)malloc((len_s2 + 1)*sizeof(int));
    int *str_matrix2 = (int *)malloc((len_s2 + 1)*sizeof(int));
    int *str_matrix3 = (int *)malloc((len_s2 + 1)*sizeof(int));


    for (int i = 0; i < len_s2 + 1; i++)
    {
        str_matrix1[i] = i;
    }
    str_matrix2[0] = 1;
    for (int i = 1; i < len_s2 + 1; i++)
    {
        str_matrix2[i] = levinshtein_fill_number(str_matrix2[i - 1], str_matrix1[i - 1], str_matrix1[i], s1[0] == s2[i - 1]);
    }

    for (int i = 2; i < len_s1 + 1; i++)
    {
        str_matrix3[0] = i;
        str_matrix3[1] = levinshtein_fill_number(str_matrix3[0], str_matrix2[0], str_matrix2[1], s1[i-1] == s2[0]);
        for (int j = 2; j < len_s2 + 1; j++)
        {
            str_matrix3[j] = levinshtein_damerau_fill_number(str_matrix3[j - 1], str_matrix2[j - 1], str_matrix2[j],
                    str_matrix1[j-2], s2[j - 1] == s1[i - 1],possible_transpos(s1[i - 2], s1[i - 1], s2[j - 2], s2[j - 1]));
        }
        /*for (int i = 0; i < len_s2 + 1; i++)
            {
                std::cout << str_matrix1[i] << " ";
            }
            std::cout << "\n";*/
        swap_int_poiter(&str_matrix1, &str_matrix2);
        swap_int_poiter(&str_matrix2, &str_matrix3);
    }
    /*for (int i = 0; i < len_s2 + 1; i++)
    {
        std::cout << str_matrix1[i] << " ";
    }
    std::cout << "\n";*/
    /*for (int i = 0; i < len_s2 + 1; i++)
    {
        std::cout << str_matrix2[i] << " ";
    }*/
    std::cout << "\n";
    int res = str_matrix2[len_s2];
    free(str_matrix1);
    free(str_matrix2);
    free(str_matrix3);
    return res;
}



int levinshtein_recur(QString s1, QString s2)
{
    //qDebug() << s1 << s2 << "\n";
    int len_s1 = s1.length();
    int len_s2 = s2.length();

    if (len_s1 == 0)
        return len_s2;
    if (len_s2 == 0)
        return len_s1;


    if (len_s1 == 1)
    {
        if (s1[0] != s2[len_s2-1])
            return len_s2;
        else
            return len_s2 - 1;
    }
    if (len_s2 == 1)
    {
        if (s1[len_s1-1] != s2[0])
            return len_s1;
        else
            return len_s1 - 1;
    }
    int pen = 0;
    if (s1[len_s1-1] != s2[len_s2-1])
        pen++;
    return std::min(levinshtein_recur( s1.left(len_s1-1),  s2) + 1,
                    std::min(levinshtein_recur( s1, s2.left(len_s2-1)) + 1,
                             levinshtein_recur( s1.left(len_s1-1), s2.left(len_s2-1)) + pen));
}

unsigned long long tick(void)
{
    unsigned long long d;
    __asm__ __volatile__ ("rdtsc" : "=A" (d));
    return d;
}


void time_tests()
{
    srand(time(NULL));
    unsigned long long tb, te, t_mid1 = 0, t_mid2 = 0;
    QString s1 = "";
    QString s2 = "";
    int number_of_tests = 10;
    int number_of_tests_check = 10;
    int ans ;
    for (int i = 1; i < number_of_tests + 1; i++)
    {
        for (int j = 0; j < i * 10; j++)
        {
            s1.append('a' + rand() % ('z' - 'a'));
            s2.append('a' + rand() % ('z' - 'a'));
        }

        tb = tick();
        for (int j = 0; j < number_of_tests_check; j++)
        {
           ans = levinshtein_matrix(s1, s2);

        }
        te = tick();
        t_mid1 = (te - tb)/number_of_tests_check;

        tb = tick();
        for (int j = 0; j < number_of_tests_check; j++)
        {
           ans = levinshtein_recur(s1, s2);
        }
        te = tick();
        t_mid2 = (te - tb)/number_of_tests_check;

        //qDebug() << s1 << s2 << "\n";
        s1 = "";
        s2 = "";
        std::cout << "length = " << i * 10 << "\nMatrix method: " <<  t_mid1 << "\nRecur method: " <<  t_mid2 << "\n";
    }
}
int main()
{
    time_tests();
}
/*
int main()
{
    //QString s1 = "tartar"; QString s2 = "otara";
    QString s1 = "mu"; QString s2 = "um";
    //QString s1 = "увлечение"; QString s2 = "развлечения";
    //QString s1 = "uvlecenie"; QString s2 = "razvleceniy";
    //QString s1 = "увлечение"; QString s2 = "";
    int res1 = levinshtein_matrix(s1, s2);
    std::cout << "Levenshtein Distance = " << res1 << "\n";
    int res2 = levinshtein_recur(s1, s2);
    std::cout << "Levenshtein Distance recur = " << res2 << "\n" ;

    int res3 = levinshtein_damerau_matrix(s1, s2);
    std::cout << "levinshtein_damerau_matrix Distance = " << res3;

    //qDebug() << s1[];
}
*/
