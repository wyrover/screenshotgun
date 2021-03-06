#ifndef SCREENSHOTGUN_LINEMODE_H
#define SCREENSHOTGUN_LINEMODE_H

#include "AbstractMode.h"
#include "items/LineItem.h"

class LineMode : public AbstractMode {

public:
    LineMode(Overlay&);

    void init(int x, int y);
    void move(int x, int y);
    void stop(int x, int y);

protected:
    LineItem* line_;
};

#endif // SCREENSHOTGUN_LINEMODE_H
