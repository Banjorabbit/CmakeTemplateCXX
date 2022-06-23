#include <Tutorial.h>
#include <test.h>

using namespace Eigen;

// a hack square root calculation using simple operations
double mysqrt(double x)
{
  
  if (x <= 0) {
    return 0;
  }

  double result = x;

  // do ten iterations
  for (int i = 0; i < 10; ++i) {
    if (result <= 0) {
      result = 0.1;
    }
    double delta = x - (result * result);
    result = result + 0.5 * delta / result;
  }
  return result;
}


TEST_CASE("Test Doctest")
{
  ArrayXf x(4);
  x << 1, 3, 3, 4;

  plt::plot(x);
  plt::save("mysqrt.png");
  CHECK(doctest::Approx(3.f) == mysqrt(9.f));
}

TEST_CASE("Test Doctest3")
{
	//plt::figure(3);
  ArrayXf x(5);
  x << 1, 3, 2, 4, 5;
  plt::plot(x);
  plt::save("mysqrt2.png");
  CHECK(doctest::Approx(2.f) == mysqrt(4.f));
}
