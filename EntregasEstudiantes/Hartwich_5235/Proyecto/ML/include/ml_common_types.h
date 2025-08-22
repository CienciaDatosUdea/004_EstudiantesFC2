#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-variable" // this flag triggered warnings about code from the Eigen header when run with -march=native
#include <Eigen/Dense>
#pragma GCC diagnostic pop

// type definitions used throughout this part of the project

using Index = Eigen::Index;
