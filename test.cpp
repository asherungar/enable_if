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


template<class C>
class CheckBase
{
public:
    bool is_on(C& c, int idx)
    {
        return c.configuration[idx].on;
    }
};

template<>
class CheckBase<B>
{
protected:
    int m_secondIndex =  -1; /// i want this member *only* if the class is B

public:
    CheckBase(int index) : m_secondIndex(index) {}    

    bool is_on(B& c, int idx)
    {
        return c.configuration[m_secondIndex][idx].on;
    }
};


template <class C, class... Args>
class Check : private CheckBase<C>
{
protected:
    C& m_c;

public:
    
    Check(C& _c, Args... args) : CheckBase<C>(args...), m_c(_c) { }

    bool is_on(int idx) {
        return CheckBase<C>::is_on(m_c, idx);
    }
};
 
int main()
{
    A a;
    B b;
    Check<A> c(a); // this works
    Check<B> c1(b, 1); // doesnt compile
    Check<B> c2(b, 2); // doesnt compile

    if(c.is_on(0))
        std::cout << "its B!\n";
    else
        std::cout << "its A!\n";
}
