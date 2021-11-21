#include<iostream>
#include<cstdlib>
using namespace std;

class MCSSS{
    private: 
        int f[100];
        int s[100];
    public:
        int n;
        int fi[2],si[2];
        void Read();
        int Bruteforce(int person);
        int Incremental(int person);
        int DivNConquer(int person,int beg,int end);
        int Pruning(int person);
        void print(int mf,int ms);
};

void MCSSS::Read(){
    cout<<"Enter Length of DNA Sequence: ";
    cin>>n;
    cout<<"Enter DNA Sequence of Father: ";
    char temp;
    for(int i=0;i<n;i++){
        cin>>temp;
        if(temp=='A')f[i]=2;
        else if(temp=='C')f[i]=1;
        else if(temp=='G')f[i]=-1;
        else if(temp=='T')f[i]=-2;
        if(temp=='a')f[i]=2;
        else if(temp=='c')f[i]=1;
        else if(temp=='g')f[i]=-1;
        else if(temp=='t')f[i]=-2;
    }
    cout<<"Enter DNA Sequence of Son: ";
    for(int j=0;j<n;j++){
        cin>>temp;
        if(temp=='A')s[j]=2;
        else if(temp=='C')s[j]=1;
        else if(temp=='G')s[j]=-1;
        else if(temp=='T')s[j]=-2;
        if(temp=='a')s[j]=2;
        else if(temp=='c')s[j]=1;
        else if(temp=='g')s[j]=-1;
        else if(temp=='t')s[j]=-2;
    }
    
}

int MCSSS::Bruteforce(int person){		//person=0 -- Father		||		person=1 -- Son
    int msum=0;
    for(int i=0;i<n;i++){
        for(int j=i;j<n;j++){
            int sum=0;
            for(int k=i;k<=j;k++){
                if(person==0)sum=sum+f[k];
                if(person==1)sum=sum+s[k];
            }
            if(msum<sum){
                msum=sum;
                if(person==0){
                    fi[0]=i;
                    fi[1]=j;
                }
                if(person==1){
                    si[0]=i;
                    si[1]=j;
                }
            }
        }
    }
    return msum;
}

int MCSSS::Incremental(int person){
    int msum=0;
    for(int i=0;i<n;i++){
        int sum=0;
        for(int j=i;j<n;j++){
            if(person==0)sum=sum+f[j];
            if(person==1)sum=sum+s[j];
            if(msum<sum){
                msum=sum;
                if(person==0){
                    fi[0]=i;
                    fi[1]=j;
                }
                if(person==1){
                    si[0]=i;
                    si[1]=j;
                }
            }
        }
    }
    return msum;
}

int MCSSS::DivNConquer(int person,int beg,int end){
    int mid=(beg+end)/2;
    if(beg==end){
        if(person==0)return f[beg];
        if(person==1)return s[beg];
    }
    int LS = DivNConquer(person,beg,mid);
    int RS = DivNConquer(person,mid+1,end);
    
    int sum=0,rosum=0,losum=0,i1=mid,i2=mid;
    for(int i=mid;i<n;i++){			//changed to end from n
        if(person==0)sum=sum+f[i];
        if(person==1)sum=sum+s[i];
        if(sum>rosum){
            rosum=sum;
            i2=i;
        }
    }
    sum=0;
    for(int j=mid-1;j>=beg;j--){
        if(person==0)sum=sum+f[j];
        if(person==1)sum=sum+s[j];
        if(sum>losum){
            losum=sum;
            i1=j;
        }
    }
    
    int MS=losum+rosum;
    if(beg==mid){
        beg=-1;
        mid=-1;
    }
    if(mid+1==end){
        mid=-2;
        end=-1;
    }
    if(i1==i2){
        i1=-1;
        i2=-1;
    }
    if(LS>=MS && LS>=RS){
        if(person==0){
            fi[0]=beg;
            fi[1]=mid;
        }
        if(person==1){
            si[0]=beg;
            si[1]=mid;
        }
        return LS;
    }
    else if(MS>=LS && MS>=RS){
        if(person==0){
            fi[0]=i1;
            fi[1]=i2;
        }
        if(person==1){
            si[0]=i1;
            si[1]=i2;
        }
        return MS;
    }
    else if(RS>=MS && RS>=LS){
        if(person==0){
            fi[0]=mid+1;
            fi[1]=end;
        }
        if(person==1){
            si[0]=mid+1;
            si[1]=end;
        }
        return RS;
    }
}

int MCSSS::Pruning(int person){
    int csum=0,msum=0,i1=0,i2=0;
    for(int i=0;i<n;i++){
        if(person==0)csum=csum+f[i];
        if(person==1)csum=csum+s[i];
        if(csum>msum){
            msum=csum;
            i2=i;
            if(person==0){
                fi[0]=i1;
                fi[1]=i2;
            }
            if(person==1){
                si[0]=i1;
                si[1]=i2;
            }
        }
        else if(csum<0){
            csum=0;
            i1=i+1;
        }
    }
    return msum;
}

void MCSSS::print(int mf,int ms){
    char temp;
    
    cout<<"Optimal Sub-Sequence of Father: ";
    if(fi[0]<=-1 || fi[1]<=-1)cout<<"Null";
    else { cout<<"\n"<<fi[0]<<"\n"<<fi[1]<<"\n";
        for(int i=fi[0];i<=fi[1];i++){
            if(f[i]==2)temp='A';
            else if(f[i]==1)temp='C';
            else if(f[i]==-1)temp='G';
            else if(f[i]==-2)temp='T';
            cout<<temp<<" ";
        }
    }
    cout<<"\n";
    cout<<"Max value of Father's DNA: "<<mf;
    
    cout<<"\n";
    
    cout<<"Optimal Sub-Sequence of Son: ";
    if(si[0]<=-1 || si[1]<=-1)cout<<"Null";
    else {
        for(int i=si[0];i<=si[1];i++){
            if(s[i]==2)temp='A';
            else if(s[i]==1)temp='C';
            else if(s[i]==-1)temp='G';
            else if(s[i]==-2)temp='T';
            cout<<temp<<" ";
        }
    }
    cout<<"\n";
    cout<<"Max value of Son's DNA: "<<ms;
    
    cout<<"\n";
}

int main(){
    cout<<"----------------------DNA Sequence Analyser-----------------------\n";
    MCSSS s;
    s.n=20;
    s.Read();
    int ms=0,mf=0;
    
    s.fi[0]=-1;
    s.fi[1]=-1;
    s.si[0]=-1;
    s.si[1]=-1;
    
    cout<<"Brute Force: \n";
    mf=s.Bruteforce(0);
    ms=s.Bruteforce(1);
    s.print(mf,ms);
    cout<<"\n";
    
    cout<<"Incremental: \n";
    mf=s.Incremental(0);
    ms=s.Incremental(1);
    s.print(mf,ms);
    cout<<"\n";
    
    cout<<"Divide and Conquer: \n";
    mf=s.DivNConquer(0,0,s.n);
    ms=s.DivNConquer(1,0,s.n);
    s.print(mf,ms);
    cout<<"\n";
    
    cout<<"Pruning: \n";
    mf=s.Pruning(0);
    ms=s.Pruning(1);
    s.print(mf,ms);
    cout<<"\n";
    
    if(mf-ms>=-10 || mf-ms<=10)cout<<"The person is the father of the child.\n";
    else cout<<"The person is not the father of the child.\n";
    
    cout<<"------------------------------------------------------------\n";
}