#include<iostream>
#include<cstdlib>
using namespace std;

class Knapsack{
	private:
		int w[100];
		float p[100];
		float tp[100];
		int tw[100];
		float pw[100];
		int M;
		float select[100];
	public:
		int n;
		void Read();
		float P();
		float PW();
		float Frac();
		void print(int pr);
		void ISort(int c);
		
};

////////////////////////////////////////////////////

void Knapsack::ISort(int c){

	for(int i=0;i<n;i++){
		pw[i]=p[i]/w[i];
		tp[i]=p[i];
		tw[i]=w[i];
	}

	if(c==1){
		for(int i=1;i<n;i++){
			for(int j=i;j>0;j--){
				if(tp[j-1]>tp[j]){
					int temp=tp[j];
					tp[j]=tp[j-1];
					tp[j-1]=temp;
				
					int temp2=tw[j];
					tw[j]=tw[j-1];
					tw[j-1]=temp2;
				}
				else break;
			}
		}
	}
	else if(c==2){
	
		for(int i=1;i<n;i++){
			for(int j=i;j>0;j--){
				if(pw[j-1]>pw[j]){
					int temp=pw[j];
					pw[j]=pw[j-1];
					pw[j-1]=temp;
				
					int temp2=tw[j];
					tw[j]=tw[j-1];
					tw[j-1]=temp2;
					
					int temp3=tp[j];
					tp[j]=tp[j-1];
					tp[j-1]=temp3;
				}
				else break;
			}
		}
	}
	
	for(int j=0;j<n/2;j++){
			int temp=tp[j];
			tp[j]=tp[n-1-j];
			tp[n-1-j]=temp;
				
			int temp2=tw[j];
			tw[j]=tw[n-1-j];
			tw[n-1-j]=temp2;
			
			int temp3=pw[j];
			pw[j]=pw[n-1-j];
			pw[n-1-j]=temp3;
	}
	
	
	/*cout<<"\n\nMarker: ";
	for(int i=0;i<n;i++){
		cout<<""<<tp[i]<<"\n";
	}*/
	
}

////////////////////////////////////////////////////

void Knapsack::Read(){

	cout<<"Enter max weight carryable: ";
	cin>>M;

	cout<<"Enter weights: ";
	for(int i=0;i<n;i++){
		cin>>w[i];
		tw[i]=w[i];
	}
	
	cout<<"Enter prices: ";
	for(int i=0;i<n;i++){
		cin>>p[i];
		tp[i]=p[i];
	}
	
	for(int i=0;i<n;i++){
		pw[i]=p[i]/w[i];
	}
}

float Knapsack::P(){
	ISort(1);
	for(int j=0;j<n;j++)select[j]=0;
	
	int m=M;
	int pr=0;
	int KW=0;
	
	for(int i=0;i<n;i++){
		if(m>=tw[i]){
			select[i]=1;
			m=m-tw[i];
			pr=pr+tp[i];
			KW=KW+tw[i];
			cout<<"\n"<<KW<<" \n";
		}
	}
	return pr;
}

float Knapsack::PW(){
	ISort(2);
	for(int j=0;j<n;j++)select[j]=0;
	
	int m=M;
	int pr=0;
	int KW=0;
	
	for(int i=0;i<n;i++){
		if(m>=tw[i]){
			select[i]=1;
			m=m-tw[i];
			pr=pr+tp[i];
			KW=KW+tw[i];
			cout<<"\n"<<KW<<" \n";
		}
	}
	return pr;
}

float Knapsack::Frac(){
	ISort(2);
	for(int j=0;j<n;j++)select[j]=0;
	
	int m=M;
	float KW=0;
	float pr=0;
	
	for(int i=0;i<n;i++){
		if(m>=tw[i]){
			select[i]=1;
			m=m-tw[i];
			pr=pr+tp[i];
			KW=KW+tw[i];
			cout<<"\n"<<KW<<" \n";
		}
		else {
			select[i]=(m+0.0)/(tw[i]+0.0);
			pr=pr+(tp[i]*select[i]);
			m=m-(select[i]*tw[i]);
			KW=KW+(select[i]*tw[i]);
			cout<<"\n"<<KW<<" \n";
		}
	}
	return pr;
}

void Knapsack::print(int pr){
	cout<<"Chosen Objects: ";
	for(int i=0;i<n;i++){
		if(select[i]>0){
			cout<<select[i]<<"x"<<tw[i]<<" + ";
		}
	}
	cout<<"\b\b ";
	cout<<"\n";
	cout<<"Total price: "<<pr<<"\n\n";
}

int main(){
	cout<<"----------------------Knapsack Problem-----------------------\n";
	Knapsack ks;
	cout<<"Enter number of objects: ";
	cin>>ks.n;
	ks.Read();
	
	float pr1 = ks.P();
	cout<<"Greedy on Price: \n";
	ks.print(pr1);
	
	float pr2 = ks.PW();
	cout<<"Greedy on Price per Weight: \n";
	ks.print(pr2);
	
	float pr3 = ks.Frac();
	cout<<"Fractional Knapsack: \n";
	ks.print(pr3);
	
	cout<<"---------------------------------------------------------\n";
}



///////////////////////////////////////////////////////


