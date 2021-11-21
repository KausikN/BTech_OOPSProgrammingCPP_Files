#include<iostream>
#include<cstdlib>
using namespace std;

class DosaFlip{
    private: 
        int d[100];
    public:
        int n;
        void Read();
        int Flip(int fin);
        int Find();
        void print();
};

void DosaFlip::Read(){
    cout<<"Enter number of Dosas: ";
    cin>>n;
    if(n<1){
        cout<<"Invalid number of dosas.\n";
        Read();
        return;
    }
    cout<<"Enter the sizes of Dosas: ";
    for(int i=0;i<n;i++){
        cin>>d[i];
    }
}

int DosaFlip::Flip(int fin){
    int max=d[0];
    int beg=0;
    int end=0;
    for(int k=0;k<fin;k++){
        if(max<d[k]){
            max=d[k];
            end=k;
        }
    }
    if(end==fin-1)return 0;
    else if(end==0){
        for(int j=0;j<fin/2;j++){
            int temp=d[j];
            d[j]=d[fin-1-j];
            d[fin-1-j]=temp;
        }
        return 1;
    }
    else {
        for(int i=0;i<(end-beg+1)/2;i++){
            int temp=d[i];
            d[i]=d[end-beg-i];
            d[end-beg-i]=temp;
        }
        for(int j=0;j<fin/2;j++){
            int temp=d[j];
            d[j]=d[fin-1-j];
            d[fin-1-j]=temp;
        }
        return 2;
    }
}

int DosaFlip::Find(){
    int numflip=0;
    for(int i=0;i<n;i++){
        numflip=numflip+Flip(n-i);
    }
    return numflip;
}

void DosaFlip::print(){
    for(int i=0;i<n;i++){
        cout<<d[i]<<" ";
    }
    cout<<"\n";
}

int main(){
    cout<<"----------------------Dosa Flipper Problem-----------------------\n";
    DosaFlip df;
    df.Read();
    int num = df.Find();
    cout<<"Number of Flips required is "<<num<<". \n";
    cout<<"Flipped order: ";
    df.print();
    cout<<"-----------------------------------------------------------------\n";
}