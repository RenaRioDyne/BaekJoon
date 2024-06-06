#include <vector>
#include <stack>
#include <stdio.h>
#include <algorithm>

struct Edge{
    int v1, v2;
};

const int MAX_VERTICES = 20005;

std::vector<Edge> graph[MAX_VERTICES];
int color[MAX_VERTICES];

void clear(){
    for(int i=0; i<MAX_VERTICES; i++){
        graph[i].clear();
        color[i] = -1;
    }
}

int main(){
    int K;
    int V;
    int E;
    Edge edge;

    scanf("%d", &K);

    for(int k=0; k<K; k++){
        clear();

        scanf("%d %d", &V, &E);


        for(int e=0; e<E; e++){
            scanf("%d %d", &edge.v1, &edge.v2);
            graph[edge.v1].push_back(edge);
            graph[edge.v2].push_back(edge);
        }


        bool flag = false;
        for(int starting = 0; starting < MAX_VERTICES; starting++){        
            if(graph[starting].size() == 0 || color[starting] != -1) continue;

            std::stack<Edge> stack;
            color[starting] = 0;
            for(int i=0; i<graph[starting].size(); i++){
                stack.push(graph[starting][i]);
            }
            while(stack.size() > 0){
                edge = stack.top();
                stack.pop();
                if(color[edge.v1] == -1) std::swap(edge.v1, edge.v2);
                if(color[edge.v2] != -1){
                    if(color[edge.v2] == color[edge.v1]){
                        flag = true;
                        break;
                    }
                    else continue;
                }
                color[edge.v2] = (color[edge.v1] + 1) % 2;
                for(int i=0; i<graph[edge.v2].size(); i++){
                    stack.push(graph[edge.v2][i]);
                }
            }
            if(flag) break;
        }
        if(!flag) printf("YES\n");
        else printf("NO\n");
    }
}
