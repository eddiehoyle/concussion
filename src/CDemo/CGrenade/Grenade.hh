//
// Created by Eddie Hoyle on 1/04/18.
//

#ifndef CONCUSSION_GRENADE_HH
#define CONCUSSION_GRENADE_HH

#include <CEngine/GameObject.hh>

namespace concussion {

class Grenade : public GameObject<Grenade> {

public:

    Grenade();
    virtual ~Grenade();

private:

    TransformComponent*		m_transform;

};

}


#endif //CONCUSSION_GRENADE_HH
