#include <stdio.h>
#include <vector>
#include <algorithm>

const int MAX_N = 100005;

// ------------------ from problem 2150 ------------------------ //

#define nextChild vertices[e.index].adjacent[e.childrenIndex]

const int MAX_VERTICES = MAX_N;
const int MAX_EDGES = 100005;

class Vertex{
public:
    int lowlink;
    int visitOrder;
    bool onStack;
    std::vector<int> adjacent;

    void init(){
        onStack = false;
        visitOrder = -1;
    }
};

std::vector<int> connected_components[MAX_VERTICES];
Vertex vertices[MAX_VERTICES];
Vertex hypergraph[MAX_N];
int hypergraph_nodes[MAX_VERTICES];
bool visited[MAX_N];

void clear(){
    for(int i=0; i<MAX_VERTICES; i++){
        connected_components[i].clear();
        vertices[i].init();
        vertices[i].adjacent.clear();
    }
    for(int i=0; i<MAX_N; i++){
        hypergraph[i].init();
        hypergraph[i].adjacent.clear();
        visited[i] = false;
    }
}

struct recursionElt{
    int index;
    int childrenIndex;
    bool skip;
};

bool cmp(const std::vector<int> &p1, const std::vector<int> &p2){
    if(p1[0] < p2[0]){
        return true;
    }
    return false;
}

int makeReverseHypergraph(int V, int E){ // returns the size of the hypergraph
    int global_index = 0;
    int num_connected_components = 0;

    std::vector<int> dfs_stack;
    std::vector<recursionElt> recursion_stack;
    recursionElt e;

    for(int v=1; v<=V; v++){
        if(vertices[v].visitOrder >= 0) continue;
        vertices[v].visitOrder = vertices[v].lowlink = global_index;
        vertices[v].onStack = true;
        global_index++;
        dfs_stack.push_back(v);
        recursion_stack.push_back({v,-1,false});

        while(!recursion_stack.empty()){
            e = recursion_stack.back();
            recursion_stack.pop_back();
            if(e.childrenIndex >= 0 && !e.skip){
                vertices[e.index].lowlink = std::min(vertices[e.index].lowlink, vertices[nextChild].lowlink);
            }
            e.childrenIndex++;
            if(e.childrenIndex < vertices[e.index].adjacent.size()){
                if(vertices[nextChild].visitOrder < 0){
                    e.skip = false;
                    recursion_stack.push_back(e);
                    dfs_stack.push_back(nextChild);
                    vertices[nextChild].visitOrder = vertices[nextChild].lowlink = global_index;
                    vertices[nextChild].onStack = true;
                    global_index++;
                    e = {nextChild, -1, false};
                    recursion_stack.push_back(e);
                }else{
                    e.skip = true;
                    recursion_stack.push_back(e);
                    if(vertices[nextChild].onStack){
                        vertices[e.index].lowlink = std::min(vertices[e.index].lowlink, vertices[nextChild].visitOrder);
                    }
                } 
            }else if(vertices[e.index].lowlink == vertices[e.index].visitOrder){
                // make new connected comp
                while(dfs_stack.back() != e.index){
                    connected_components[num_connected_components].push_back(dfs_stack.back());
                    vertices[dfs_stack.back()].onStack = false;
                    hypergraph_nodes[dfs_stack.back()] = num_connected_components;
                    dfs_stack.pop_back();
                }
                connected_components[num_connected_components].push_back(e.index);
                vertices[e.index].onStack = false;
                hypergraph_nodes[e.index] = num_connected_components;
                dfs_stack.pop_back();
                num_connected_components++;
            }
        }
    }

    // inverse pushback for finding roots
    for(int i=0; i<num_connected_components; i++){
        for(int j=0; j<connected_components[i].size(); j++){
            for(int k=0; k<vertices[connected_components[i][j]].adjacent.size(); k++){
                if(hypergraph_nodes[vertices[connected_components[i][j]].adjacent[k]] == i) continue;
                hypergraph[hypergraph_nodes[vertices[connected_components[i][j]].adjacent[k]]].adjacent.push_back(i);
            }
        }
    }

    return num_connected_components;
}

int main(){
    int T;
    scanf("%d", &T);
    for(int t=0; t<T; t++){
        int N, M;
        scanf("%d %d", &N, &M);
        clear();

        int from, to;
        for(int m=0; m<M; m++){
            scanf("%d %d", &from, &to);
            vertices[from].adjacent.push_back(to);
        }
        for(int n=1; n<=N; n++){
            vertices[n].init();
        }
        
        int hyperN = makeReverseHypergraph(N, M);

        int counter = 0;
        for(int i=0; i<hyperN; i++){
            if(hypergraph[i].adjacent.size() == 0) counter++;
        }

        printf("%d\n", counter);
    }
}