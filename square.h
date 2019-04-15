#define     MAXNN   100
#define     MAXN    10

typedef struct square
{
    int i[MAXNN];
    int remain[MAXNN];
    int totalCount, resultCount, partResultCount;
    int t_start, t_current;
    int stdsum;
    int rsum[MAXN],csum[MAXN];
} SQUARE;

typedef struct squarelist {
    SQUARE      s;
    struct squarelist  *next;
} SQUARENODE;

int     exam(SQUARE *ps);
void    print(SQUARE s, int direct);
void    msquare( SQUARE *ps, int no);
void    fileWrite( char *filename, SQUARENODE head) ;
void    initSquare( SQUARE  *ps);

SQUARENODE *sl_append(SQUARE *ps); 
void    sl_free( SQUARENODE head);