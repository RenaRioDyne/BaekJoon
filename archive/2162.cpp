#include <stdio.h>
#include <algorithm>

const int MAX_N = 3005;

class OnionFind{ // since union is a keyword, use onion instead for funzies
private:
    int size;
    int ptr[MAX_N];
    void clear(){
        for(int i=0; i<MAX_N; i++){
            ptr[i] = i;
        }
    }

    void shorten(int rootidx, int leafidx){
        int cur = leafidx;
        int parent = ptr[cur];
        while(parent != rootidx){
            ptr[cur] = rootidx;
            cur = parent;
            parent = ptr[cur];
        }
    }

public:
    OnionFind(){
        size = MAX_N;
    }

    void initWithSize(int s){
        size = s;
        clear();
    }

    int find(int idx){
        int cur = idx;
        int parent = ptr[cur];
        while(parent != cur){
            cur = parent;
            parent = ptr[cur];
        }
        shorten(parent, idx);
        return parent;
    }

    int onion(int i1, int i2){
        i1 = find(i1);
        i2 = find(i2);
        if(i1 > i2) std::swap(i1, i2);
        ptr[i2] = i1;
        return i1;
    }

    void survey(){
        int surveyarr[MAX_N];

        for(int i=0; i<size; i++){
            surveyarr[i] = 0;
            surveyarr[find(i)]++;
        }

        int numSets = 0;
        int maxCount = 0;

        for(int i=0; i<size; i++){
            if(surveyarr[i] != 0){
                numSets++;
                if(maxCount < surveyarr[i]){
                    maxCount = surveyarr[i];
                }
            }
        }

        printf("%d\n%d\n", numSets, maxCount);
    }
};

OnionFind group;

class Point{
public:
    long long x, y;

    long long ccw(Point p2, Point p3){
        return (p2.x - x) * (p3.y - p2.y) - (p2.y - y) * (p3.x - p2.x);
    }

    long long getX(){
        return x;
    }

    long long getY(){
        return y;
    }
};

class Segment{
private:
    Point p1, p2;

    bool boxContains(Point p){
        if(p1.x >= p2.x) std::swap(p1, p2);
        if(p1.x > p.x || p2.x < p.x) return false;
        
        if(p1.y >= p2.y) std::swap(p1, p2);
        if(p1.y > p.y || p2.y < p.y) return false;

        return true;
    }

public:
    bool intersects(Segment* otherSegment){
        long long ccw1 = p1.ccw(p2, otherSegment->p1) * p1.ccw(p2, otherSegment->p2);
        long long ccw2 = otherSegment->p1.ccw(otherSegment->p2, p1) * otherSegment->p1.ccw(otherSegment->p2, p2);
        
        if(ccw1 == 0 && ccw2 == 0){
            if(boxContains(otherSegment->p1) || boxContains(otherSegment->p2)){
                return (boxContains(otherSegment->p1) && boxContains(otherSegment->p2)) || otherSegment->boxContains(p1) || otherSegment->boxContains(p2);
            }
            return otherSegment->boxContains(p1) && otherSegment->boxContains(p2);
        }

        return ccw1 <= 0 && ccw2 <= 0;
    }

    void setPoints(Point f1, Point f2){
        p1.x = f1.x;
        p1.y = f1.y;
        p2.x = f2.x;
        p2.y = f2.y;
    }
};

Segment lines[MAX_N];

int main(){
    int N;
    scanf("%d", &N);
    Point f1, f2;

    for(int i=0; i<N; i++){
        scanf("%lld %lld %lld %lld", &f1.x, &f1.y, &f2.x, &f2.y);
        lines[i].setPoints(f1, f2);
    }

    group.initWithSize(N);

    for(int i=0; i<N; i++){
        for(int j=i+1; j<N; j++){
            if(lines[i].intersects(lines + j)) group.onion(i,j);
        }
    }

    group.survey();
}