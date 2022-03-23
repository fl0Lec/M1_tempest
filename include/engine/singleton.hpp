/**
 * @file singleton.hpp
 * @brief Base for classes usually statically hosting a unique instance of
 *  themselves 
 */

#ifndef __SINGLETON_H__
#define __SINGLETON_H__

#include <memory>

namespace Engine
{

template<class T>
class Singleton
{
public:
    static const std::shared_ptr<T>& getInstance()
    {
        return m_instance;
    }

    static void setInstance(const std::shared_ptr<T>& instance)
    {
        m_instance = instance;
    }

private:
    static std::shared_ptr<T> m_instance;

};

template<class T>
std::shared_ptr<T> Singleton<T>::m_instance;

};

#endif
