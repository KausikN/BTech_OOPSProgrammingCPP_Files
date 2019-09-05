#include<iostream>
#include<cstdlib>
#include<string.h>
using namespace std;

struct node *rptr=NULL;

struct node{
	struct node *lcptr;
	char sym;
	int freq;
	struct node *rcptr;
};

struct lookup{
	char s;
	char code[200];
};

class HC{
	private:
		
	public:
		char s[200];
		char ds[200];
		int f[200];
		int n;
		int nc;
		void Read();
		void print(struct node *ptr);
		void ISort();
		void count();
		void BuildTree(int a[], char c[], int size, struct node *ptrarr[]);
		void LookupTable(struct node *ptr, char en[], int ensize);
		void Encoder();
		void Decoder(char seq[], int nd);
		struct lookup strucarr[200];
		int lookup_size;
};




////////////////////////////////////////////////////

void HC::ISort(){
	for(int i=1;i<nc;i++){
		for(int j=i;j>0;j--){
			if(f[j-1]>f[j]){
				int temp=f[j];
				f[j]=f[j-1];
				f[j-1]=temp;
				
				char temp2=ds[j];
				ds[j]=ds[j-1];
				ds[j-1]=temp2;
			}
			else break;
		}
	}
}

////////////////////////////////////////////////////

void HC::Read(){
	cout<<"Enter the string: ";
	for(int i=0;i<n;i++){
		cin>>s[i];
	}
	lookup_size = 0;
}

void HC::count(){
	nc=0;
	for(int i=0;i<n;i++){
		int flag=0;
		//ds[0]=0;
		for(int j=0;j<nc;j++){
			if(s[i]==ds[j]){
				flag=1;
				break;
			}
		}
		if(flag==0 ){
			ds[nc]=s[i];
			nc++;
		}
	}
	for(int i=0;i<nc;i++){
		int cou=0;
		for(int j=0;j<n;j++){
			if(ds[i]==s[j]){
				cou++;
			}
		}
		f[i]=cou;
	}
	
	ISort();

}

void HC::BuildTree(int a[], char c[], int size, struct node *ptrarr[]){
	if(size>1){
		int b[200];
		char t[200];
		struct node *nparr[200];
		struct node *ptr = new node;
		
		
		int temp=a[0]+a[1];
		int tempi=0;
		
		for(int i=2;i<size;i++){
			if(temp>=a[i]){
				tempi=i-1;
			}
		}
		//cout<<"\n\ntempi - "<<tempi<<" -- temp - "<<temp<<"\n\nSize - "<<size<<endl<<endl;
		int ct=2;
		for(int i=0;i<tempi;i++){
			b[i]=a[ct];
			t[i]=c[ct];
			nparr[i]=ptrarr[ct];
			ct++;
		}
		b[tempi]=temp;
		nparr[tempi]=ptr;
		t[tempi]=0;
		for(int i=tempi+1;i<nc-1;i++){
			b[i]=a[ct];
			t[i]=c[ct];
			nparr[i]=ptrarr[ct];
			ct++;
		}
		
		struct node *lfptr = new node;
		struct node *rgptr = new node;
		
		lfptr->sym=c[0];
		lfptr->freq = a[0];
		
		if(ptrarr[0]!=NULL){
			lfptr = ptrarr[0];
		}
		
		rgptr->sym=c[1];
		rgptr->freq = a[1];
		
		if(ptrarr[1]!=NULL){
			rgptr = ptrarr[1];
		}
		
		ptr->sym=0;
		ptr->freq=temp;
		ptr->lcptr=lfptr;
		ptr->rcptr=rgptr;
		rptr=ptr;

		BuildTree(b,t,size-1,nparr);
	}
}

void HC::LookupTable(struct node *ptr, char en[], int ensize){
	if(ptr!=NULL){
		if(ptr->lcptr==NULL && ptr->rcptr==NULL){
			lookup_size++;
			int index = (int)(ptr->sym);
			strucarr[index].s = ptr->sym;
			for(int i=0;i<ensize;i++)strucarr[index].code[i] = en[i];
		}
		else {
			ensize++;
			en[ensize-1] = '0';
			LookupTable(ptr->lcptr, en, ensize);
			
			en[ensize-1] = '1';
			LookupTable(ptr->rcptr, en, ensize);
		}
	}
}

void HC::Encoder(){
	cout<<"Encoded Sequence: ";
	char temp[400];
	for(int i=0;i<n;i++){
		int index = (int)(s[i]);
		for(int j=0;j<strlen(strucarr[index].code);j++)cout<<strucarr[index].code[j];
		//cout<<"|";
	}
	cout<<"\n";
}

void HC::Decoder(char seq[], int nd){
	int cn=0;
	cout<<"Decoded sequence: ";
	while(cn<nd){
		struct node *ptr = rptr;
		while(ptr!=NULL){
			if(ptr->lcptr==NULL && ptr->rcptr==NULL){
				cout<<ptr->sym;
				ptr=NULL;
			}
			else {
				if(seq[cn]=='0')ptr=ptr->lcptr;
				else if(seq[cn]=='1')ptr=ptr->rcptr;
				cn++;
			}
			
		}
	}
	cout<<"\n";
}

void HC::print(struct node *ptr){
	if(ptr!=NULL){
		print(ptr->lcptr);
		cout<<"\n";
		cout<<ptr->sym<<" - "<<ptr->freq;
		cout<<"\n";
		print(ptr->rcptr);
	}
}



int main(){
	cout<<"----------------------Huffman Coding-----------------------\n";
	
	rptr=NULL;
	
	HC hc;
	cout<<"Enter number of symbols: ";
	cin>>hc.n;
	//cout<<"Enter 0 for encoding and 1 for decoding: ";
	int tt=0;
	//cin>>tt;
	if(tt==0){
		hc.Read();
		hc.count();
		for(int i=0;i<hc.nc;i++){
			cout<<hc.ds[i]<<" - "<<hc.f[i]<<endl;
		}
		struct node *ptrarr[200];
		for(int i=0;i<hc.nc;i++)ptrarr[i]=NULL;
		hc.BuildTree(hc.f,hc.ds,hc.nc,ptrarr);
		cout<<"\n\n";
		hc.print(rptr);
		cout<<"\n------------Encode----------\n";
		char en[200];
		hc.LookupTable(rptr, en, 0);
		hc.Encoder();
		cout<<"\n----------------------------\n";
		tt++;
	}
	if(tt==1) { //REVERT TO 1
		cout<<"\n------------Decode----------\n";
		cout<<"Enter number of bits: ";
		int nd=0;
		cin>>nd;
		cout<<"Enter the sequence: ";
		char seq[200];
		for(int i=0;i<nd;i++){
			cin>>seq[i];
		}
		hc.Decoder(seq, nd);
		cout<<"\n----------------------------\n";
	}
	
	
	cout<<"---------------------------------------------------------\n";
}



///////////////////////////////////////////////////////

