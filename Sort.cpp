#include<iostream>
#include<cstdlib>
using namespace std;

class Sort{
	private: 
		int x[200];
		int x2[200];
	public:
		int n;
		void populate();
		void Refresh();
		int BSort();
		int ISort();
		int SSort();
		void print();
};

void Sort::populate(){
	for(int i=0;i<n;i++){
		x[i]=rand()%100;
		x2[i]=x[i];
	}
}

void Sort::Refresh(){
	for(int i=0;i<n;i++){
		x[i]=x2[i];
	}
}

int Sort::BSort(){
	int no=0;
	for(int i=1;i<n+1;i++){
		int tcheck=0;
		for(int j=0;j<n-i;j++){
			no++;
			if(x[j]>x[j+1]){
				int temp=x[j];
				x[j]=x[j+1];
				x[j+1]=temp;
				tcheck=1;
			}
		}
		if(tcheck==0)break;
	}
	Refresh();
	return no;
}

int Sort::ISort(){
	int no=0;
	for(int i=1;i<n;i++){
		for(int j=i;j>0;j--){
			no++;
			if(x[j-1]>x[j]){
				int temp=x[j];
				x[j]=x[j-1];
				x[j-1]=temp;
			}
			else break;
		}
	}
	Refresh();
	return no;
}

int Sort::SSort(){
	int no=0;
	for(int i=0;i<n;i++){
		int max=x[0];
		int imax=0;
		for(int j=1;j<n-i;j++){
			if(x[j]>max){
				max=x[j];
				imax=j;
			}
			no++;
		}
		int temp=x[n-i-1];
		x[n-i-1]=x[imax];
		x[imax]=temp;
	}
	Refresh();
	return no;
}

void Sort::print(){
	cout<<"The values in old array are: 	";
	for(int i=0;i<n;i++){
		cout<<x2[i]<<" ";
	}
	cout<<"\n";
	cout<<"The values in sorted array are:	";
	for(int j=0;j<n;j++){
		cout<<x[j]<<" ";
	}
	cout<<"\n";
}

int main(){
	cout<<"----------------------Sorting-----------------------\n";
	int cb[20],ci[20],cs[20];
	float ab=0,ai=0,as=0;
	Sort s;
	s.n=5;
	s.populate();
	cout<<"Case	|	BSort	|	ISort	|	SSort\n";
	cout<<"-----------------------------------------------------\n";
	for(int i=1;i<21;i++){
		s.n=s.n+5;
		s.populate();
		
		cb[i-1]=s.BSort();
		ci[i-1]=s.ISort();
		cs[i-1]=s.SSort();
		
		ab=ab+(cb[i-1]/s.n);
		ai=ai+(ci[i-1]/s.n);
		as=as+(cs[i-1]/s.n);
		
		cout<<""<<i<<"	|	"<<cb[i-1]<<"	|	"<<ci[i-1]<<"	|	"<<cs[i-1]<<"\n";
	}
	cout<<"----------------------------------------------------\n";
	
	ab=ab/20;
	ai=ai/20;
	as=as/20;
	
	cout<<"Avg number of comparisons:\nBSort: "<<ab<<"\nISort: "<<ai<<"\nSSort: "<<as<<"\n";
	
}
