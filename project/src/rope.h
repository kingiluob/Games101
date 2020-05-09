#ifndef ROPE_H
#define ROPE_H

#include "CGL/CGL.h"
#include "mass.h"
#include "spring.h"

using namespace std;

namespace CGL {

class Rope {
public:
  Rope(vector<Mass *> &masses, vector<Spring *> &springs)
      : masses(masses), springs(springs) {}
  Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass, float k,
       vector<int> pinned_nodes);

  void simulateVerlet(float delta_t, Vector2D gravity);
  void simulateEuler(float delta_t, Vector2D gravity);

  vector<Mass *> masses;
  vector<Spring *> springs;
}; // struct Rope
class Cloth
{
  public:
  Cloth(vector<Mass *> &masses, vector<Spring *> &springs)
      : masses(masses), springs(springs) {}
  Cloth(Vector3D leftTop,Vector3D rightTop,Vector3D leftBot,Vector3D rightBot,int rows,int column,
      float nodemass,float k,vector<int> pinndenodes);

  void simulateEuler(float delta_t,Vector3D gravity);
  void simulateVerlet(float delta_t,Vector3D gravity);

  vector<Mass *> masses;
  vector<Spring *> springs;
};//struct cloth

}
#endif /* ROPE_H */
