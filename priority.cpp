#include<iostream>
#define max 20
using namespace std;

int main(){
	struct process{
		int id,AT,TAT,BT,WT,ST,CT,priority;
	}p[20];
	int n,i=0,cur_time=0,completed=0,min_index=-1,is_comp[max];
	float ATA,AWT;
	cout<<"\nEnter no pf processes:";
	cin>>n;
	for(int i=0;i<n;i++){
		p[i].id=i+1;
		cout<<"\nEnter burst time of p["<<i+1<<"]:";
		cin>>p[i].BT;
		cout<<"\nEnter arrival time of p["<<i+1<<"]:";
		cin>>p[i].AT;
		cout<<"\nEnter priority pf p["<<i+1<<"]:";
		cin>>p[i].priority;
		is_comp[i]=0;
	}
	cout<<"Gantt chart"<<endl;
	while(completed!=n){
		int min=-1;
		for(int i=0;i<n;i++){
			if(p[i].AT<=cur_time && is_comp[i]==0){
				if(p[i].priority>min){
					min=p[i].priority;
					min_index=i;
				}
				if(p[i].priority==min){
					if(p[i].AT<p[min_index].AT){
						min=p[i].priority;
						min_index=i;
					}
				}
			}
		}
		if(min_index==-1){
			cur_time++;
		}
		else{
			p[min_index].ST=cur_time;
			p[i].CT=p[min_index].ST+p[min_index].BT;
			p[min_index].TAT=p[i].CT-p[min_index].AT;
			p[min_index].WT=p[min_index].TAT-p[min_index].BT;
			is_comp[min_index]=1;
			ATA+=p[min_index].TAT;
			AWT+=p[min_index].WT;
			cur_time=p[i].CT;
			i++;
			completed++;
			cout<<"|   P"<<p[min_index].id<<"\t";
		}
	}
	cout<<"|";
	cout<<endl<<"0\t";
	for(int i=0;i<n;i++){
		cout<<p[i].CT<<"\t";
	}
	cout<<endl;
	cout<<"\nTURN AROUND TIME";
	for(int i=0;i<n;i++){
		cout<<"\nTurn around time of p["<<i+1<<"] is:"<<p[i].TAT;
	}
	ATA=ATA/n;
	cout<<"\nWAITING TIME";
	for(int i=0;i<n;i++){
		cout<<"\nWating time of p["<<i+1<<"] is:"<<p[i].WT;
	}
	AWT=AWT/n;
	cout<<"\nAverage TAT:"<<ATA;
	cout<<"\nAverage WT:"<<AWT;
	return 0;
}

//INPUT:
Enter no pf processes:2

Enter burst time of p[1]:1

Enter arrival time of p[1]:1

Enter priority pf p[1]:1

Enter burst time of p[2]:1

Enter arrival time of p[2]:1

Enter priority pf p[2]:1


//OUTPUT:

Gantt chart
|   P1  |   P2  |
0       2       3

TURN AROUND TIME
Turn around time of p[1] is:1
Turn around time of p[2] is:2
WAITING TIME
Wating time of p[1] is:0
Wating time of p[2] is:1
Average TAT:1.5
Average WT:0.5