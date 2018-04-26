

#ifndef LOGGER_FORMAT_H
#define LOGGER_FORMAT_H

#include <sstream>
#include <string>

namespace devlib
{

class format
{
public:
    	
    template <class... Ts>
    format(const Ts&... ts) {
        assemble(ts...);
    }

    // Get string.
    std::string str() const{
        return ss_.str();
    }

private:

    // Base case for assembly.
    template <class T> 
    void assemble(const T& head){
        ss_ << head;
    }


    // Assembler.
    template <class T, class... Ts> 
    void assemble(const T& t, const Ts&... ts)
    {
        ss_ << t << ' ';
        assemble(ts...);
    }
     
    // The stringstream used to assemble the string.   
    std::stringstream ss_;
};
}

#endif
