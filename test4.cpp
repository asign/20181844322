#include <stdio.h>
#include <conio.h>
#include <time.h>
#include <memory.h>
#include <string.h>

#include "square.h"
int     NN;
int     N, interval;
SQUARENODE  head, *tail;
int main(int argc, char *argv[])
{
    SQUARE s;
    printf("input a number(3-5):");
    scanf("%d,%d", &N, &interval);
    NN = N*N;
    head.next = NULL;
    tail = &head;

    initSquare(&s);
    msquare(&s, 0);
    char    filename[256];
    sprintf(filename, "%dx%d result.txt", N,N);
    fileWrite( filename, head );
    sl_free(head);
    _getch();
}
void    initSquare( SQUARE  *ps) 
{
    ps->t_start = clock();
    ps->resultCount = ps->totalCount = ps->partResultCount = 0;

    int     i, temp;
    ps->t_start = clock();
    temp = 0;    
    for(i=1;i<=NN;i++) {
        ps->i[i] = 0;
        ps->remain[i] = 1;
        temp += i;
    }
    ps->stdsum = temp / N;
    ps->t_current = 0;
}
SQUARENODE *sl_append(SQUARE *ps) 
{
    SQUARENODE  *newnode;

    newnode = new SQUARENODE;

    memcpy( &(newnode->s), ps, sizeof(SQUARE) );
    newnode->next = tail->next;
    tail->next = newnode;
    tail = newnode;

    return newnode;
}

void    sl_free( SQUARENODE head)
{
    SQUARENODE  *node;

    while( head.next!=NULL) {
        node = head.next;
        head.next = node->next;
        delete node;
    }
}

void    msquare( SQUARE *ps, int no)
{
    int     i;
    int     r, c, rsum, csum, temprsum, tempcsum;

    r = no / N;
    c = no % N;

    if (r==0) {
        ps->csum[c] = 0;
        if (c==0) {
            for(i=0;i<N;i++)
                ps->rsum[i]=0;
        }
    }
    rsum = ps->rsum[r];
    csum = ps->csum[c];

    for(i=1;i<=NN;i++) {
        if ( ps->remain[i]==0 )
            continue;
        
        tempcsum = csum + i;
        temprsum = rsum + i;
        if (temprsum>ps->stdsum || tempcsum>ps->stdsum)
            break;

        ps->totalCount ++;
        if ( c==N-1 && temprsum!=ps->stdsum)
            continue;
        if ( r==N-1 && tempcsum!=ps->stdsum)
            continue;
            
        ps->i[no] = i;
        ps->remain[i] = 0;
        ps->rsum[r] = temprsum;
        ps->csum[c] = tempcsum;
        if (no==NN-1) {
            ps->partResultCount ++;
            if (exam(ps)) {
                ps->resultCount ++;
                ps->t_current = clock()- ps->t_start;
                sl_append( ps );
                print(*ps, false);
            }
        } else
        {
            msquare( ps, no + 1);
        }
        ps->remain[i] = 1;
        ps->i[no] = 0;
    }
    ps->rsum[r] = rsum;
    ps->csum[c] = csum;

}

void print(SQUARE s, int direct)
{
    int j;

    if (s.resultCount%interval==0 || (direct) ) {
        printf("%-6d[ ", s.resultCount);
        for (j = 0; j < NN; j++)
            printf("%2d ", s.i[j]);
        printf("] %ld\r\n", clock() - s.t_start);
    }
}

int exam(SQUARE *ps)
{
    int j;
    int sum1, sum2;
    
    sum1 = 0;
    sum2 = 0;

    for (j = 0; j < N; j++)
    {
        sum1 += ps->i[j * N + j];     
        sum2 += ps->i[j * N + N - 1 - j]; 
    }
    if (sum1 != ps->stdsum || ps->stdsum != sum2)
        return 0;
    else
        return 1;
}
void fileWrite( char *filename, SQUARENODE head) 
{
    FILE    *fp;
    SQUARENODE *n;
    char    line[4096], temp[1024];
    int     i;

    fopen_s( &fp, filename, "w");
    n = head.next;

    while(n) {
        sprintf( line, "%6d [ ", n->s.resultCount);
        for(i=0;i<NN;i++) {
            sprintf(temp, "%2d ", n->s.i[i]);
            strcat_s( line, sizeof(line), temp);
        } 
        strcat_s( line, sizeof(line), "] ");
        sprintf( temp, "%10d\n", n->s.t_current);
        strcat_s( line, sizeof(line), temp);
        fwrite( line, strlen(line), 1, fp);

        n = n->next;
    }

    fclose(fp);
}