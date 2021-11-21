#include<iostream>
#include<cstdlib>
using namespace std;

class i_Min{
    private:
    public:
        int t[5];
        int x[200];
        int x2[200];
        int s;
        void Read();
        int Select(int a[200], int beg, int end, int k);
        int Partition(int a[200], int beg, int end, int n, int p);
        void ISort();
        void print(int a[200],int n);
        void Refresh();
};

void i_Min::Read(){
    cout<<"Enter Number of Hits for each: ";
    for(int i=0;i<s;i++){
        cin>>x[i];
        x2[i]=x[i];
    }
}

void i_Min::Refresh(){
    for(int i=0;i<s;i++){
        x[i]=x2[i];
    }
}

void i_Min::ISort(){
    int n=5;
    for(int i=1;i<n;i++){
        for(int j=i;j>0;j--){
            if(t[j-1]>t[j]){
                int temp=t[j];
                t[j]=t[j-1];
                t[j-1]=temp;
            }
            else break;
        }
    }
    //print(t,5);
}

int i_Min::Select(int a[200], int beg, int end, int k){
    int n = end-beg+1;
    if(n>=5){
        int medians[200];
        int mn=0;
        int i=beg;
        for(i=beg;i<=end+1-5;i=i+5){
            for(int j=i;j<i+5;j++){
                t[j-i]=a[j];
            }
            ISort();
            medians[mn] = t[2];
            //cout<<"\n\n"<<t[2]<<"\n\n";
            mn++;
            //cout<<"\n\n\nMEdno "<<mn<<"\n\n\n";
        }
        if(n%5!=0){
            i = i-5 + 1;
            for(int j=0;j<n%5;j++){
                t[j]=a[i+j];
            }
            ISort();
            medians[mn] = t[2];
            //cout<<"\n\nHi"<<t[2]<<"\n\n";
            mn++;
            //cout<<"\n\n\nMEdno "<<mn<<"\n\n\n";
        }
        //cout<<"\n\n\nMEdno "<<mn<<"\n\n\n";
        if(mn%2==1)mn++;
        //cout<<"\n\n\nMEdno "<<mn<<"\n\n\n";
        int medomed = Select(medians,0,mn-1,mn/2);
        //cout<<"\nMedomed - "<<medomed<<"\n";
        int pos = Partition(a,beg,end,n,medomed);
        for(int i=0;i<s;i++){
            a[i]=x[i];
        }s
        //print(a,s);
        //cout<<"pos:"<<pos<<" k:"<<k;
        if(pos==k){
            if(beg==0)cout<<"The "<<k+1<<"th smallest is "<<x[pos]<<"\n";
            return pos;
        }
        else if(pos>k)return Select(a,beg,pos-1,k);
        else return Select(a,pos+1,end,k);
    }
    else {//cout<<"BLAh";
        for(int j=beg;j<end+1;j++){
                t[j-beg]=a[j];
        }
        
        
        for(int i=1;i<n;i++){
            for(int j=i;j>0;j--){
                if(t[j-1]>t[j]){
                    int temp=t[j];
                    t[j]=t[j-1];
                    t[j-1]=temp;
                }
                else break;
            }
        }
        //print(t,n);
        int pp=beg;
        int hhh=k-beg;
        //cout<<hhh;
        /*for(int i=beg;i<end+1;i++){
            if(t[hhh]==a[i]){
                cout<<"i:"<<i;
                return i;
            }
        }*/
        for(int i=0;i<s;i++){
            if(t[hhh]==x2[i]){
                cout<<"The "<<k+1<<"th smallest is "<<x2[i]<<"\n";
                return i;
            }
        }
    }
}

int i_Min::Partition(int a[200], int beg, int end, int n, int piv){
    /*for(int i=beg;i<end+1;i++){
        if(piv==a[i]){
            p=i;
            break;
        }
    }*/
    cout<<piv;
    int p=piv;
    int temp=a[p];//cout<<"\nHII\n";
    a[p]=a[beg];
    a[beg]=temp;

    int i=beg+1,j=end;
    p=beg;
    int val=p;
    while(i<j){
        while(a[p]>=a[i] && i<end){
            i++;
        }
        while(a[p]<a[j] && j>beg){
            j--;
            
        }
        if(i<j){
            temp = a[i];
            a[i]=a[j];
            a[j]=temp;
        }	
    }
    temp = a[p];
    a[p]=a[j];
    a[j]=temp;
    val=j;
    //cout<<"AAAAAAAAAAa";
    for(int i=0;i<n;i++){
        x[i]=a[i];
    }
    return val;
}

void i_Min::print(int a[200],int n){
    cout<<"\n";
    for(int i=0;i<n;i++){
        cout<<a[i]<<" ";
    }
    cout<<"\n";
}

int main(){
    cout<<"----------------------k'th Smallest Hit-----------------------\n";
    i_Min imin;
    

    
    cout<<"Enter number of websites: ";
    cin>>imin.s;
    imin.Read();
    int k=0;
    cout<<"Enter the value of k: ";
    cin>>k;
    //for(int i=0;i<k;i++){
        //imin.print(imin.x,imin.s);
        //imin.Refresh();
        //imin.print(imin.x,imin.s);
        int pos = imin.Select(imin.x,0,(imin.s)-1,k-1);
        //cout<<"\nPosition: "<<pos<<"\n";
        
        //imin.print(imin.x,imin.s);
    //}
    cout<<"---------------------------------------------------------\n";
}