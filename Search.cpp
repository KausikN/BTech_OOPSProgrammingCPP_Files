#include<iostream>
#include<cstdlib>
using namespace std;

class Search{
    private: 
        int array[100];
    public:
        int size;
        void input();
        int LS(int x);
        int BS(int x);
};

void Search::input(){
    for(int i=0;i<size;i++){
        array[i]=rand()%100;
    }
}

int Search::LS(int x){
    int nol=0;
    for(int i=0;i<size;i++){
        nol++;
        if(array[i]==x)return nol;
    }
    return nol;
}

int Search::BS(int x){

    //Sort
    for(int i=1;i<size;i++){
        for(int j=i;j>0;j--){
            if(array[j-1]>array[j]){
                int temp=array[j];
                array[j]=array[j-1];
                array[j-1]=temp;
            }
            else break;
        }
    }
    //Sorts

    int nob=0;
    int s=0,e=size-1,m;
    m=(s+e)/2;
    while(s<=e){
        nob++;
        m=(s+e)/2;
        if(x==array[m])return nob;
        else if(x>array[m])s=m+1;
        else if(x<array[m])e=m-1;
    }
    return nob;
}

int main(){
    cout<<"----------------------Search-----------------------\n";
    
    float al=0;
    float ab=0;
    int x=0;
    int cases=1000;
    
    Search s;
    s.size=100;
    cout<<"Enter value to search: ";
    cin>>x;
    for(int i=0;i<cases;i++){
        s.input();
        al=al+s.LS(x);
        ab=ab+s.BS(x);	
        //cout<<s.LS(x)<<" , "<<s.BS(x)<<"\n";
    }
    
    al=al/cases;
    ab=ab/cases;
    
    cout<<"Avg number of comparisons:\nLinear Search: "<<al<<"\nBinary Search: "<<ab<<"\n";
    cout<<"-----------------------------------------------------\n";
    return 0;
}