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
		
		int mark[200];
		int dist[200];
		int source;
		
		
		void Read();
		void Generate(int choice);
		void print();
		
		void DijInitialize();
		void Dijkstra();
		void DijPrint();
		
		void BFInitialize();
		void BF(int choice);
		void BFPrint();
};

void Graph::Read(){
	cout<<"Enter the number of edges: ";
	cin>>edge_n;
	cout<<"Enter the edges: ";
	for(int i=0;i<edge_n;i++){
		cin>>e_l[i];
		cin>>e_r[i];
		cin>>w[i];
	}
	/*cout<<"Enter the weights: \n";
	for(int i=0;i<edge_n;i++){
		cout<<e_l[i]<<" - "<<e_r[i]<<": ";
		cin>>w[i];
	}*/
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
//////////////////////////Dijkstra////////////////////////////////
void Graph::DijInitialize(){
	cout<<"Enter source: ";
	cin>>source;
	if(source > node_n || source < 0)cout<<"Invalid source.\n";
	else {
		for(int i=1;i<=node_n;i++){
			mark[i] = 0;
			dist[i] = -777; //Marker Value for Infinity
		}
		mark[source] = 1;
		dist[source] = 0;
	}
}

void Graph::Dijkstra(){
	/*struct node *ptr = arr[source];
	int minw = ptr->w;
	int min_index = ptr->x;
	while(ptr != NULL){
		dist[ptr->x] = ptr->w;
		if(ptr->w < minw){
			minw = ptr->w;
			min_index = ptr->x;
		}
		ptr=ptr->nptr;
	}*/
	
	struct node *ptr = arr[source];
	int minw = 0;
	int min_index = source;
	
	for(int i=0;i<=node_n;i++){
		mark[min_index] = 1;
		struct node *ptr = arr[min_index];
		int parent = min_index;
		minw = ptr->w;
		min_index = ptr->x;
		while(ptr != NULL){
			int dist_from_source = ptr->w + dist[parent];
			//if(parent == 6 && ptr->x == 4)cout<<"\nHello There: "<<dist_from_source<<" - "<<dist[ptr->x]<<endl;
			if((dist[ptr->x] == -777) || (dist[ptr->x] > dist_from_source)){
				//cout<<"\n---"<<ptr->x<<"---oldidist: "<<dist[ptr->x]<<" newdist: "<<dist_from_source<<"---\n";
				dist[ptr->x] = dist_from_source; 
			}
			if((ptr->w < minw) && (mark[ptr->x] == 0)){
				minw = ptr->w;
				min_index = ptr->x;
			}
		ptr=ptr->nptr;
		//DijPrint();
		}
		//cout<<"\nMinw: "<<minw<<" Minind: "<<min_index<<endl;
	}
}

void Graph::DijPrint(){
	cout<<"\nMark: ";
	for(int i=1;i<=node_n;i++){
		cout<<mark[i]<<" ";
	}
	
	cout<<"\nDist: ";
	for(int i=1;i<=node_n;i++){
		cout<<dist[i]<<" ";
	}
	cout<<"\n";
}
//////////////////////////Dijkstra////////////////////////////////

////////////////////////////Bellman Ford////////////////////////////
void Graph::BFInitialize(){
	for(int i=1;i<=node_n;i++){
		dist[i] = -777; //Marker Value for Infinity
	}
	dist[source] = 0;
}

void Graph::BF(int choice){
	
	for(int i=1;i<=node_n;i++){
		for(int j=0;j<edge_n;j++){
			int u = e_l[j];
			int v = e_r[j];
			if(((dist[u] + w[j] < dist[v]) && (dist[u] != -777)) || (dist[v] == -777)){
				if(dist[u] == -777) dist[v] = -777;
				else dist[v] = dist[u] + w[j];
			}
			if(choice == 1){
				if(((dist[v] + w[j] < dist[u]) && (dist[v] != -777)) || (dist[u] == -777)){
					if(dist[v] == -777) dist[u] = -777;
					else dist[u] = dist[v] + w[j];
				}
			}
		}
	}
}

void Graph::BFPrint(){
	cout<<"\nDist: ";
	for(int i=1;i<=node_n;i++){
		cout<<dist[i]<<" ";
	}
	cout<<"\n";
}
////////////////////////////Bellman Ford////////////////////////////

int main(){
	cout<<"----------------------Dijkstra-----------------------\n";
	
	Graph g;
	int choice=0;
	cout<<"Enter 0 for directed, 1 for undirected: ";
	cin>>choice;
	cout<<"Enter the number of nodes: ";
	cin>>g.node_n;
	g.Read();
	g.Generate(choice);
	g.print();
	
	g.DijInitialize();
	g.Dijkstra();
	g.DijPrint();
	
	
	cout<<"---------------------------------------------------------\n";
	
	cout<<"----------------------Bellman Ford-----------------------\n";

	g.BFInitialize();
	g.BF(choice);
	g.BFPrint();
	
	
	cout<<"---------------------------------------------------------\n";
}



///////////////////////////////////////////////////////

/*
1 2 1
1 3 3
3 6 1
6 4 2 
4 2 7
2 5 4
5 4 3 
5 6 5

*/

