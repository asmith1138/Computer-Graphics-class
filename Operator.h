class MyClass{
    public:
    int number;
    bool operator<(MyClass const& m) const;
    bool operator<(int i) const;
};
bool operator<(int i, MyClass const& m);