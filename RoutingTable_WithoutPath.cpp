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
        
        
        void Read(int choice);
        void Generate(int choice);
        void print();
        
        void DijInitialize();
        void Dijkstra();
        void DijPrint();
        
        void BFInitialize();
        int BF(int choice);
        void BFPrint();
};

void Graph::Read(int choice){
    cout<<"Enter the distances: \n";
    edge_n = 0;
    for(int i=1;i<=node_n;i++){
        for(int j=1;j<=node_n;j++){
            if(i!=j && choice == 0){
                e_l[edge_n] = i;
                e_r[edge_n] = j;
                cout<<i<<" - "<<j<<" : ";
                cin>>w[edge_n];
                edge_n++;
            }
            else if(i<j && choice == 1){
                e_l[edge_n] = i;
                e_r[edge_n] = j;
                cout<<i<<" - "<<j<<" : ";
                cin>>w[edge_n];
                edge_n++;
            }
        }
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
//////////////////////////Dijkstra////////////////////////////////
void Graph::DijInitialize(){
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
            if((dist[ptr->x] == -777) || (dist[ptr->x] > dist_from_source)){
                dist[ptr->x] = dist_from_source; 
            }
            if((ptr->w < minw) && (mark[ptr->x] == 0)){
                minw = ptr->w;
                min_index = ptr->x;
            }
        ptr=ptr->nptr;
        }
    }
}

void Graph::DijPrint(){
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

int Graph::BF(int choice){
    
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
    
    //Check
    int olddist[200];
    for(int i=1;i<=node_n;i++) olddist[i] = dist[i];
    
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
    
    for(int i=1;i<=node_n;i++){
        if(olddist[i] != dist[i]){
            return 0;
        }
    }
    return 1;
}

void Graph::BFPrint(){
    for(int i=1;i<=node_n;i++){
        cout<<dist[i]<<" ";
    }
    cout<<"\n";
}
////////////////////////////Bellman Ford////////////////////////////

int main(){
    cout<<"----------------------Routing Table-----------------------\n";
    
    int choice = 1;
    
    Graph g;
    cout<<"Enter the number of nodes: ";
    cin>>g.node_n;
    g.Read(choice);
    g.Generate(choice);
    g.print();
    
    cout<<"\n----------------------Dijkstra-----------------------\n";
    
    for(int i=1;i<=g.node_n;i++){
        g.source = i;
        g.DijInitialize();
        g.Dijkstra();
        
        cout<<i<<": ";
        g.DijPrint();
    }
    
    cout<<"---------------------------------------------------------\n";
    
    cout<<"----------------------Bellman Ford-----------------------\n";

    int flag = 1;
    for(int i=1;i<=g.node_n;i++){
        g.source = i;
        g.BFInitialize();
        flag = flag * g.BF(choice);

        cout<<i<<": ";
        g.BFPrint();
    }
    if(flag == 0){
        cout<<"\nThere is a negative cycle.\n";
    }

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

/*
2 5 3 1 2 4 7 2 1 6 3 9
*/