#pragma once
#include "../core/Macro.hpp"

#include <iostream>

#define DEBUG
//#undef DEBUG

template <typename OutputStreamT>
class API LoggerBase
{
public:
    LoggerBase(OutputStreamT& OutputStream) : m_OutputStream(OutputStream) {}

    template<typename ... Args>
    void Info(Args&& ... args)
    {
        LogBase("Info", std::forward<Args>(args)...);
    }
    
    template<typename ... Args>
    void Warn(Args&& ... args)
    {
        LogBase("Warn", std::forward<Args>(args)...);
    }

    template<typename ... Args>
    void Error(Args&& ... args)
    {
        LogBase("Error", std::forward<Args>(args)...);
    }

private:
    template<typename Category, typename ... Args>
    void LogBase(const Category& category, Args&& ... args)
    {
        #ifdef DEBUG
            m_OutputStream << category << ": ";
            ((m_OutputStream << std::forward<Args>(args)), ...) << "\n";
        #endif
    }

private:
    OutputStreamT& m_OutputStream;
};

inline static LoggerBase<std::ostream> Log(std::cout);