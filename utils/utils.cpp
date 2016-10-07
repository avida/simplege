#include "utils.hpp"
#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>

namespace utils
{
std::string LoadFile(const std::string& fname)
{
    auto name = boost::filesystem::file_size(fname);
    return boost::lexical_cast<std::string>(name);    
}

}