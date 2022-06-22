#include <Tutorial.h>

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

#ifdef ENABLE_TESTS
#include <tests.h>

TEST_CASE("Test Doctest")
{
  plt::plot({1,3,2,4});
  plt::save("mysqrt.png");
  CHECK(doctest::Approx(3.f) == mysqrt(9.f));
}

TEST_CASE("Test Doctest2")
{
  plt::plot({1,3,2,4,5});
  plt::save("mysqrt2.png");
  CHECK(doctest::Approx(2.f) == mysqrt(4.f));
}
#endif