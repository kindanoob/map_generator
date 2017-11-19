#ifndef UTIL_H_
#define UTIL_H_

#include <vector>
#include <utility>

namespace Util {
    double dist_squared_from_point_to_point(double x0, double y0, double x1, double y1);
    double dist_from_point_to_point(double x0, double y0, double x1, double y1);
    double dist_from_point_to_line(double point_x, double point_y,
                                   double line_a, double line_b, double line_c);

    bool cmp_tile_connected_components_by_size_descending(std::vector<std::pair<int, int> >& cc1,
                                           std::vector<std::pair<int, int> >& cc2);
}

#endif // UTIL_H_
