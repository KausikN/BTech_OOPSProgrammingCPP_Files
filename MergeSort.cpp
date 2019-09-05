#include<iostream>
#include<string.h>

using namespace std;

class MergeSort{
	private:
		char a[200][200];
		char mn[200][200];
		char new_mn[200][200];
		char b[200][200];
	public:
		int n;
		void Read();
		void sort(int beg, int end);
		void merge(int beg, int end);
		void print();
		void add(char c[], char nm[]);
};

void MergeSort::Read(){
	for(int i=0;i<n;i++){
		cout<<"Enter word "<<i+1<<": ";
		int j=0;
		cin>>a[i];
		j=0;
		cout<<"Enter meaning "<<i+1<<": ";
		cin>>mn[i];
	}
}

void MergeSort::sort(int beg, int end){
	if(beg<end){
		int mid = (beg+end)/2;
		sort(beg, mid);
		sort(mid+1, end);
		merge(beg, end);
	}
}

void MergeSort::merge(int beg, int end){
	int mid = (beg+end)/2;
	int ls = mid-beg+1;
	int rs = end-mid;
	int m = ls+rs;
	int li=0,ri=0;
	for(int i=0;i<m;i++){
		if(li<ls && ri<rs){
			if(strcmp(a[beg+li],a[mid+1+ri])>=0){
				//cout<<"\n\n"<<strcmp(a[beg+li],a[mid+1+ri])<<"\n\n";
				strcpy(b[i],a[mid+1+ri]);
				strcpy(new_mn[i],mn[mid+1+ri]);
				ri++;
				//cout<<"\n\nIndicator1!!"<<b[i]<<"\n\n";
			}
			else {
				//cout<<"\n\n"<<strcmp(a[beg+li],a[mid+1+ri])<<"\n\n";
				strcpy(b[i],a[beg+li]);
				strcpy(new_mn[i],mn[beg+li]);
				li++;
				//cout<<"\n\nIndicator2!!"<<b[i]<<"\n\n";
			}
		}
		else if(li==ls && ri<rs){
			strcpy(b[i],a[mid+1+ri]);
			strcpy(new_mn[i],mn[mid+1+ri]);
			ri++;
			//cout<<"\n\nIndicator3!!"<<b[i]<<"\n\n";
		}
		else if(ri==rs && li<ls){
			strcpy(b[i],a[beg+li]);
			strcpy(new_mn[i],mn[beg+li]);
			li++;
			//cout<<"\n\nIndicator4!!"<<b[i]<<"\n\n";
		}
	}
	for(int j=0;j<m;j++){
		strcpy(a[beg+j],b[j]);
	}
}

void MergeSort::print(){
	for(int i=0;i<n;i++){
		cout<<"("<<a[i]<<" , "<<new_mn[i]<<") ";
		if(i<n-1)cout<<", ";
	}
	cout<<"\n\n";
}

void MergeSort::add(char c[], char nm[]){
	int check=0;
	int j=0;
	int pos=0;
	if(strcmp(c,a[0])<0){
		pos=0;
		for(int i=n;i>pos;i--){
			strcpy(a[i],a[i-1]);
			strcpy(new_mn[i], new_mn[i-1]);
		}
		strcpy(a[pos],c);
		strcpy(new_mn[pos],nm);
		n++;
	}
	else if(strcmp(c,a[n-1])>0){
		strcpy(a[n],c);
		strcpy(new_mn[n],nm);
		n++;
	}
	else {
		for(int i=0;i<n-1;i++){
			if(strcmp(c,a[i])>0 && strcmp(c,a[i+1])<=0){
				pos = i+1;
			}
		}
		for(int i=n;i>pos;i--){
			strcpy(a[i],a[i-1]);
			strcpy(new_mn[i], new_mn[i-1]);
		}
			strcpy(a[pos],c);
			strcpy(new_mn[pos],nm);
			n++;
	}
}

int main(){
	cout<<"----------------------Merge Sort-----------------------\n";
	
	int now = 0;
	
	cout<<"Enter number of words: ";
	cin>>now;
	
	MergeSort ms;
	ms.n=now;
	ms.Read();
	ms.sort(0, now-1);
	ms.print();
	
	cout<<"Enter new word: ";
	char c[200];
	cin>>c;
	cout<<"Enter new meaning: ";
	char nm[200];
	cin>>nm;
	ms.add(c,nm);
	ms.print();
	
	cout<<"----------------------------------------------------\n";
}


