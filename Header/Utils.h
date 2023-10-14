

template<typename T>
void Swap(T& InrValueA, T& InrValueB)
{
    T rTemp = InrValueA;

    InrValueA = InrValueB;
    InrValueB = rTemp;
};