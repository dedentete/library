#define EPS (1e-10)
#define equals(a, b) (fabs((a) - (b)) < EPS)

struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    Point operator+(Point p) {
        return Point(x + p.x, y + p.y);
    }
    Point operator-(Point p) {
        return Point(x - p.x, y - p.y);
    }
    Point operator*(double a) {
        return Point(a * x, a * y);
    }
    Point operator/(double a) {
        return Point(x / a, y / a);
    }

    double abs() {
        return sqrt(norm());
    }
    double norm() {
        return x * x + y * y;
    }

    bool operator<(const Point &p) const {
        return x != p.x ? x < p.x : y < p.y;
    }

    bool operator==(const Point &p) const {
        return fabs(x - p.x) < EPS && fabs(y - p.y) < EPS;
    }
};

bool compX(Point a, Point b) {
    return a.x != b.x ? a.x < b.x : a.y < b.y;
}

bool compY(Point a, Point b) {
    return a.y != b.y ? a.y < b.y : a.x < b.x;
}

typedef Point Vector;

double norm(Vector a) {
    return a.x * a.x + a.y * a.y;
}
double abs(Vector a) {
    return sqrt(norm(a));
}
double dot(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y;
}
double cross(Vector a, Vector b) {
    return a.x * b.y - a.y * b.x;
}

struct Segment {
    Point p1, p2;
    Segment(Point p1 = Point(), Point p2 = Point()) : p1(p1), p2(p2) {}
};

typedef Segment Line;

struct Circle {
    Point c;
    double r;
    Circle(Point c = Point(), double r = 0.0) : c(c), r(r) {}
};

typedef vector<Point> Polygon;

// 直交判定
bool isOrthogonal(Vector a, Vector b) {
    return equals(dot(a, b), 0.0);
}

bool isOrthogonal(Point a1, Point a2, Point b1, Point b2) {
    return isOrthogonal(a1 - a2, b1 - b2);
}

