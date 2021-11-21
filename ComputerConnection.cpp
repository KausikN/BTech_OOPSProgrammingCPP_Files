#include<iostream>
#include<cstdlib>
#include<string.h>
#include<math.h>
using namespace std;

struct node *rptr=NULL;

struct node{
    int x;
    float w;
    struct node *nptr;
};

struct edge{
    int l;
    int r;
    float w;
};

class Graph{
    private:
        
    public:
        char nodes[200][200];//1
        int node_n;
        int edge_n;
        int e_l[200];
        int e_r[200];
        
        int x[200];//1
        int y[200];//1
        
        float w[200];
        struct edge edges[200];
        struct node *arr[200];//1
        int disjoint[200];//1
        int mst_edges[200];
        
        void Read();
        void Generate(int choice);
        void print_adj();
        void ISort();
        int Find(int p[], int a);
        void Kruskal();
        void print();
};



void Graph::Read(){
    cout<<"Enter the nodes: ";
    for(int i=1;i<=node_n;i++){
        cin>>nodes[i];
    }
    int k=0;
    for(int i=1;i<=node_n;i++){
        for(int j=i+1;j<=node_n;j++){
            e_l[k] = i;
            e_r[k] = j;
            
            edges[k].l = i;
            edges[k].r = j;
            
            k++;
        }
    }
    edge_n = k;
    
    for(int i=1;i<=node_n;i++){
        cout<<"Enter the coordinates(x y) of "<<nodes[i]<<": ";
        cin>>x[i];
        cin>>y[i];
    }

    for(int i=0;i<edge_n;i++){
        int a = edges[i].l;
        int b = edges[i].r;
        float dist = sqrt(((x[a]-x[b])*(x[a]-x[b])) + ((y[a]-y[b])*(y[a]-y[b])));
        w[i] = dist;
        edges[i].w = dist;
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

void Graph::print_adj(){
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

void Graph::ISort(){
    for(int i=1;i<edge_n;i++){
        for(int j=i;j>0;j--){
            if(edges[j-1].w>edges[j].w){
                int temp=edges[j].w;
                edges[j].w=edges[j-1].w;
                edges[j-1].w=temp;
                
                temp=edges[j].l;
                edges[j].l=edges[j-1].l;
                edges[j-1].l=temp;
                
                temp=edges[j].r;
                edges[j].r=edges[j-1].r;
                edges[j-1].r=temp;
            }
            else break;
        }
    }
}

int Graph::Find(int p[], int a){
    int i=a;
    while(p[i]>0){
        i=p[i];
    }
    return i;
}

void Graph::Kruskal(){
    for(int i=1;i<=node_n;i++)disjoint[i]=-1;
    
    int kn = node_n;
    int i=0;
    int j=0;
    
    while(i<kn-1 && j<edge_n){//cout<<"\n\ndisjoint: "; for(int kk=1;kk<=node_n;kk++) cout<<disjoint[kk]<<" ";
        if(Find(disjoint, edges[j].l) != Find(disjoint, edges[j].r)){
            i++;
            if(disjoint[Find(disjoint, edges[j].l)] < disjoint[Find(disjoint, edges[j].r)]){
                disjoint[Find(disjoint, edges[j].l)] = disjoint[Find(disjoint, edges[j].l)] + disjoint[Find(disjoint, edges[j].r)];
                disjoint[Find(disjoint, edges[j].r)] = Find(disjoint, edges[j].l);
            }
            else {
                disjoint[Find(disjoint, edges[j].r)] = disjoint[Find(disjoint, edges[j].l)] + disjoint[Find(disjoint, edges[j].r)];
                disjoint[Find(disjoint, edges[j].l)] = Find(disjoint, edges[j].r);
            }
            mst_edges[j] = 1;
        }
        else {
            mst_edges[j] = 0;
        }
        j++;
    }
}

void Graph::print(){
    cout<<"Pairs to be connected are: \n";
    for(int i=0;i<edge_n;i++){
        if(mst_edges[i] == 1){
            cout<<nodes[edges[i].l]<<" - "<<nodes[edges[i].r]<<" ("<<edges[i].w<<")"<<"\n";
        }
    }
    cout<<"\n";
}

int main(){
    cout<<"----------------------Computer Connection-----------------------\n";
    
    Graph g;
    
    cout<<"Enter the number of locations: ";
    cin>>g.node_n;
    if(g.node_n < 2){
        cout<<"";
    }
    
    
    
    
    g.Read();
    g.Generate(1);
    g.print_adj();
    g.ISort();
    g.Kruskal();
    g.print();
    
    cout<<"---------------------------------------------------------\n";
}



///////////////////////////////////////////////////////

/*void Graph::Read(){
    cout<<"Enter the number of edges: ";
    cin>>edge_n;
    cout<<"Enter the edges: ";
    for(int i=0;i<edge_n;i++){
        cin>>e_l[i];
        cin>>e_r[i];
        edges[i].l = e_l[i];
        edges[i].r = e_r[i];
    }
    cout<<"Enter the weights: \n";
    for(int i=0;i<edge_n;i++){
        cout<<e_l[i]<<" - "<<e_r[i]<<": ";
        cin>>w[i];
        edges[i].w = w[i];
    }
    for(int i=0;i<=node_n;i++){
        arr[i]=NULL;
    }
}*/