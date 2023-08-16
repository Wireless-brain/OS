#include<stdio.h>
struct process
{
    int pid;
    int at;
    int bt;
    int ct;
    int tt;
    int wt;
    int stat;
}p[10],temp;
struct gchart
{
    int pid;
    int end;
}g[10];
int n,t=0,ind[5],in=0,k=0,strt=0;
float tt=0,wt=0;

int printP()
{
    int i;
    printf("\n\t  \tAT\tBT ");
    for (i=0;i<n;i++)
    {
        printf("\n\tP%d\t%d\t%d ",p[i].pid,p[i].at,p[i].bt);
    }
    printf("\n");
    return 0;
}
int printPP()
{
    int i;
    printf("\n\t  \tAT\tBT\tCT\tWT\tTT ");
    for (i=0;i<n;i++)
    {
        printf("\n\tP%d\t%d\t%d\t%d\t%d\t%d ",p[i].pid,p[i].at,p[i].bt,p[i].ct,p[i].wt,p[i].tt);
    }
    printf("\n");
    return 0;
}
int chart()
{
    int i;
    printf("\n\tGANTT CHART\n");
    printf("\n\t");
    for (i=0;i<(5*k)+1;i++)
    {
        printf("-");
    }
    printf("\n\t|");
    for (i=0;i<k;i++)
    {
        if (g[i].pid==-1)
        {
            printf(" ID |");
        }
        else
        {
            printf(" P%d |",g[i].pid);
        }
    }
    printf("\n\t");
    for (i=0;i<(5*k)+1;i++)
    {
        printf("-");
    }
    printf("\n\t0");
    for (i=0;i<k;i++)
    {
        printf("    %d",g[i].end);
    }
    printf("\n");
    return 0;
}
int makeChart()
{
    int i,t,minbt,min;
    minbt=p[ind[0]].bt;
    min=ind[0];
    for (i=0;i<in;i++)
    {
        if (p[ind[i]].bt < minbt)
        {
            minbt=p[ind[i]].bt;
            min=ind[i];
        }
    }
    if (strt==0)
    {
        p[min].ct=p[min].at+p[min].bt;
        p[min].tt=p[min].bt;
        p[min].wt=0;
        if (p[min].at!=0)
        {
            g[k].pid=-1;
            g[k].end=p[min].at;
            k++;
            g[k].pid=p[min].pid;
            g[k].end=p[min].ct;
            t=g[k].end;
            k++;
        }
        else
        {
            g[k].pid=p[min].pid;
            g[k].end=p[min].ct;
            t=g[k].end;
            k++;
        }
        strt=1;
    }
    else
    {
        if (p[min].at>g[k-1].end)
        {
            g[k].pid=-1;
            g[k].end=p[min].at;
            k++;
            p[min].tt=p[min].bt;
            p[min].wt=p[min].tt-p[min].bt;
            p[min].ct=g[k-1].end+p[min].bt+(p[min].at-g[k-1].end);
            g[k].pid=p[min].pid;
            g[k].end=p[min].ct;
            t=g[k].end;
            k++;
        }
        else
        {
            p[min].ct=g[k-1].end+p[min].bt;
            p[min].tt=p[min].ct-p[min].at;
            p[min].wt=p[min].tt-p[min].bt;
            g[k].pid=p[min].pid;
            g[k].end=p[min].ct;
            t=g[k].end;
            k++;
        }
    }
    wt+=p[min].wt;
    tt+=p[min].tt;
    p[min].stat=1;
    return t;
}

int main()
{
    int i,j,c=0,t=0,flag=0;
    printf("\n\tEnter the number of processes: ");
    scanf("%d",&n);
    printf("\n\tEnter processes details: ");
    for (i=0;i<n;i++)
    {
        printf("\n\tEnter process ID: ");
        scanf("%d",&p[i].pid);
        printf("\n\tEnter the arrival time of P%d: ",p[i].pid);
        scanf("%d",&p[i].at);
        printf("\n\tEnter the burst time of P%d: ",p[i].pid);
        scanf("%d",&p[i].bt);
        p[i].stat=0;
    }
    printP();
    while(c==0)
    {
        for (i=0;i<n;i++)
        {
            if (p[i].stat==0 && p[i].at<=t)
            {
                ind[in]=i;
                in++;
            }
        }
        t=makeChart();
        in=0;
        for (i=0;i<n;i++)
        {
            if (p[i].stat==0)
            {
                flag=1;
            }
        }
        if (flag==0)
        {
            c=1;
        }
        flag=0;
    }
    printPP();
    chart();
    printf("\n\tTotal waiting time: %.2f",wt);
    printf("\n\tTotal turn around time: %.2f",tt);
    printf("\n\tAvg waiting time: %.2f",wt/n);
    printf("\n\tAvg turn around time: %.2f\n\n",tt/n);
    return 0;
}

/*OUTPUT

        Enter the number of processes: 4

        Enter processes details:
        Enter process ID: 1

        Enter the arrival time of P1: 0

        Enter the burst time of P1: 7

        Enter process ID: 2

        Enter the arrival time of P2: 1

        Enter the burst time of P2: 5

        Enter process ID: 3

        Enter the arrival time of P3: 3

        Enter the burst time of P3: 2

        Enter process ID: 4

        Enter the arrival time of P4: 4

        Enter the burst time of P4: 3

                AT      BT
        P1      0       7
        P2      1       5
        P3      3       2
        P4      4       3

                AT      BT      CT      WT      TT
        P1      0       7       7       0       7
        P2      1       5       17      11      16
        P3      3       2       9       4       6
        P4      4       3       12      5       8

        GANTT CHART

        ---------------------
        | P1 | P3 | P4 | P2 |
        ---------------------
        0    7    9    12    17

        Total waiting time: 20.00
        Total turn around time: 37.00
        Avg waiting time: 5.00
        Avg turn around time: 9.25

*/