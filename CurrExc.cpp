#include<iostream>
#include<cstdlib>
using namespace std;

class CurrExc{
	private:
		int d[100];
		int a[100];
	public:
		int n;
		int total;
		void Read();
		void Change(int i);
		void print();
};

void CurrExc::Read(){
	cout<<"Enter denominations(in desc order): ";
	for(int i=0;i<n;i++){
		cin>>d[i];
	}
	
	cout<<"Enter bill value: ";
	cin>>total;
}

void CurrExc::Change(int i){
	int t=total;
	int temp=i;
	
	for(int j=0;j<n;j++)a[j]=0;
	
	for(;i<n;i++){
		if(t>=d[i]){
			a[i]=t/d[i];
			t=t-(a[i]*d[i]);
		}
		if(t==0)break;
	}
	if(t!=0)Change(temp+1);
}

void CurrExc::print(){
	cout<<"Change: ";
	int tt=1;
	for(int k=0;k<n;k++){
		if(a[k]>0){
			if(tt==1){
				cout<<a[k]<<"x"<<d[k]<<" ";
				tt=0;
			}
			else cout<<"+ "<<a[k]<<"x"<<d[k]<<" ";
		}
	}
}


int main(){
	cout<<"----------------------Currency Exchange-----------------------\n";
	CurrExc ce;
	

	
	cout<<"Enter number of denominations: ";
	cin>>ce.n;
	ce.Read();
	ce.Change(0);
	ce.print();
	cout<<"\n---------------------------------------------------------\n";
}
