#include <stdio.h>
#include <vector>
#include <algorithm>

#define nextChild vertices[e.index].adjacent[e.childrenIndex]

const int MAX_VERTICES = 10005;
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

int main(){
    int V;
    int E;

    scanf("%d %d", &V, &E);

    int from, to;
    for(int e=0; e<E; e++){
        scanf("%d %d", &from, &to);
        vertices[from].adjacent.push_back(to);
    }
    for(int v=1; v<=V; v++){
        vertices[v].init();
    }

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
                // handle returning the outgoing edge
                vertices[e.index].lowlink = std::min(vertices[e.index].lowlink, vertices[nextChild].lowlink);
            }
            e.childrenIndex++;
            if(e.childrenIndex < vertices[e.index].adjacent.size()){
                // printf("vertex %d child %d onstack %d\n", e.index, nextChild, vertices[nextChild].onStack ? 1 : 0);
                // consider outgoing edge
                if(vertices[nextChild].visitOrder < 0){
                    e.skip = false;
                    recursion_stack.push_back(e);
                    dfs_stack.push_back(nextChild);
                    vertices[nextChild].visitOrder = vertices[nextChild].lowlink = global_index;
                    vertices[nextChild].onStack = true;
                    global_index++;
                    e = {nextChild, -1, false};
                    recursion_stack.push_back(e);
                    //printf("%d %d\n", e.index, e.childrenIndex);
                    //printf("%d %d\n", nextChild, vertices[nextChild].visitOrder);
                }else{
                    e.skip = true;
                    recursion_stack.push_back(e);
                    if(vertices[nextChild].onStack){
                        vertices[e.index].lowlink = std::min(vertices[e.index].lowlink, vertices[nextChild].visitOrder);
                        // printf("index %d lowlink %d nextchild %d\n",e.index, vertices[e.index].lowlink, nextChild);
                    }
                } 
            }else if(vertices[e.index].lowlink == vertices[e.index].visitOrder){
                // make new connected comp
                // printf("new connected comp.:\n");
                while(dfs_stack.back() != e.index){
                    connected_components[num_connected_components].push_back(dfs_stack.back());
                    vertices[dfs_stack.back()].onStack = false;
                    // printf("index %d\n", dfs_stack.back());
                    dfs_stack.pop_back();
                }
                connected_components[num_connected_components].push_back(e.index);
                vertices[e.index].onStack = false;
                dfs_stack.pop_back();
                num_connected_components++;
            }

            //printf("e has index %d and children index %d\n", e.index, e.childrenIndex);
            //printf("current stack depth is recursion %d, dfs %d\n", recursion_stack.size(), dfs_stack.size());
            //printf("num of connected comps %d. global index %d\n", num_connected_components, global_index);
        }
    }

    for(int i=0; i<num_connected_components; i++){
        std::sort(connected_components[i].begin(), connected_components[i].end());
    }

    std::sort(connected_components, connected_components + num_connected_components, cmp);

    printf("%d\n", num_connected_components);

    for(int i=0; i<num_connected_components; i++){
        for(int j=0; j<connected_components[i].size(); j++){
            printf("%d ", connected_components[i][j]);
        }
        printf("-1\n");
    }
}
