#include <stdio.h>
#include <conio.h>
#include <time.h>

#define NN      9
#define N       3

typedef struct square {
    int     i[NN];
    int     totalCount, resultCount, partResultCount;
    int     start;
} SQUARE;


int     exam( SQUARE *ps );
void    print(SQUARE s );
int     Used( int i[], int n);

int main(int argc, char *argv[])
{
    SQUARE  s;

    s.start = clock();
    s.resultCount = s.totalCount = s.partResultCount = 0;

    int     *i;

    i = s.i;
    for (i[0] = 1; i[0] <= 9; i[0]++)
    {
        for (i[1] = 1; i[1] <= 9; i[1]++)
        {
            if ( Used(i, 1) )
                continue;
            for (i[2] = 1; i[2] <= 9; i[2]++)
            {
                if ( Used(i,2) )
                    continue;
                for (i[3] = 1; i[3] <= 9; i[3]++)
                {
                    if ( Used(i,3) )
                        continue;
                    for (i[4] = 1; i[4] <= 9; i[4]++)
                    {
                        if ( Used(i,4) )
                            continue;
                        for (i[5] = 1; i[5] <= 9; i[5]++)
                        {
                            if ( Used(i,5) )
                                continue;
                            for (i[6] = 1; i[6] <= 9; i[6]++)
                            {
                                if ( Used(i,6) )
                                    continue;
                                for (i[7] = 1; i[7] <= 9; i[7]++)
                                {
                                    if ( Used(i,7) )
                                        continue;
                                    for (i[8] = 1; i[8] <= 9; i[8]++)
                                    {
                                        if ( Used(i,8) )
                                            continue;

                                        s.totalCount++;
                                        if ( exam( &s ) )
                                        {
                                            s.resultCount++;
                                            print( s );
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    _getch();
}

int     Used( int i[], int n)
{
    int     j, used = 0;

    for(j=0;j<n;j++) {
        if (i[j]==i[n]) {
            used = 1;
            break;
        }
    }
    return used;
}

void    print( SQUARE s )
{
    int     j;

    printf("%d\t[ ", s.resultCount);
    for (j = 0; j < NN; j++)
        printf("%d ", s.i[j]);
    printf("]\t\t[%d] [%d] \ttime:[%ld]\r\n", s.totalCount, s.partResultCount, clock() - s.start);

}

int     exam( SQUARE *ps )
{
    int     j, k, cflag, n;
    int     sum1, sum2, rsum[3], csum[3], stdsum;

    stdsum = 15;

    for (j = 0; j < 3; j++)
    {
        csum[j] = 0;
        rsum[j] = 0;
    }
    sum1 = 0;
    sum2 = 0;

    for (j = 0; j < 3; j++)
    {
        for (k = 0; k < 3; k++)
        {
            csum[k] += ps->i[j*N+k];     
            rsum[j] += ps->i[j*N+k];     
        }
        sum1 += ps->i[j*N+j];           
        sum2 += ps->i[j*N+N-1-j];         
    }

   
    if (sum1 != stdsum || stdsum != sum2)
        return 0;

    (ps->partResultCount)++;
    cflag = 1;
    for (j = 0; j < 3; j++)
    {
        if (csum[j] != stdsum || rsum[j] != stdsum)
        {
            cflag = 0;
            break;
        }
    }    
    return cflag;

}