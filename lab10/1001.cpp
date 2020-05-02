#include <bits/stdc++.h>
#define mp make_pair
#define pub push_back
#define pob pop_back
#define pof pop_front
#define pii pair<int, int>
#define fi first
#define se second
#define MOD 1000000007
#define MOD2 998244353
#define LL long long
#define ULL unsigned long long
#define ui unsigned int
#define bas 26
#define bas2 131
using namespace std;
const int N = 200005;
const int M = 8000005;
const int INF = 1000000000;
typedef double db;
const db eps = 1e-8;
const db pi = acos(-1);
const db inf = 1e30;
inline int sign(db a) { return a < -eps ? -1 : a > eps;}
inline int cmp(db a, db b) {return sign(a - b);}
inline int inmid(db a, db b, db c) 
{return sign(a - c) * sign(b - c) <= 0;}//c在[a,b]内
//L line S segment P point
struct point {
    db x, y;
    point() {}
    point(db _x, db _y): x(_x), y(_y) {}
    point operator + (const point &p) const {return point(x + p.x, y + p.y);}
    point operator - (const point &p) const {return point(x - p.x, y - p.y);}
    point operator * (db k) const {return point(x * k, y * k);}
    point operator / (db k) const {return point(x / k, y / k);}
    int operator == (const point &p) const 
    {return cmp(x, p.x) == 0 && cmp(y, p.y) == 0;}
    point turn(db k) {return point(x * cos(k) - y * sin(k), x * sin(k) + y * cos(k));}
    point turn90() {return point(-y, x);}
    bool operator < (const point &p) const {
        int c = cmp(x, p.x);
        if(c) return c == -1;
        return cmp(y, p.y) == -1;
    }
    bool operator > (const point &p) const {
        int c = cmp(x, p.x);
        if(c) return c == 1;
        return cmp(y, p.y) == 1;
    }
    db abs() {return sqrt(x * x + y * y);}
    db abs2() {return x * x + y * y;}
    db disto(point p) {return (*this - p).abs();}
    db alpha() {return atan2(y, x);}
    point unit() {db z = abs(); return point(x / z, y / z);}
    void scan() {db _x, _y; scanf("%lf%lf", &_x, &_y); x = _x, y = _y;}
    void print() {printf("%.11lf %.11lf\n", x, y);}
    point getdel() 
    {return (sign(x)==-1||(sign(x)==0&&sign(y)==-1))?(*this)*(-1):(*this);}
    int getP() const{return sign(y) == 1 || (!sign(y) && sign(x) == -1);}//向量相对方向
};
int inmid(point p1, point p2, point p3)
{return inmid(p1.x, p2.x, p3.x) && inmid(p1.y, p2.y, p3.y);}
db dot(point p1, point p2) {return p1.x * p2.x + p1.y * p2.y;}
db cross(point p1, point p2) {return p1.x * p2.y - p1.y * p2.x;}
db rad(point p1, point p2) {return atan2(cross(p1, p2), dot(p1, p2));}
int compareangle(point p1, point p2) {
    return p1.getP() < p2.getP() || (p1.getP() == p2.getP() && sign(cross(p1, p2)) > 0);
}
point proj(point p1, point p2, point q) {
//q到直线p1, p2的投影
    point p = p2 - p1;
    return p1 + p * (dot(q - p1, p) / p.abs2());
}
point reflect(point p1, point p2, point q) {return proj(p1, p2, q) * 2 - q;}
int clockwise(point p1, point p2, point p3) {
//p1, p2, p3 逆时针 1 顺时针 -1 其他 0
    return sign(cross(p2 - p1, p3 - p1));
}
int checkLL(point p1, point p2, point p3, point p4) {
//求直线p1, p2 和直线p3, p4是否有交点
    return cmp(cross(p3 - p1, p4 - p1), cross(p3 - p2, p4 - p2)) != 0;
}
point getLL(point p1, point p2, point p3, point p4) {
//求直线p1, p2 和直线p3, p4的交点
    db w1 = cross(p1 - p3, p4 - p3), w2 = cross(p4 - p3, p2 - p3);
    return (p1 * w2 + p2 * w1) / (w1 + w2);
}
int intersect(db l1, db r1, db l2, db r2) {
//判断两个区间(l1, r1)和(l2, r2)是否有交
    if(l1 > r1) swap(l1, r1);
    if(l2 > r2) swap(l2, r2);
    return cmp(r1, l2) != -1 && cmp(r2, l1) != -1;
}
int checkSS(point p1, point p2, point p3, point p4) {
    //判断线段p1, p2和线段p3, p4是否有交点
    return intersect(p1.x, p2.x, p3.x, p4.x) && intersect(p1.y, p2.y, p3.y, p4.y) &&
    sign(cross(p3 - p1, p4 - p1)) * sign(cross(p3 - p2, p4 - p2)) <= 0 &&
    sign(cross(p1 - p3, p2 - p3)) * sign(cross(p1 - p4, p2 - p4)) <= 0;
}
db disSP(point p1, point p2, point q) {//点到线段的距离
    point p3 = proj(p1, p2, q);
    return inmid(p1, p2, p3) ? q.disto(p3) : min(q.disto(p1), q.disto(p2));
}
db disSS(point p1, point p2, point p3, point p4) {
    if(checkSS(p1, p2, p3, p4)) return 0;
    return min(min(disSP(p1, p2, p3), disSP(p1, p2, p4)), 
                min(disSP(p3, p4, p1), disSP(p3, p4, p2)));
}
int onS(point p1, point p2, point q) {
    return inmid(p1, p2, q) && sign(cross(p1 - q, p2 - q)) == 0;
}
struct circle {
    point o; db r;
    circle(point _o, db _r): o(_o), r(_r) {}
    void scan() {o.scan(); scanf("%lf", &r);}
    int inside(point p) {return cmp(r, o.disto(p));}
};
struct line {//ps[0] -> ps[1] 有向直线
    point ps[2];
    line(point p1, point p2) {ps[0] = p1, ps[1] = p2;}
    point& operator[] (int k) {return ps[k];}
    int include(point p) {return sign(cross(ps[1] - ps[0], p - ps[0])) > 0;}
    //在这个半平面内
    point dir() {return ps[1] - ps[0];}
    line push() {//向外平移eps
        point delta = (ps[1] - ps[0]).turn90().unit() * eps;
        return line(ps[0] - delta, ps[1] - delta);
    }
};
point getLL(line l1, line l2) {return getLL(l1[0], l1[1], l2[0], l2[1]);}
int checkLL(line l1, line l2) {return checkLL(l1[0], l1[1], l2[0], l2[1]);}
int parallel(line l1, line l2) {return sign(cross(l1.dir(), l2.dir())) == 0;}
int samedir(line l1, line l2) 
{return parallel(l1, l2) && sign(dot(l1.dir(), l2.dir())) == 1;}
int operator < (line l1, line l2) {
    if(samedir(l1, l2)) return l2.include(l1[0]);
    return compareangle(l1.dir(), l2.dir());
}
db area(vector<point> ps) {
    db res = 0;
    for(int i = 0, l = (int)ps.size(); i < l; ++i) 
        res += cross(ps[i], ps[(i + 1) % l]);
    return fabs(res / 2);
}
int contain(vector<point> ps, point p) {
//2:内部 1:边界 0:外部
    int n = (int)ps.size(), res = 0;
    for(int i = 0; i < n; ++i) {
        point p1 = ps[i], p2 = ps[(i + 1) % n];
        if(onS(p1, p2, p)) return 1;
        if(cmp(p1.y, p2.y) > 0) swap(p1, p2);
        if(cmp(p1.y, p.y) >= 0 || cmp(p2.y, p.y) < 0) continue;
        if(sign(cross(p1 - p2, p - p2)) < 0) res ^= 1;
    }
    return res << 1;
}
int convex(vector<point> ps) {
    int n = ps.size(); if(n <= 1) return n;
    sort(ps.begin(), ps.end());
    vector<point> qs(n * 2); int k = 0;
    for(int i = 0; i < n; qs[k++] = ps[i++]) {
        while(k > 1 && sign(cross(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 2])) < 0) --k;
    }
    for(int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--]) {
        while(k > t && sign(cross(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 2])) < 0) --k;
    }
    return k - 1;
}
vector<point> convexNonStrict(vector<point> ps) {
    //需要所有点都是独一的 结果会把边界上的点都算进去
    int n = ps.size(); if(n <= 1) return ps;
    sort(ps.begin(), ps.end());
    vector<point> qs(n * 2); int k = 0;
    for(int i = 0; i < n; qs[k++] = ps[i++]) {
        while(k > 1 && sign(cross(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 2])) < 0) --k;
    }
    for(int i = n - 2, t = k; i >= 0; qs[k++] = ps[i--]) {
        while(k > t && sign(cross(qs[k - 1] - qs[k - 2], ps[i] - qs[k - 2])) < 0) --k;
    }
    qs.resize(k - 1);
    return qs;
}
db convexDiameter(vector<point> ps) {
    int n = (int)ps.size(); if(n <= 1) return 0;
    int is = 0, js = 0;
    for(int k = 1; k < n; ++k) {
        is = ps[k] < ps[is] ? k : is;
        js = ps[js] < ps[k] ? k : js;
    }
    int i = is, j = js;
    db res = ps[i].disto(ps[j]);
    do {
        if(cross(ps[(i + 1) % n] - ps[i], ps[(j + 1) % n] - ps[j]) >= 0) 
            j = (j + 1) % n;
        else i = (i + 1) % n;
        res = max(res, ps[i].disto(ps[j]));
    }while(i != is || j != js);
    return res;
}
vector<point> convexCut(const vector<point> &ps, point p1, point p2) {
    vector<point> qs;//凸包与这条直线必须同向
    int n = (int)ps.size();
    for(int i = 0; i < n; ++i) {
        point p3 = ps[i], p4 = ps[(i + 1) % n];
        int d1 = sign(cross(p2 - p1, p3 - p1)), d2 = sign(cross(p2 - p1, p4 - p1));
        if(d1 >= 0) qs.pub(p3);
        if(d1 * d2 < 0) qs.pub(getLL(p1, p2, p3, p4));
    }
    return qs;
}
bool cmpy(const point &lhs, const point &rhs) {return lhs.y < rhs.y;}
db closepoint(vector<point> &ps, int l, int r) {
//最近点对，先要按照x排序 //还可以优化成nlogn
    if(r - l <= 5) {
        db res = inf;
        for(int i = l; i < r; ++i) {
            for(int j = i + 1; j <= r; ++j) res = min(res, ps[i].disto(ps[j]));
        }
        return res;
    }
    int mid = (l + r) >> 1, tx = ps[mid].x;
    db res = min(closepoint(ps, l, mid), closepoint(ps, mid + 1, r));
    vector<point> qs;
    for(int i = l; i <= r; ++i) if(abs(ps[i].x - tx) <= res) qs.pub(ps[i]);
    sort(qs.begin(), qs.end(), cmpy); int len = (int)qs.size();
    for(int i = 0; i < len; ++i) {
        for(int j = i + 1; j < len && qs[j].y - qs[i].y; ++j) 
            res = min(res, qs[i].disto(qs[j]));
    }
    return res;
}
int checkpos(line l1, line l2, line l3) {return l3.include(getLL(l1, l2));}
vector<point> getHalfPlane(vector<line> &L) {
//求半平面交，半平面是逆时针方向，输出按逆时针
    sort(L.begin(), L.end()); deque<line> q;
    for(int i = 0, il = (int)L.size(); i < il; ++i) {
        if(i && samedir(L[i], L[i - 1])) continue;
        while(q.size() > 1 && !checkpos(q[q.size() - 2], q[q.size() - 1], L[i])) 
            q.pob();
        while(q.size() > 1 && !checkpos(q[0], q[1], L[i])) 
            q.pof();
        q.pub(L[i]);
    }
    while(q.size() > 2 && !checkpos(q[q.size() - 2], q[q.size() - 1], q[0])) 
        q.pob();
    while(q.size() > 2 && !checkpos(q[1], q[0], q[q.size() - 1])) 
        q.pof();
    vector<point> res;
    for(int i = 0, l = (int)q.size(); i < l; ++i) 
        res.pub(getLL(q[i], q[(i + 1) % l]));
    return res;
}
int checkposCC(circle c1, circle c2) { 
//返回两个圆公切线数量
    if(cmp(c1.r, c2.r) == -1) swap(c1, c2);
    db dis = c1.o.disto(c2.o);
    int w1 = cmp(dis, c1.r + c2.r), w2 = cmp(dis, c1.r - c2.r);
    if(w1 > 0) return 4; else if(!w1) return 3; else if(w2 > 0) return 2;
    else if(!w2) return 1; else return 0;
}
vector<point> getCL(circle c, point p1, point p2) {
//沿着p1 -> p2方向給出，相切給出两个
    point p = proj(p1, p2, c.o); db d = c.r * c.r - (p - c.o).abs2();
    if(sign(d) == -1) return {};
    point delta = (p2 - p1).unit() * sqrt(max(0.0, d));
    return {p - delta, p + delta};
}
vector<point> getCC(circle c1, circle c2) { 
//沿c1逆时针給出，相切給出两个
    int pd = checkposCC(c1, c2); if(pd == 0 || pd == 4) return {};
    db a = (c1.o - c2.o).abs2();
    db cosA = (c1.r * c1.r + a - c2.r * c2.r) / (2 * c1.r * sqrt(max(0.0, a)));
    db b = c1.r * cosA, c = sqrt(max(0.0, c1.r * c1.r - b * b));
    point t = (c2.o - c1.o).unit(), p = c1.o + t * b, delta = t.turn90() * c;
    return {p - delta, p + delta};
}
vector<point> tangentCP(circle c1, point p1) {
//沿c逆时针给出两个切点
    db a = (p1 - c1.o).abs(), b = c1.r * c1.r / a;
    db c = sqrt(max(0.0, c1.r * c1.r - b * b));
    point t = (p1 - c1.o).unit(), mid = c1.o + t * b, delta = t.turn90() * c;
    return {mid - delta, mid + delta};
}
vector<line> tangentoutCC(circle c1, circle c2) {//只有外切线
    int pd = checkposCC(c1, c2); if(!pd) return {};
    if(pd == 1) {point p = getCC(c1, c2)[0]; return {line(p, p)};}
    if(cmp(c1.r, c2.r) == 0) {
        point delta = (c2.o - c1.o).unit().turn90().getdel();
        return {line(c1.o - delta * c1.r, c2.o - delta * c2.r), 
            line(c1.o + delta * c1.r, c2.o + delta * c2.r)};
    }
    else {
        point p = (c1.o * c2.r - c2.o * c1.r) / (c2.r - c2.r);
        vector<point> A = tangentCP(c1, p), B = tangentCP(c2, p);
        vector<line> res;
        for(int i = 0, l = (int)A.size(); i < l; ++i) res.pub(line(A[i], B[i]));
        return res;
    }
}
vector<line> tangentinCC(circle c1, circle c2) {
    int pd = checkposCC(c1, c2); if(pd <= 2) return {};
    if(pd == 3) {point p = getCC(c1, c2)[0]; return {line(p, p)};}
    point p = (c1.o * c2.r + c2.o * c1.r) / (c1.r + c2.r);
    vector<point> A = tangentCP(c1, p), B = tangentCP(c2, p);
    vector<line> res;
    for(int i = 0, l = (int)A.size(); i < l; ++i) res.pub(line(A[i], B[i]));
    return res;
}
vector<line> tangentCC(circle c1, circle c2) {
    int flag = 0; if(c1.r < c2.r) swap(c1, c2), flag = 1;
    vector<line> A = tangentoutCC(c1, c2), B = tangentinCC(c1, c2);
    for(line k: B) A.pub(k);
    if(flag) for(line &k: A) swap(k[0], k[1]);
    return A;
}
db areaCT(circle c1, point p2, point p3) {
//圆c1和三角形p1, p2, c1.o的有向面积交
    point p1 = c1.o; c1.o = c1.o - p1; p2 = p2 - p1; p3 = p3 - p1;
    int pd1 = c1.inside(p2), pd2 = c1.inside(p3);
    vector<point> A = getCL(c1, p2, p3);
    if(pd1 >= 0) {
        if(pd2 >= 0) return cross(p2, p3) / 2;
        else return c1.r * c1.r * rad(A[1], p3) / 2 + cross(p2, A[1]) / 2;
    }
    else if(pd2 >= 0) return c1.r * c1.r * rad(p2, A[0]) / 2 + cross(A[0], p3) / 2;
    else {
        int pd = cmp(c1.r, disSP(p2, p3, c1.o));
        if(pd <= 0) return c1.r * c1.r * rad(p2, p3) / 2;
        else return c1.r * c1.r * (rad(p2, A[0]) + rad(A[1], p3)) / 2 
            + cross(A[0], A[1]) / 2;
    }
}
circle getcircle(point p1, point p2, point p3) {//返回3个点的外接圆
    db a1 = p2.x - p1.x, b1 = p2.y - p1.y, c1 = (a1 * a1 + b1 * b1) / 2;
    db a2 = p3.x - p1.x, b2 = p3.y - p1.y, c2 = (a2 * a2 + b2 * b2) / 2;
    db d = a1 * b2 - a2 * b1;
    point o = point(p1.x + (c1 * b2 - c2 * b1) / d, p1.y + (c2 * a1 - c1 * a2) / d);
    return circle(o, p1.disto(o));
}
circle getScircle(vector<point> ps) {
    random_shuffle(ps.begin(), ps.end());
    circle res = circle(ps[0], 0);
    int n = (int)ps.size();
    for(int i = 1; i < n; ++i) if(res.inside(ps[i]) == -1) {
        res = circle(ps[i], 0);
        for(int j = 0; j < i; ++j) if(res.inside(ps[j]) == -1) {
            res.o = (ps[i] + ps[j]) / 2; res.r = res.o.disto(ps[i]);
            for(int k = 0; k < j; ++k) {
                if(res.inside(ps[k]) == -1) res = getcircle(ps[i], ps[j], ps[k]);
            }
        }
    }
    return res;
}
typedef pair<db, int> pdi;
point a[N];
pdi alp[N << 2];
bool cmp_alp(const pdi &lhs, const pdi &rhs) {
    if(sign(lhs.fi - rhs.fi) == 0) return lhs.se < rhs.se;
    else return lhs.fi < rhs.fi;
}
bool check(db R, int n, int s) {
//判断半径为R的圆能否覆盖s个点，最后的res+1位最多可覆盖的点数
    int res = 0;
    for(int i = 1; i <= n; ++i) {
        int sum = 0, tot = 0;
        for(int j = 1; j <= n; ++j) {
            db dis = a[i].disto(a[j]);
            if(i == j || sign(dis - R * 2) > 0) continue;
            db theta = atan2(a[j].y - a[i].y, a[j].x - a[i].x);
            if(theta < 0) theta += pi * 2;
            db phi = acos(dis / (R * 2));
            db le = theta - phi, ri = theta + phi;
            if(sign(le) >= 0 && sign(ri - 2 * pi) <= 0) {
                alp[++tot] = mp(le, 1);
                alp[++tot] = mp(ri, -1);
            }
            else if(sign(le) < 0) {
                alp[++tot] = mp(0, 1);
                alp[++tot] = mp(ri, -1);
                alp[++tot] = mp(le + 2 * pi, 1);
                alp[++tot] = mp(2 * pi, -1);
            }
            else {
                alp[++tot] = mp(0, 1);
                alp[++tot] = mp(ri - 2 * pi, -1);
                alp[++tot] = mp(le, 1);
                alp[++tot] = mp(2 * pi, -1);
            }
        }
        sort(alp + 1, alp + tot + 1, cmp_alp);
        for(int i = 1; i <= tot; ++i) {
            sum += alp[i].se;
            res = max(res, sum);
        }
    }
    return res + 1 >= s;
}
struct CH {
    int n;
    vector<point> ps, lower, upper;
    point operator[] (int i) {return ps[i];}

