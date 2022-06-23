#pragma once
#include <Eigen/Dense>

namespace plt
{
    bool plot(const Eigen::Ref<const Eigen::ArrayXXf>& y);
    bool plot(const Eigen::Ref<const Eigen::ArrayXXf>& x, const Eigen::Ref<const Eigen::ArrayXXf>& y);

    void figure(int plotNumber); // open new/select figure

    // avoid using std::string so we don't have to pull in unnecessary std headers in production code
    void title(const char *text);
    void save(const char *text); 
    void xlabel(const char *text);
    void ylabel(const char *text);
    
    void xlim(const float xMin, const float xMax);
    void ylim(const float yMin, const float yMax);

    void grid();
}
