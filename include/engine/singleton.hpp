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
    const std::shared_ptr<T>& getInstance() const
    {
        return m_instance;
    }

    void setInstance(const std::shared_ptr<T>& instance)
    {
        m_instance = instance;
    }

private:
    static std::shared_ptr<T> m_instance;

};

};

#endif
