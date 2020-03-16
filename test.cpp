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
class CheckBase;

template<>
class CheckBase<A>
{
public:
    bool is_on(A& c, int idx)
    {
        return c.configuration[idx].on;
    }
};

template<>
class CheckBase<B>
{
public:
    int m_secondIndex = 1; /// i want this member *only* if the class is B

    bool is_on(B& c, int idx)
    {
        return c.configuration[m_secondIndex][idx].on;
    }
};


template <class C>
class Check : private CheckBase<C>
{
protected:
    C& m_c;

public:
    Check(C& _c) :m_c(_c) {}

    bool is_on(int idx) {
        return CheckBase<C>::is_on(m_c, idx);
    }
};
 
int main()
{
    A a;
    B b;
    Check c(b);
    (void)a;
    (void)b;
    if(c.is_on(0))
        std::cout << "its B!\n";
    else
        std::cout << "its A!\n";
}
