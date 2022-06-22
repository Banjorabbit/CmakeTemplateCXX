#include "Tutorial.h"
#include "TutorialConfig.h"
#include <Eigen/Core>
#include <fmt/core.h>
#include <iostream>

int main(int argc, char* argv[])
{

    fmt::print("Hello world!\n");

    if (argc < 2) 
    {
        // report version
		fmt::print("{0} Version {1}.{2}.{3}\n", argv[0], Tutorial_VERSION_MAJOR, Tutorial_VERSION_MINOR, Tutorial_VERSION_PATCH);
		fmt::print("Usage: {} number\n", argv[0]);
        return 1;
    }

    const double inputValue = std::stod(argv[1]);
	fmt::print("Input value: {}\n", inputValue);
    
    const double outputValue = mysqrt(inputValue);
	
	fmt::print("Output value: {}\n", outputValue);
 
    Eigen::ArrayXf outEigen(3);
	outEigen = static_cast<float>(outputValue);
	fmt::print("Values in eigen array: {0}, {1}, {2}\n", outEigen(0),outEigen(1),outEigen(2));
	std::cout << "Eigen array: " << outEigen << "\n";
	
    return 0;
}
