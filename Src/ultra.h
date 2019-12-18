// ultra.h

#ifndef ULTRA_H
#define ULTRA_H

class Ultra
{
private:
    int lDistance;
    int rDistance;
public:
    Ultra();
    void mesureDistance();
    inline int getLDistance() {return lDistance;};
    inline int getRDistance() {return rDistance;};
};

#endif
