#include <iostream>
#include <vector>

#include "CGL/vector2D.h"

#include "mass.h"
#include "rope.h"
#include "spring.h"

namespace CGL {

    Rope::Rope(Vector2D start, Vector2D end, int num_nodes, float node_mass, float k, vector<int> pinned_nodes)
    {
        // TODO (Part 1): Create a rope starting at `start`, ending at `end`, and containing `num_nodes` nodes.
        if(num_nodes == 0 || num_nodes == 1)
            return;
        vector2D CurrentPosition = start;
        //treat rope as a list
        Mass * p = new Mass(start,node_mass,false);
        masses.pushback(p);
        Mass * n = nullptr;
        Spring * presentSpring = nullptr;
        for(int i = 1;i < num_nodes - 1;i++)
        {
            if(i == (num_nodes -2))
            {
                CurrentPosition = end;
            }
            else
            {
                CurrentPosition = start + i * (end-start) / (num_nodes - 1);
            }
            n = new Mass(CurrentPosition,node_mass,false);
            p = n;
            presentSpring = new Spring(p,n,k);
            masses.pushback(n);
            springs.pushback(presentSpring);
        }
//        Comment-in this part when you implement the constructor
        for (auto &i : pinned_nodes) {
            masses[i]->pinned = true;
        }
    }

    void Rope::simulateEuler(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 2): Use Hooke's law to calculate the force on a node
            vector2D ab = s->m1->position - s->m2->position;
            vector2D f = - s->k * (ab / ab.norm()) * (ab - s->rest_length);
            s->m1->forces += f;
            s->m2->forces -= f;
            //damping force
            float fd = 0;
            vector2D v_ba = s->m2->velocity - s->m1->velocity;
            vector fd = - fd * dot(ab / ab.norm(),v_ba) * (ab/ab.norm());
            s->m1->forces += fd;
            s->m2->forces -= fd;
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                // TODO (Part 2): Add the force due to gravity, then compute the new velocity and position
                m->forces += gravity * m->mass;
                a = m->forces / m->mass;
                // TODO (Part 2): Add global damping
                if(true)
                {
                    float k_d_global = 0.01;
                    m->forces += - k_d_global * m->velocity;
                }
                
                if(true)
                {
                    //Explicit method
                    m->position += m->velocity * delta_t;
                    m->velocity += a * delta_t;
                }
                else
                {
                    //semi-implicit method
                    m->velocity += a * delta_t;
                    m->position += m->velocity * delta_t;
                }   
            }
            // Reset all forces on each mass
            m->forces = Vector2D(0, 0);
        }
    }

    void Rope::simulateVerlet(float delta_t, Vector2D gravity)
    {
        for (auto &s : springs)
        {
            // TODO (Part 3): Simulate one timestep of the rope using explicit Verlet （solving constraints)
            vector2D ab = s->m1->position - s->m2->position;
            vector2D f = - s->k * (ab / ab.norm()) * (ab - s->rest_length);
            s->m1->forces += f;
            s->m2->forces -= f;
        }

        for (auto &m : masses)
        {
            if (!m->pinned)
            {
                m->forces += gravity * m->mass;
                Vector2D a = m->forces / m->mass;
                // TODO (Part 3.1): Set the new position of the rope mass
                Vector2D temp_position = m->position;
                // TODO (Part 4): Add global Verlet damping
                float dampfactor = 0.00005;
                m->position = temp_position +  (1 - dampfactor) * (temp_position - m->last_position) + a * delta_t *delta_t;
                m->last_position = m->position;
            }
        }
    }
}
