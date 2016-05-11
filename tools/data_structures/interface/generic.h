#ifndef __GENERIC_H
#define __GENERIC_H


#include <CommProtocol/architecture/os/include_defines.h>

namespace Comnet {
namespace DataStructure {
namespace Package {

/**
 Handles the data structure type.
*/
enum DataStructureType {
  NONE,
  LIST,
  QUEUE,
  HEAP,
  TREE,
};
    
/**
  Interface default for Information on the data structure at hand.
*/
class Interface {
public:
  
private:
  // size of data structure
  // enum of data structure
}

} // Package
} // DataStructure
} // Comnet

#endif // __GENERIC_H