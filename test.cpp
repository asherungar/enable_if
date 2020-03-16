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


template <class C>
class CheckBase
{
protected:
    C& m_c;

public:
    CheckBase(C& _c) :m_c(_c) {}
};

template<class C>
class Check;

template<>
class Check<A> : public CheckBase<A>
{
public:
    using CheckBase::CheckBase;

    bool is_on(int idx)
    {
        return m_c.configuration[idx].on;
    }
};

template<>
class Check<B> : public CheckBase<B>
{
public:
    using CheckBase::CheckBase;

    int m_secondIndex = 1; /// i want this member *only* if the class is B

    bool is_on(int idx)
    {
        return m_c.configuration[m_secondIndex][idx].on;
    }
};

// deduction guides
template<class C>
Check(C& c) -> Check<C>;
 
int main()
{
    A a;
    B b;
    Check c(a);
    (void)a;
    (void)b;
    if(c.is_on(0))
        std::cout << "its B!\n";
    else
        std::cout << "its A!\n";
}
