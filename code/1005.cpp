#include <stdio.h>
#include <vector>

struct building{
    int cost;
    std::vector<building*> prerequisites;
    int opt;
    int visited_children;
    int index;
};

building acmCraft[1005];

int dfs_propagate(building* first){
    std::vector<building*> stack;
    building *cur, *child;

    stack.push_back(first);

    while(!stack.empty()){
        cur = stack.back();
        if((int)cur->prerequisites.size() == cur->visited_children){
            //printf("popping element %d\n", cur->index);
            stack.pop_back();
        }else{
            child = cur->prerequisites[cur->visited_children];
            if((int)child->prerequisites.size() > child->visited_children){
                //printf("investigating child #%d of element %d\n", cur->visited_children+1, cur->index);
                stack.push_back(child);
            }else{
                //printf("child #%d of element %d has %d cost\n", cur->visited_children+1, cur->index, child->opt);
                if(cur->opt < child->opt + cur->cost) cur->opt = child->opt + cur->cost;
                cur->visited_children++;
                //printf("#visited children: %d\n", cur->visited_children);
            }
        }
    }

    return first->opt;
}

int main(){
    int T, N, K, X, Y, W;
    scanf("%d", &T);
    for(int t = 0; t < T; t++){
        //printf("-----%dth iteration-----\n", t);
        scanf("%d %d", &N, &K);

        for(int n = 1; n <= N; n++){
            scanf("%d", &acmCraft[n].cost);
            acmCraft[n].prerequisites.clear();
            acmCraft[n].opt = acmCraft[n].cost;
            acmCraft[n].visited_children = 0;
            acmCraft[n].index = n;
        }

        for(int k=0; k < K; k++){
            scanf("%d %d", &X, &Y);
            acmCraft[Y].prerequisites.push_back(acmCraft + X);
        }

        scanf("%d", &W);

        printf("%d\n", dfs_propagate(acmCraft + W));
    }
}