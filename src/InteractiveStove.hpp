#ifndef INTERACTIVESTOVE_H
#define INTERACTIVESTOVE_H
#include "InteractiveObject.hpp"

class InteractiveStove : public InteractiveObject {
    public:
        InteractiveStove(Game&);

        virtual ObjectType getType() const noexcept override;
        virtual void action() override;
        virtual void reset() override;
};

#endif // INTERACTIVESTOVE_H
