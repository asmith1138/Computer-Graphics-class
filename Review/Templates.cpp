template <class T>
T max(T const& t1, T const& t2)
{
    return t1 < t2 ? t2 : t1;
}


template<class T>
class Accum
{
    private:
        T total;
    public:
        Accum(T start): total(start){};
        T operator+=(T const& t)
            {return total = total + t;};
        T GetTotal() const {return total;}
};