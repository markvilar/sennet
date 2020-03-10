#include <boost/cstdint.hpp>

#include <sl/Camera.hpp>

#include <vector>

sl::Mat flattenMat(sl::Mat x);
std::vector<boost::uint8_t> slMat2Vec(sl::Mat& x);
