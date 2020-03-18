#include <iostream>

struct A
{
    struct cfg
    {
        bool on = false;
    };
    
    cfg configuration[3];
};

struct B
{
    struct cfg
    {
        bool on = true;
    };
    
    cfg configuration[2][3];
};

template <class C, bool isMutli = false>
class Check 
{
protected:
    const C& m_c;

public:
    
    Check(const C& c_) : m_c(c_) {}

    bool is_on(int idx) {
        if constexpr ( isMutli )
        {
            return m_c.configuration[0][idx].on;
        }
        else
        {
            return m_c.configuration[idx].on;
        }
        
    }
};
 
int main()
{
    A a;
    B b;
    Check<A> c(a); // this works
    Check<B, true> c1(b); 

    if(c.is_on(0))
        std::cout << "its B!\n";
    else
        std::cout << "its A!\n";
    c1.is_on(1);
    
}
