#include <test/plot.h>
#include <matplotlibcpp.h>
#include <vector>

bool plt::plot(const Eigen::Ref<const Eigen::ArrayXXf>& y)
{
    bool flag = true;
    std::vector<float> yVec;
    yVec.resize(y.rows());
    for (auto i = 0; i < y.cols(); i++)
    {
        for (auto j=0;j<y.rows();j++)
        {
            yVec[j] = y(j,i);
        }
        flag &= matplotlibcpp::plot(yVec);
    }
    return flag;
}
    

bool plt::plot(const Eigen::Ref<const Eigen::ArrayXXf>& x, const Eigen::Ref<const Eigen::ArrayXXf>& y)
{
    if (x.cols() != y.cols()) { return false; }
    if (x.rows() != y.rows()) { return false; }

    bool flag = true;;
    for (auto i = 0; i < y.cols(); i++)
    {
        std::vector<float> xVec, yVec;
        yVec.resize(y.rows());
        xVec.resize(y.rows());
        for (auto j=0;j<y.rows();j++)
        {
            xVec[j] = x(j,i);
            yVec[j] = y(j,i);
        }
        flag &= matplotlibcpp::plot(xVec, yVec);
    }
    return flag;
}

void plt::figure(int plotNumber = -1)
{
    matplotlibcpp::figure(plotNumber);
}

void plt::title(const char *text)
{
    matplotlibcpp::title(text);
}

void plt::save(const char *text)
{
    matplotlibcpp::save(text);
}

void plt::xlabel(const char *text)
{
    matplotlibcpp::xlabel(text);
}

void plt::ylabel(const char *text)
{
    matplotlibcpp::ylabel(text);
}
    
void plt::xlim(const float xMin, const float xMax)
{
    matplotlibcpp::xlim(xMin, xMax);
}

void plt::ylim(const float yMin, const float yMax)
{
    matplotlibcpp::ylim(yMin, yMax);
}

void plt::grid()
{
    matplotlibcpp::grid(true);
}
