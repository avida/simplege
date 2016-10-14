#pragma once

#include <boost/noncopyable.hpp>
#include <memory>

namespace generic
{

template <class T>
class singleton : public boost::noncopyable
{
public:
    static T& get_instance()
    { 
        if (!m_instance)
        {
            m_instance = std::unique_ptr<T>(new T());
            m_instance->init_instance(); 
        } 
        return *m_instance; 
    }
    static void destroy_instance() { m_instance = 0; };
protected:
    virtual void init_instance() = 0;
    virtual ~singleton(){}

    static std::unique_ptr<T> m_instance;
private:
};

template<typename T>
std::unique_ptr<T> singleton<T>::m_instance = 0;

} // namespace
