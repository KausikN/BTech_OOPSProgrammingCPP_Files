#include<iostream>
#include<cstdlib>
#include<time.h>
using namespace std;

float avgn=0,avgr=0;

class QuickSort{
    private: 
    public:
        int a[200];
        int a2[200];
        int n;
        int noc;
        int pivotcheck;
        void populate();
        void Refresh();
        void QSort(int beg, int end);
        int Partition(int beg, int end);
        void print(int no);
};

void QuickSort::populate(){
    srand(time(NULL));
    for(int i=0;i<n;i++){
        a[i]=rand()%100;
        a2[i]=a[i];
    }
}

void QuickSort::Refresh(){
    for(int i=0;i<n;i++){
        a[i]=a2[i];
    }
}

void QuickSort::QSort(int beg, int end){
    if(beg<end){
        int j = Partition(beg, end);
        QSort(beg, j-1);
        QSort(j+1, end);
    }
}

int QuickSort::Partition(int beg, int end){
    srand(time(NULL));
    int i=beg,j=end;
    int p;
    if(pivotcheck==0)p=beg;
    else if(pivotcheck==1)p=beg+rand()%(end-beg+1);
    int val=p;
    while(i<j){
        while(a[p]>=a[i] && i<end && ++noc){
            i++;
        }
        while(a[p]<a[j] && j>beg && ++noc){
            if(j==p+1 && i<=p)j=p-1;
            //if(j!=beg)j--;
            else j--;
            
        }
        if(i<j){
            int temp = a[i];
            a[i]=a[j];
            a[j]=temp;
        }	
    }
    int temp = a[p];
    a[p]=a[j];
    a[j]=temp;
    val=j;
    return val;
}

void QuickSort::print(int no){
    cout<<"Array "<<no<<": ";
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<"\n\n";
}

int main(){
    cout<<"----------------------Quick Sorting-----------------------\n";
    
    int nocases = 1000;
    int length = 100;
    
    QuickSort qs;
    qs.n=length;

    int shuffle=2;
    
    for(int i=0;i<nocases;i++){
        for(int u=0;u<shuffle;u++)
        qs.populate();
        
        qs.print(1);
        qs.noc = 0;
        qs.pivotcheck=0;
        qs.QSort(0,length-1);
        avgn = avgn + qs.noc;
        qs.print(2);
        
        qs.Refresh();
        
        qs.print(3);
        qs.noc = 0;
        qs.pivotcheck=1;
        qs.QSort(0,length-1);
        avgr = avgr + qs.noc;
        qs.print(4);
        
    }
    
    avgn = avgn/nocases;
    avgr = avgr/nocases;
    
    cout<<"Avg number of comparisons: \n"<<"Normal: "<<avgn<<"\n"<<"Randomized: "<<avgr<<"\n";
    cout<<"---------------------------------------------------------\n";
}