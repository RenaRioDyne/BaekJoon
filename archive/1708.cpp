#include <stdio.h>
#include <cmath>
#include <algorithm>
#include <float.h>

const int MAX_N = 100005;
const int MAX_X = 40005;

class Point{
public:
    long long x, y;

    Point(){
        x = 0;
        y = 0;
    }

    long double distance(Point otherPoint){
        return sqrt((long double)((otherPoint.x - x) * (otherPoint.x - x) + (otherPoint.y - y) * (otherPoint.y - y)));
    }

    Point & operator=(const Point &rhs){
        if(this != &rhs){
            x = rhs.x;
            y = rhs.y;
        }
        return *this;
    }

    bool operator==(const Point &rhs) const {
        return (x == rhs.x) && (y == rhs.y);
    }

    bool operator!=(const Point &rhs) const {
        return !(*this == rhs);
    }
};

Point points[MAX_N];

class Vector{
public:
    Point origin, dest;
    long double magnitude;

    Vector(){
        Point dummy;
        origin = dummy;
        dest = dummy;
        magnitude = -1;
    }

    void init(Point o, Point d){
        origin = o;
        dest = d;
        magnitude = o.distance(d);
    }

    long double cosine(Vector* otherVector){
        long long inner = (dest.x - origin.x) * (otherVector->dest.x - otherVector->origin.x) + (dest.y - origin.y) * (otherVector->dest.y - otherVector->origin.y);
        return inner / (magnitude * otherVector->magnitude);
    }

    Vector & operator=(const Vector &rhs){
        if(this != &rhs){
            origin = rhs.origin;
            dest = rhs.dest;
            magnitude = rhs.magnitude;
        }
        return *this;
    }
};

int main(){
    int N;
    scanf("%d", &N);

    int top = 0;
    int next = 0;
    for(; top < N; top++){
        scanf("%lld %lld", &points[top].x, &points[top].y);
        if(points[top].x < points[next].x || (points[top].x == points[next].x && points[top].y > points[next].y)){
            next = top;
        }
    }

    top--;

    int convex = 1;

    Vector prev;
    Point dummy;
    dummy.x = points[next].x;
    dummy.y = points[next].y + 5;
    prev.init(points[next], dummy);

    long double next_magnitude = -1;
    Vector cur;
    while(top > 0){
        dummy = points[top];
        points[top] = points[next];
        points[next] = dummy;

        long double cosine = -2;
        long double temp;
        for(int i=0; i<N; i++){
            if(i == top) continue;
            cur.init(points[top], points[i]);
            temp = prev.cosine(&cur);
            
            if(temp > (cosine + DBL_EPSILON) || (temp < (cosine + DBL_EPSILON) && temp > (cosine - DBL_EPSILON) && cur.magnitude > next_magnitude)){
                cosine = temp;
                next = i;
                next_magnitude = cur.magnitude;
            }
        }
        
        prev.init(points[top], points[next]);

        if(next > top) break;

        convex++;
        top--;
    }

    printf("%d\n", convex);
}