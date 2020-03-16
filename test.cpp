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
class Check
{

private:
    C& m_c;

    int m_secondIndex = 1; /// i want this member *only* if the class is B

public:
    Check(C& _c) :m_c(_c) {}
    
    bool is_on(int idx);
};

// i want this for the case the class is A
template<class T>
typename std::enable_if<!std::is_array_v<decltype(std::declval<T>().configuration[0])>>
bool Check<T>::is_on(int idx)
{
    return m_c.configuration[idx].on;
}

// i want this for the case the class is B (using the member m_secondIndex)
template<class T>
typename std::enable_if<std::is_array_v<decltype(std::declval<T>().configuration[0])>>
bool Check<T>::is_on(int idx)
{
    return m_c.configuration[m_secondIndex][idx].on;
}
 
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