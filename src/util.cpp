#include <cmath>
#include "util.h"


namespace Util {
    double DistSquaredFromPointToPoint(double x0, double y0, double x1, double y1) {
        double dx = x0 - x1;
        double dy = y0 - y1;
        return dx * dx + dy * dy;
    }

    double DistFromPointToPoint(double x0, double y0, double x1, double y1) {
        return sqrt(DistSquaredFromPointToPoint(x0, y0, x1, y1));
    }

    //line equation: y = a * x + b, ignore vertical line case for now
    double DistFromPointToLine(double point_x, double point_y,
                                   double line_a, double line_b, double line_c) {
        return fabs(line_a * point_x + line_b * point_y + line_c) / sqrt(line_a * line_a + line_b * line_b);
    }

    bool CmpTileConnectedComponentsBySizeDescending (
                std::vector<std::pair<int, int> >& cc1, std::vector<std::pair<int, int> >& cc2) {
        return cc1.size() > cc2.size();
    }
}
