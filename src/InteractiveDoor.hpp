#ifndef INTERACTIVEDOOR_H
#define INTERACTIVEDOOR_H
#include "InteractiveObject.hpp"

class InteractiveDoor : public InteractiveObject {
    public:
        InteractiveDoor(Game&);

        virtual void action() override;
};

#endif // INTERACTIVEDOOR_H
