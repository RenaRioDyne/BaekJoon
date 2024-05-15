#include <stdio.h>

const int MAX_ELTS = 100005;

class MaxHeap{
private:
    int elements[MAX_ELTS];
    int top; // index of first null elt

    void upheap(int index){
        int temp;

        while(index > 1 && elements[index] > elements[index / 2]){
            temp = elements[index];
            elements[index] = elements[index / 2];
            elements[index / 2] = temp;
            index = index / 2;
        }
    }

    void downheap(int index){
        int temp, next;

        while(index * 2 < top){
            next = index * 2;

            if(next + 1 < top && elements[next + 1] > elements[next]){
                next += 1;
            }

            if(elements[next] < elements[index]) break;
            temp = elements[index];
            elements[index] = elements[next];
            elements[next] = temp;
            index = next;
        }
    }

public:
    MaxHeap(){
        top = 1;
    }

    void add(int element){
        if(top == MAX_ELTS) return;

        elements[top] = element;
        upheap(top);
        top++;
    }

    int pop(){
        if(top == 1) return -1;

        top--;

        int temp = elements[1];
        elements[1] = elements[top];
        elements[top] = temp;

        downheap(1);

        return temp;
    }

    int size(){
        return top - 1;
    }
};

int main(){
    int N;
    int input;
    MaxHeap heap;

    scanf("%d", &N);
    for(int i=0; i<N; i++){
        scanf("%d", &input);
        if(input == 0){
            if(heap.size() == 0) printf("0\n");
            else printf("%d\n",heap.pop());
        }else{
            heap.add(input);
        }
    }

    return 0;
}