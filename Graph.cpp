#include<iostream>
#include<cstdlib>
#include<string.h>
using namespace std;

struct node *rptr=NULL;

struct node{
	int x;
	int w;
	struct node *nptr;
};

class Graph{
	private:
		
	public:
		int node_n;
		int edge_n;
		int e_l[200];
		int e_r[200];
		int w[200];
		struct node *arr[200];
		void Read();
		void Generate(int choice);
		void print();
};

void Graph::Read(){
	cout<<"Enter the number of edges: ";
	cin>>edge_n;
	cout<<"Enter the edges: ";
	for(int i=0;i<edge_n;i++){
		cin>>e_l[i];
		cin>>e_r[i];
	}
	cout<<"Enter the weights: \n";
	for(int i=0;i<edge_n;i++){
		cout<<e_l[i]<<" - "<<e_r[i]<<": ";
		cin>>w[i];
	}
	for(int i=0;i<=node_n;i++){
		arr[i]=NULL;
	}
}

void Graph::Generate(int choice){
	for(int i=0;i<edge_n;i++){
		struct node *ptr = new node;
		ptr->x = e_r[i];
		ptr->w = w[i];
		ptr->nptr = arr[e_l[i]];
		arr[e_l[i]] = ptr;
		if(choice == 1){
			struct node *ptr2 = new node;
			ptr2->x = e_l[i];
			ptr2->w = w[i];
			ptr2->nptr = arr[e_r[i]];
			arr[e_r[i]] = ptr2;
		}
		
	}
}

void Graph::print(){
	for(int i=1;i<=node_n;i++){
		struct node *ptr = arr[i];
		cout<<"Edge "<<i<<": ";
		while(ptr!=NULL){
			cout<<ptr->x<<"("<<ptr->w<<") ";
			ptr = ptr->nptr;
		}
		cout<<"\n";
	}
	
}

int main(){
	cout<<"----------------------Computer Connection-----------------------\n";
	
	Graph g;
	int choice=0;
	cout<<"Enter 0 for directed, 1 for undirected: ";
	cin>>choice;
	cout<<"Enter the number of nodes: ";
	cin>>g.node_n;
	g.Read();
	g.Generate(choice);
	g.print();
	
	cout<<"---------------------------------------------------------\n";
}



///////////////////////////////////////////////////////

