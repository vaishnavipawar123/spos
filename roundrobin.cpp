#include<iostream>
using namespace std;
class rr
{
    public:
        string pr[20];
        int n,tq,bt[20];
        string temp[20];
        int tempbt[20],ttime[20];
        int k;
        void ganttchart(string pr[], int bt[], int tq, int n)
        {
            
            string remainpr[20];
            int remainbt[20];
            int btime;
            tempbt[0]=0;
            for(int i=0;i<n;i++)
            {
                remainpr[i]=pr[i];
            }
            for(int i=0;i<n;i++)
            {
                remainbt[i]=bt[i];
            }
            for(int i=0,j=n;i!=j;i++)
            {
                if(remainbt[i]<=tq)
                {
                    temp[i]=remainpr[i];
                    tempbt[i+1]=tempbt[i]+remainbt[i];
                }
                else
                {
                    btime=remainbt[i]-tq;     
                    temp[i]=remainpr[i];
                    tempbt[i+1]=tempbt[i]+tq;
                    remainpr[j]=remainpr[i];
                    remainbt[j]=btime;
                    j++;
                    k=j;

                }
            
            }
            cout<<"\n Gantt Chart"<<endl;
            cout<<"   ";
            for(int i=0;i<k;i++)
            {
                cout<<temp[i]<<"      ";
            }
            cout<<endl;
            for(int i=0;i<=k;i++)
            {
                cout<<tempbt[i]<<"      ";
            }
        }
        void turnaround(string pr[], int n)
        {
            int AT =0;
            int tt=0;
            int sum=0;
            cout<<"\n"<<endl;
            for(int i=0;i<n;i++)
            {
                for(int j=0;j<k;j++)
                {
                    if(pr[i]==temp[j])
                    {
                        tt=tempbt[j+1]-AT;
                    }
                }
                ttime[i]=tt;
                sum=sum+tt;
                cout<<"Turn Around time of "<<pr[i]<<" is:"<<tt<<endl;

            }
            cout<<"\nAverage turnaround time ="<<sum/n;
        }
        void waiting(string pr[], int bt[], int n)
        {
            int sum1=0;
            int wt;
            cout<<"\n"<<endl;
            for(int i=0;i<n;i++)
            {
                wt=ttime[i]-bt[i];
                cout<<"Waiting time of "<<pr[i]<<" is: "<<wt<<endl;
                sum1=sum1+wt;

            }
            cout<<"\n Average waiting time = "<<sum1/n;
        }
    
    

};
//void rr::ganttchart(string pr[], int bt[], int tq, int n)

int main()
{
    rr obj;

    string pr[20];
    int n,tq,bt[20];
    cout<<"ROUND ROBIN"<<endl;
    cout<<"enter total number of process: ";
    cin>>n;
    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter processes["<<i+1<<"] : ";
        cin>>pr[i];
    }
    for(int i=0;i<n;i++)
    {
        cout<<"\nEnter B. Time of "<<pr[i]<<" : ";
        cin>>bt[i];
    }
    cout<<"\nenter time quantum: ";
    cin>>tq;
    cout<<"\nProceses"<<"\tB.Time"<<"\tTime quantum"<<endl;
    for(int i=0;i<n;i++)
    {
        cout<<pr[i]<<"\t\t"<<bt[i]<<"\t\t"<<tq<<endl;
    }
    obj.ganttchart(pr,bt,tq,n);
    obj.turnaround(pr,n);
    obj.waiting(pr,bt,n);

    return 0;
}



//INPUT:
ROUND ROBIN SCHEDULING
Enter total number of processes: 3

Enter process name [1]: P1
Enter Burst Time of P1: 10

Enter process name [2]: P2
Enter Burst Time of P2: 5

Enter process name [3]: P3
Enter Burst Time of P3: 8

Enter Time Quantum: 3

Processes   Burst Time   Time Quantum
P1          10          3
P2          5           3
P3          8           3


//OUTPUT:
Gantt Chart
 P1 P2 P3 P1 P3 

Turnaround time of P1 is: 12
Turnaround time of P2 is: 3
Turnaround time of P3 is: 10

Average turnaround time = 8.33333
Waiting time of P1 is: 2
Waiting time of P2 is: 0
Waiting time of P3 is: 2

Average waiting time = 1.33333

