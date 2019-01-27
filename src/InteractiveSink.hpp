#ifndef INTERACTIVESINK_H
#define INTERACTIVESINK_H
#include "InteractiveObject.hpp"

class InteractiveSink : public InteractiveObject {
    public:
        InteractiveSink(Game&);

        virtual ObjectType getType() const noexcept override;
        virtual void action() override;
        virtual void reset() override;
};

#endif // INTERACTIVESINK_H
