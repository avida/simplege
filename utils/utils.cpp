#include "utils.hpp"
#include "utils/logger.hpp"

#include <boost/filesystem.hpp>
#include <boost/lexical_cast.hpp>
#include <sstream>

const int maxFileSize = 1024 * 1024;
namespace utils
{

std::string LoadFile(const std::string& fname)
{
    boost::filesystem::ifstream file_stream;
    file_stream.open(fname, std::ios::in);
    if (!file_stream)
    {
        gl::LogFatal("Cannot open file " + fname);
    }
    auto fsize = boost::filesystem::file_size(fname);
    if (fsize >= maxFileSize)
    {
        gl::LogFatal(fname + " too big to be loaded");
    }
    std::stringstream sstream;
    sstream << file_stream.rdbuf();
    return sstream.str();
}

}