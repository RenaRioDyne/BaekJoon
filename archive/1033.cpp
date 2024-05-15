#include <stdio.h>

const int MAX_N = 10;

enum PRIMES{
    PRIME_TWO,
    PRIME_THREE,
    PRIME_FIVE,
    PRIME_SEVEN,
    NUM_PRIMES
};

int primeValues[] = {2, 3, 5, 7};

int ratio[MAX_N][MAX_N][NUM_PRIMES];
bool visited[MAX_N];

void decompose(long long composite, int* primeCells){ // 1 \le composite \le 10
    for(int i=0; i<NUM_PRIMES; i++){
        primeCells[i] = 0;
        while(composite % primeValues[i] == 0){
            primeCells[i]++;
            composite /= primeValues[i];
        }
    }
}

long long compose(int* primeCells){
    long long composite = 1;
    for(int i=0; i<NUM_PRIMES; i++){
        for(int j=0; j<primeCells[i]; j++){
            composite *= primeValues[i];
        }
    }
    return composite;
}

void relativePrime(int* decomposed1, int* decomposed2){
    for(int i=0; i<NUM_PRIMES; i++){
        while(decomposed1[i] != 0 && decomposed2[i] != 0){
            decomposed1[i]--;
            decomposed2[i]--;
        }
    }
}

void multiply(int* decomposed1, int* decomposed2){ // decomposed2 stays the same
    for(int i=0; i<NUM_PRIMES; i++){
        decomposed1[i] += decomposed2[i];
    }
}

void divide(int* decomposed1, int* decomposed2){ // decomposed2 stays the same
    for(int i=0; i<NUM_PRIMES; i++){
        decomposed1[i] -= decomposed2[i];
    }
}

void copy(int* from, int* to){
    for(int i=0; i<NUM_PRIMES; i++){
        to[i] = from[i];
    }
}

void clear(int* decomposed){
    decompose(1, decomposed);
}

long long lcm(int* decomposed1, int* decomposed2){ // lcm in decomposed1, decomposed2 stays the same. returns lcm / original_decomposed1
    long long ret = 1;
    for(int i=0; i<NUM_PRIMES; i++){
        int diff = decomposed2[i] - decomposed1[i];
        while(diff > 0){
            decomposed1[i] = decomposed2[i];
            ret *= (primeValues[i]);
            diff--;
        }
    }
    return ret;
}

class Ingredient{
private:
    int quantity[NUM_PRIMES];
    Ingredient* pairs[MAX_N];
    int numPairs;
    int index;

public:
    void setIndex(int i){
        index = i;
    }

    Ingredient(){
        numPairs = 0;
        for(int i=0; i<NUM_PRIMES; i++){
            quantity[i] = 0;
        }
    }

    void printStatus(){
        printf("Node %d is adjacent to %d nodes:\n", index, numPairs);
        for(int i=0; i<numPairs; i++){
            printf("%d ", pairs[i]->index);
        }
        printf("\n");
    }

    void addPair(Ingredient* otherIngredient){
        pairs[numPairs] = otherIngredient;
        numPairs++;
        otherIngredient->pairs[otherIngredient->numPairs] = this;
        otherIngredient->numPairs++;
    }

    long long scale(){
        int scaling_all[NUM_PRIMES];
        clear(scaling_all);

        int temp_scaling[NUM_PRIMES];

        for(int c=0; c<numPairs; c++){
            Ingredient* otherIngredient = pairs[c];
            if(visited[otherIngredient->index]) continue;
            visited[otherIngredient->index] = true;

            long long scale = lcm(quantity, ratio[index][otherIngredient->index]);
            clear(temp_scaling);
            decompose(scale, temp_scaling);
            multiply(scaling_all, temp_scaling);

            copy(quantity, otherIngredient->quantity);
            multiply(otherIngredient->quantity, ratio[otherIngredient->index][index]);
            divide(otherIngredient->quantity, ratio[index][otherIngredient->index]);

            scale = otherIngredient->scale();

            clear(temp_scaling);
            decompose(scale, temp_scaling);
            multiply(quantity, temp_scaling);
            multiply(scaling_all, temp_scaling);
        }

        return compose(scaling_all);
    }

    void propagate(){
        for(int c=0; c<numPairs; c++){
            Ingredient* otherIngredient = pairs[c];
            if(visited[otherIngredient->index]) continue;
            visited[otherIngredient->index] = true;

            long long childVal = compose(quantity) * compose(ratio[otherIngredient->index][index]) / compose(ratio[index][otherIngredient->index]);
            decompose(childVal, otherIngredient->quantity);
            otherIngredient->propagate();
        }
    }

    long long getMass(){
        return compose(quantity);
    }
};

Ingredient ingredients[MAX_N];

int main(){
    int N;
    scanf("%d", &N);

    if(N==1){
        printf("1\n");
        return 0;
    }

    int a, b, p, q;
    for(int i=0; i<N-1; i++){
        scanf("%d %d %d %d", &a, &b, &p, &q);
        ingredients[a].addPair(ingredients+b);
        decompose(p, ratio[a][b]);
        decompose(q, ratio[b][a]);
        relativePrime(ratio[a][b], ratio[b][a]);

        ingredients[i].setIndex(i);
        visited[i] = false;
    }
    ingredients[N-1].setIndex(N-1);
    visited[N-1] = false;

    visited[0] = true;
    ingredients[0].scale();

    for(int i=0; i<N; i++){
        visited[i] = false;
    }
    
    visited[0] = true;
    ingredients[0].propagate();

    for(int i=0; i<N; i++){
        printf("%lld ", ingredients[i].getMass());
    }
}