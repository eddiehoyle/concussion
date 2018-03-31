#ifndef CONCUSSION_PLAYER_HH
#define CONCUSSION_PLAYER_HH

#include <CBase/platform.hh>
#include <CBase/entity/entity.hh>

namespace concussion {

class Player : Entity< Player >{
public:
    Player( const std::string& name ) : m_name( name ) {}
    std::string name() const { return m_name; }
private:
    std::string m_name;
};

}

#endif //CONCUSSION_PLAYER_HH
