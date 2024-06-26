#include <stdio.h>
#include <algorithm>

const int MAX_N = 3005;

class OnionFind{ // since union is a keyword, use onion instead for funzies
private:
    int size;
    int numSets;
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
        size = numSets = s;
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
        if(i1 != i2) numSets--;
        if(i1 > i2) std::swap(i1, i2);
        ptr[i2] = i1;
        return i1;
    }

    int getNumSets(){
        return numSets;
    }
}

OnionFind group;

class Point{
private:
    int x, y;
public:
    int ccw(Point p2, Point p3){
        // need implementation
    }

    int getX(){
        return x;
    }

    int getY(){
        return y;
    }
}

class Segment{
private:
    Point p1, p2;

    bool boxContains(Point p){
        if(p1.getX() >= p2.getX()) std::swap(p1, p2);
        if(p1.getX() > p.getX() || p2.getX() < p.getX()) return false;
        
        if(p1.getY() >= p2.getY()) std::swap(p1, p2);
        if(p1.getY() > p.getY() || p2.getY() < p.getY()) return false;

        return true;
    }

public:
    bool intersects(Segment* otherSegment){
        int ccw1 = p1.ccw(p2, otherSegment->p1) * p1.ccw(p2, otherSegment->p2);
        int ccw2 = otherSegment->p1.ccw(otherSegment->p2, p1) * otherSegment->p1.ccw(otherSegment->p2, p2);
        
        if(ccw1 == 0 && ccw2 == 0){
            if(boxContains(otherSegment->p1) || boxContains(otherSegment->p2)){
                return (boxContains(otherSegment->p1) && boxContains(otherSegment->p2)) || otherSegment->boxContains(p1) || otherSegment->boxContains(p2);
            }
            return otherSegment->boxContains(p1) && otherSegment->boxContains(p2);
        }

        return this->splits(otherSegment) && otherSegment->splits(this);
    }
}