    int Find(vector<point> &vec, point dir) {
        int l = 0, r = vec.size();
        while(l + 5 < r) {
            int L = (l * 2 + r) / 3, R = (l + r * 2) / 3;
            if(dot(vec[L], dir) > dot(vec[R], dir)) r = R;
            else l = L;
        }
        int res = l;
        for(int i = l + 1; i < r; ++i) 
            if(dot(vec[i], dir) > dot(vec[res], dir)) res = i;
        return res;
    }
    void init(vector<point> _ps) {
        ps = _ps, n = ps.size();
        rotate(ps.begin(), min_element(ps.begin(), ps.end()), ps.end());
        int id = max_element(ps.begin(), ps.end()) - ps.begin();
        lower = vector<point>(ps.begin(), ps.begin() + id + 1);
        upper = vector<point>(ps.begin() + id, ps.end()); upper.pub(ps[0]);
    }
    int findfarest(point dir) {
        if(dir.y > 0 || (dir.y == 0 && dir.x > 0)) {
            return ((int)lower.size() - 1 + Find(upper, dir)) % n;
        }
        else {
            return Find(lower, dir);
        }
    }
    point get(int l, int r, point p1, point p2) {
        int sl = sign(cross(p2 - p1, ps[l % n] - p1));
        while(l + 1 < r) {
            int mid = (l + r) >> 1;
            if(sign(cross(p2 - p1, ps[mid % n] - p1)) == sl) l = mid;
            else r = mid;
        }
        return getLL(p1, p2, ps[l % n], ps[(l + 1) % n]);
    }
    vector<point> getIS(point p1, point p2) {
        int X = findfarest((p2 - p1).turn90());
        int Y = findfarest((p1 - p2).turn90());
        if(X > Y) swap(X, Y);
        if(sign(cross(p2 - p1, ps[X] - p1)) * sign(cross(p2 - p1, ps[Y])) < 0) {
            return {get(X, Y, p1, p2), get(Y, X + n, p1, p2)};
        }
        else {
            return {};
        }
    }
    void update_tangent(point p, int id, int &a, int &b) {
        if(sign(cross(ps[a] - p, ps[id] - p)) > 0) a = id;
        if(sign(cross(ps[b] - p, ps[id] - p)) > 0) b = id;
    }
    void Binary_Search(int l, int r, point p, int &a, int &b) {
        if(l == r) return;
        update_tangent(p, l % n, a, b);
        int sl = sign(cross(ps[l % n] - p, ps[(l + 1) % n] - p));
        while(l + 1 < r) {
            int mid = (l + r) >> 1;
            if(sign(cross(ps[mid % n] - p, ps[(mid + 1) % n] - p)) == sl) l = mid;
            else r = mid;
        }
        update_tangent(p, r % n, a, b);
    }
    bool contain(point p) {//是否在凸包内
        if(p.x < lower[0].x || p.x > lower.back().x) return 0;
        int id = lower_bound(lower.begin(), lower.end(), point(p.x, -INF))
         - lower.begin();
        if(lower[id].x == p.x) {
            if(lower[id].y > p.y) return 0;
        }
        else {
            if(sign(cross(lower[id] - lower[id - 1], p - lower[id - 1])) < 0) 
                return 0;
        }
        id = lower_bound(upper.begin(), upper.end(), point(p.x, INF), greater<point>())
         - upper.begin();
        if(upper[id].x == p.x) {
            if(upper[id].y < p.y) return 0;
        }
        else {
            if(sign(cross(upper[id] - upper[id - 2], p -  upper[id - 1])) < 0) 
                return 0;
        }
        return 1;
    }
    bool get_tangent(point p, int &a, int &b) {//求切线
        if(contain(p)) return 0;
        a = b = 0;
        int id = lower_bound(lower.begin(), lower.end(), p) - lower.begin();
        Binary_Search(0, id, p, a, b);
        Binary_Search(id, lower.size(), p, a, b);
        id = lower_bound(upper.begin(), upper.end(), p, greater<point>()) 
        - upper.begin();
        Binary_Search((int)lower.size() - 1, (int)lower.size() - 1 + id, p, a, b);
        Binary_Search((int)lower.size() - 1 + id, 
            (int)lower.size() - 1 + upper.size(), p, a, b);
        return 0;
    }
};

vector<point> ps;

int main() {
    int n; scanf("%d", &n);
    for(int i = 0; i < n; i++) {
        double x, y; scanf("%lf%lf", &x, &y);
        ps.push_back(point(x, y));
    }
    printf("%d\n", convex(ps));
    return 0;
}