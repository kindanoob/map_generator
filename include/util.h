#ifndef UTIL_H_
#define UTIL_H_

#include <vector>
#include <utility>

namespace Util {
    double DistSquaredFromPointToPoint(double x0, double y0, double x1, double y1);
    double DistFromPointToPoint(double x0, double y0, double x1, double y1);
    double DistFromPointToLine(double point_x, double point_y,
                                   double line_a, double line_b, double line_c);

    bool CmpTileConnectedComponentsBySizeDescending(std::vector<std::pair<int, int> >& cc1,
                                           std::vector<std::pair<int, int> >& cc2);
}

#endif // UTIL_H_
