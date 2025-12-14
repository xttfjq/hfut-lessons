#include <iostream>
#include <cmath>
#include <iomanip>
#define _USE_MATH_DEFINES
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

using namespace std;

struct Point {
    double x, y, z;
    Point(double x = 0, double y = 0, double z = 0) : x(x), y(y), z(z) {}
};

// 计算两点间的距离
double distance(const Point& a, const Point& b) {
    double dx = a.x - b.x;
    double dy = a.y - b.y;
    double dz = a.z - b.z;
    return sqrt(dx * dx + dy * dy + dz * dz);
}

// 计算数量积
double dot(const Point& a, const Point& b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

int main() {
    Point A, B, C;
    int R;
    cin >> A.x >> A.y >> A.z;
    cin >> B.x >> B.y >> B.z;
    cin >> C.x >> C.y >> C.z;
    cin >> R;

    // 向量AB和AC
    Point AB_vec(B.x - A.x, B.y - A.y, B.z - A.z);
    Point AC_vec(C.x - A.x, C.y - A.y, C.z - A.z);

    double ab_dot_ac = dot(AB_vec, AC_vec);//数量积（用于计算投影）
    double ab_len_sq = dot(AB_vec, AB_vec);//AB长度的平方
    double ac_len = distance(A, C);
    double bc_len = distance(B, C);
    double ab_len = distance(A, B);

    double d; //点c到线段AB的最短距离
    if (ab_len_sq < 1e-8) {  // A和B重合
        d = ac_len;
    }
    else {
        double t = ab_dot_ac / ab_len_sq;  // c在线段AB上的投影位置
        if (t < 0) {  // 投影在A的外侧，最短距离是A到C的距离
            d = ac_len;
        }
        else if (t > 1) {  // 投影在B的外侧，最短距离是B到C的距离
            d = bc_len;
        }
        else {  // 投影在线段AB上，最短距离是垂线距离
            d = sqrt(ac_len * ac_len - ab_dot_ac * ab_dot_ac / ab_len_sq);
        }
    }

    if (d >= R - 1e-8) {  // 线段AB不与球体相交，直接返回直线距离
        cout << fixed << setprecision(2) << ab_len << endl;
    }
    else {  // 线段AB穿过球体，计算绕开路径
        double ap = sqrt(ac_len * ac_len - R * R);  // A到切点的切线长
        double bq = sqrt(bc_len * bc_len - R * R);  // B到切点的切线长

        // 向量CA和CB（从球心C指向A、B）
        Point CA(A.x - C.x, A.y - C.y, A.z - C.z);
        Point CB(B.x - C.x, B.y - C.y, B.z - C.z);

        // 计算CA和CB的夹角θ
        double ca_dot_cb = dot(CA, CB); //向量CA和CB的数量积
        double cos_theta = ca_dot_cb / (ac_len * bc_len); //夹角余弦值
        cos_theta = max(min(cos_theta, 1.0), -1.0);  // 防止精度溢出导致acos出错
        double theta = acos(cos_theta); //夹角

        // 计算切线与半径的夹角β
        double cos_beta = R / ac_len;
        cos_beta = max(min(cos_beta, 1.0), -1.0);
        double beta = acos(cos_beta);

        // 球面上两切点的圆心角φ
        double phi = theta - 2 * beta;
        if (phi < 0) phi += 2 * M_PI;  // 确保角度为正

        // 总路径 = 切线长AP + 切线长BQ + 圆弧长PQ
        double pq_arc = R * phi;
        double total = ap + bq + pq_arc;

        cout << fixed << setprecision(2) << total << endl;
    }

    return 0;
}