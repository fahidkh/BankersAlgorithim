#include <stdio.h>
#include <stdlib.h>

/*******************************************************

Coding Assignment 2: Banker’s Algorithm

Fahid AlKhatieb
20191501006

********************************************************/

int n,m;

int isSafeState(int Available[],int Need[][m],int Allocation[][m],int safeSequence[]){
int Finish[n];
int Work[m];
for(int i=0;i<m;i++)
    Work[i]=Available[i];

for(int i=0;i<n;i++)
    Finish[i]=0;

int proceed=1;
int k=0;

while(proceed){
    proceed=0;
    for(int i=0;i<n;i++){
        int flag=1;
        if(Finish[i]==0)
        {
            for(int j=0;j<m;j++){
                if(Need[i][j] <= Work[j]){
                    continue;
                }
                else{
                    flag=0;
                    break;
                }
            }
            if(flag==0)
                continue;
            for(int j=0;j<m;j++)
                Work[j]=Work[j]+Allocation[i][j];
            Finish[i]=1;
            safeSequence[k++]=i;
            proceed=1;
        }
        }
    }
int z;
for(z=0;z<n && Finish[z]==1;z++){
    continue;}
if(z==n)
    return 1;
else
    return 0;
}


void ResourceRequest(int Need[][m],int Allocation[][m],int Available[],int id){
int Request[m];
int i;
printf("\nEnter requested resource(vector): ");
for(i=0;i<m;i++)
    scanf("%d", &Request[i]);
for(i=0;i<m;i++){
    if(Request[i]>Need[id][i]){
        printf("\nerror condition, since process has exceeded its maximum claim\n");
        return;
    }}
    for(i=0;i<m;i++){
    if(Request[i]>Available[i]){
        printf("\nresources are not available\n");
        return;
    }}
    for(i=0;i<m;i++){
        Available[i] = Available[i]-Request[i];
        Allocation[id][i]=Allocation[id][i]+Request[i];
        Need[id][i] = Need[id][i]-Request[i];
    }
    int safeSequence[n];
    if(isSafeState(Available,Need,Allocation,safeSequence)){
        printf("SAFE State has been detected\n");
        printf("Safe Sequence is: ");
        for(int i=0;i<n;i++)
            printf("P[%d] ",safeSequence[i]);
    }

    else
        printf("NOT SAFE State has been detected");

}

void display(int Available[],int Allocation[][m],int Max[][m],int Need[][m]){

printf("\nPID\tAllocation\tMax\tNeed\n");
for(int i=0;i<n;i++){
    printf("P[%d]\t",i);
    for(int j=0;j<m;j++){
        printf("%d",Allocation[i][j]);
    }
    printf("\t\t");
    for(int j=0;j<m;j++){
        printf("%d",Max[i][j]);
    }
    printf("\t");
    for(int j=0;j<m;j++){
        printf("%d",Need[i][j]);
    }
    printf("\n");
}
    printf("\nAvailable Resources are:  ");
    for(int i=0;i<m;i++){
        printf(" %d", Available[i]);
    }
    printf("\n");
}

int main()
{
    printf("enter the number of processes: ");
    scanf("%d",&n);

    printf("\nenter the number of resources: ");
    scanf("%d",&m);

    int Available[m];
    int Max[n][m];
    int Allocation[n][m];
    int Need[n][m];
    int safeSequence[n];

    printf("\n*******************************\n");
    for(int i=0;i<n;i++){
    printf("\nEnter process[%d] info:\n", i);

    printf("Enter No. of Allocated Resources for this process(vector): ");
    for(int j=0;j<m;j++)
    scanf("%d", &Allocation[i][j]);

    printf("Enter maximum requests vector for this process: ");
    for(int j=0;j<m;j++)
        scanf("%d", &Max[i][j]);
    }
    printf("Enter Available Resources: ");
    for(int i=0;i<m;i++){
        scanf("%d", &Available[i]);
    }
    for(int i=0;i<n;i++){
            for(int j=0;j<m;j++)
        Need[i][j]=Max[i][j]-Allocation[i][j];
     }

    display(Available,Allocation,Max,Need);
    if(isSafeState(Available,Need,Allocation,safeSequence)){
        printf("The System is in SAFE State\n");
        printf("Safe Sequence is: ");
        for(int i=0;i<n;i++)
            printf("P[%d] ",safeSequence[i]);
    }

    else
        printf("The System is not in Safe State");

    int pid;
    printf("\nChoose a process to determine if it should be assigned the requested resources or not(enter process ID): ");
    scanf("%d",&pid);
    ResourceRequest(Need,Allocation,Available,pid);
    return 0;
}