bool isOrthogonal(Segment s1, Segment s2) {
    return equals(dot(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}

// 平行判定
bool isParallel(Vector a, Vector b) {
    return equals(cross(a, b), 0.0);
}

bool isParallel(Point a1, Point a2, Point b1, Point b2) {
    return isParallel(a1 - a2, b1 - b2);
}

bool isParallel(Segment s1, Segment s2) {
    return equals(cross(s1.p2 - s1.p1, s2.p2 - s2.p1), 0.0);
}

// 線分 s に点 p から垂線を引いた交点を求める
Point project(Segment s, Point p) {
    Vector base = s.p2 - s.p1;
    double r = dot(p - s.p1, base) / norm(base);
    return s.p1 + base * r;
}

// 線分 s を対称軸として点 p と線対称の位置にある点を求める
Point reflect(Segment s, Point p) {
    return p + (project(s, p) - p) * 2.0;
}

double getDistance(Point a, Point b) {
    return abs(a - b);
}

double getDistanceLP(Line l, Point p) {
    return abs(cross(l.p2 - l.p1, p - l.p1) / abs(l.p2 - l.p1));
}

double getDistanceSP(Segment s, Point p) {
    if (dot(s.p2 - s.p1, p - s.p1) < 0.0) return abs(p - s.p1);
    if (dot(s.p1 - s.p2, p - s.p2) < 0.0) return abs(p - s.p2);
    return getDistanceLP(s, p);
}

bool intersect(Segment s1, Segment s2);

double getDistanceSS(Segment s1, Segment s2) {
    if (intersect(s1, s2)) return 0.0;
    return min(min(getDistanceSP(s1, s2.p1), getDistanceSP(s1, s2.p2)),
               min(getDistanceSP(s2, s1.p1), getDistanceSP(s2, s1.p2)));
}

static const int COUNTER_CLOCKWISE = 1;
static const int CLOCKWISE = -1;
static const int ONLINE_BACK = 2;
static const int ONLINE_FRONT = -2;
static const int ON_SEGMENT = 0;

int ccw(Point p0, Point p1, Point p2) {
    Vector a = p1 - p0;
    Vector b = p2 - p0;
    if (cross(a, b) > EPS) return COUNTER_CLOCKWISE;
    if (cross(a, b) < -EPS) return CLOCKWISE;
    if (dot(a, b) < -EPS) return ONLINE_BACK;
    if (a.norm() < b.norm()) return ONLINE_FRONT;

    return ON_SEGMENT;
}

// 交差判定
bool intersect(Point p1, Point p2, Point p3, Point p4) {
    return (ccw(p1, p2, p3) * ccw(p1, p2, p4) <= 0 &&
            ccw(p3, p4, p1) * ccw(p3, p4, p2) <= 0);
}

bool intersect(Segment s1, Segment s2) {
    return intersect(s1.p1, s1.p2, s2.p1, s2.p2);
}

Point getCrossPointSS(Segment s1, Segment s2) {
    Vector base = s2.p2 - s2.p1;
    double d1 = abs(cross(base, s1.p1 - s2.p1));
    double d2 = abs(cross(base, s1.p2 - s2.p1));
    double t = d1 / (d1 + d2);
    return s1.p1 + (s1.p2 - s1.p1) * t;
}

pair<Point, Point> getCrossPointCL(Circle c, Line l) {
    Vector pr = project(l, c.c);
    Vector e = (l.p2 - l.p1) / abs(l.p2 - l.p1);
    double base = sqrt(c.r * c.r - norm(pr - c.c));
    return make_pair(pr + e * base, pr - e * base);
}

double arg(Vector p) {
    return atan2(p.y, p.x);
}
Vector polar(double a, double r) {
    return Point(cos(r) * a, sin(r) * a);
}

pair<Point, Point> getCrossPointCC(Circle c1, Circle c2) {
    double d = abs(c1.c - c2.c);
    double a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    double t = arg(c2.c - c1.c);
    return make_pair(c1.c + polar(c1.r, t + a), c1.c + polar(c1.r, t - a));
}

// IN : 2, ON : 1, OUT : 0
int contains(Polygon g, Point p) {
    int n = g.size();
    bool x = false;
    for (int i = 0; i < n; i++) {
        Point a = g[i] - p, b = g[(i + 1) % n] - p;
        if (abs(cross(a, b)) < EPS && dot(a, b) < EPS) return 1;
        if (a.y > b.y) swap(a, b);
        if (a.y < EPS && EPS < b.y && cross(a, b) > EPS) x = !x;
    }
    return (x ? 2 : 0);
}

/*
    凸法を生成
    O(N log N)
*/
Polygon convexHull(Polygon g) {
    int n = g.size();
    sort(g.begin(), g.end(), compX);
    int k = 0;
    Polygon res(n * 2);
    for (int i = 0; i < n; i++) {
        while (k > 1 && cross(res[k - 1] - res[k - 2], g[i] - res[k - 1]) < 0)
            k--;
        res[k++] = g[i];
    }
    for (int i = n - 2, t = k; i >= 0; i--) {
        while (k > t && cross(res[k - 1] - res[k - 2], g[i] - res[k - 1]) < 0)
            k--;
        res[k++] = g[i];
    }
    res.resize(k - 1);
    return res;
}

/*
    凸法の直径を求める
    O(N log N)
*/
double convexDiameter(Polygon g) {
    int n = g.size();
    if (n == 2) return abs(g[0] - g[1]);
    int i = 0, j = 0;
    for (int k = 0; k < n; k++) {
        if (g[i] < g[k]) i = k;
        if (!(g[j] < g[k])) j = k;
    }
    double res = 0;
    int si = i, sj = j;
    while (i != sj || j != si) {
        res = max(res, abs(g[i] - g[j]));
        if (cross(g[(i + 1) % n] - g[i], g[(j + 1) % n] - g[j]) < 0.0) {
            i = (i + 1) % n;
        } else {
            j = (j + 1) % n;
        }
    }
    return res;
}

/*
    最近点対を求める
    O(N log N)
*/
double getClosestPair(Polygon &a, int l = 0, int r = -1) {
    if (r < 0) {
        r = a.size();
        sort(a.begin(), a.end(), compX);
    }
    if (r - l <= 1) return abs(a[0] - a[1]);
    int mid = (l + r) / 2;
    double x = a[mid].x;
    double d = min(getClosestPair(a, l, mid), getClosestPair(a, mid, r));
    inplace_merge(a.begin() + l, a.begin() + mid, a.begin() + r, compY);

    Polygon b;
    for (int i = l; i < r; i++) {
        if (abs(a[i].x - x) >= d) continue;
        for (int j = 0; j < b.size(); j++) {
            double dy = a[i].y - next(b.rbegin(), j)->y;
            if (dy >= d) break;
            d = min(d, abs(a[i] - *next(b.rbegin(), j)));
        }
        b.push_back(a[i]);
    }
    return d;
}