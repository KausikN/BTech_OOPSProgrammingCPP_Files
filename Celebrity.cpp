#include<iostream>
#include<cstdlib>
using namespace std;

class Celebrity{
    private: 
        int c[100][100];
    public:
        int n;
        int ans[100];
        void Read();
        int Find();
};

void Celebrity::Read(){
    cout<<"Enter number of people: ";
    cin>>n;
    if(n<1){
        cout<<"Invalid number of people.\n";
        Read();
        return;
    }
    for(int i=0;i<n;i++){
        cout<<"Enter the relationships of person "<<i<<": ";
        for(int j=0;j<n;j++){
            cin>>c[i][j];
            if(c[i][j]!=0 && c[i][j]!=1){
                cout<<"Invalid Inputs.\n";
                Read();
                return;
            }
        }
        ans[i]=7;		//to init ans array
    }
    
}

int Celebrity::Find(){
    int index=-1;
    int i=0,j=1;
    while(j<n){
        if(c[i][j]==1){
            ans[i]=0;
            i++;
            if(i==j)j++;
        }
        else if(c[i][j]==0){
            ans[j]=0;
            j++;
        }
    }
    for(int k=0;k<n;k++){
        //cout<<"\n"<<k<<ans[k]<<"\n";
        if(ans[k]==7){
            index=k;
        }
    }
    for(int l=0;l<n;l++){
        if(c[l][index]==0 && l!=index){
            index=-1;
            break;
        }	
        if(c[index][l]==1 && l!=index){
            index=-1;
            break;
        }		
    }
    return index;
}

int main(){
    cout<<"----------------------Celebrity Finder-----------------------\n";
    Celebrity cel;
    cel.Read();
    int ind = cel.Find();
    if(ind==-1)cout<<"There are no celebrities.\n";
    else cout<<"Person "<<ind<<" is a celebrity.\n";
    cout<<"-------------------------------------------------------------\n";
}