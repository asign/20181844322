#include <stdio.h>
#include <conio.h>
#include <time.h>

#define NN 9
#define N 3

typedef struct square
{
    int i[NN+1];
    int remain[NN+1];
    int totalCount, resultCount, partResultCount;
    int t_start;
} SQUARE;

int exam(SQUARE *ps);
void print(SQUARE s);
int Used( SQUARE *ps, int no, int i);
void    msquare( SQUARE *ps, int no);

int main(int argc, char *argv[])
{
    SQUARE s;

    s.t_start = clock();
    s.resultCount = s.totalCount = s.partResultCount = 0;

    int     i;

    for(i=1;i<=NN;i++) {
        s.i[i] = 0;
        s.remain[i] = 1;
    }


    msquare(&s, 0);

    _getch();
}

void    msquare( SQUARE *ps, int no)
{
    int     i;


    for(i=1;i<=NN;i++) {
        if ( ps->remain[i]==0 )
            continue;
        ps->i[no] = i;
        ps->remain[i] = 0;
        if (no==NN-1) {
            ps->totalCount ++;
            if (exam(ps)) {
                ps->resultCount ++;
                print(*ps);
            }
        } else
        {
            msquare( ps, no + 1);
        }
        ps->remain[i] = 1;
        ps->i[no] = 0;
    }

}

void print(SQUARE s)
{
    int j;

    printf("%d\t[ ", s.resultCount);
    for (j = 0; j < NN; j++)
        printf("%d ", s.i[j]);
    printf("]\t\t[%d] [%d] \ttime:[%ld]\r\n", s.totalCount, s.partResultCount, clock() - s.t_start);
}


int exam(SQUARE *ps)
{
    int j, k, cflag, n;
    int sum1, sum2, rsum[3], csum[3], stdsum;

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
            csum[k] += ps->i[j * N + k]; 
            rsum[j] += ps->i[j * N + k]; 
        }
        sum1 += ps->i[j * N + j];     
        sum2 += ps->i[j * N + 2 - j]; 
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
