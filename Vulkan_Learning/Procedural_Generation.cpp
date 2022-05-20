#include "Procedural_Generation.h"

//#include "Procedural_ObjectData_Operations.h"
//#include "Operations_3d.h"
#include "Order_Creator_3d.h";

namespace Proc
{
    //We create a quard by providing 4 points
    //We crate a circle made of quards
    //



    Procedural_Generation::Procedural_Generation()
    {
        //We call object 3d controller -> which calls something in Generative 3d collection ( example small_rnd_ring() )
        //Generate 3d collection -> is using one or multiple calls into Elements 3d to generate a scene (this is the class that's holds functions
        //representing art peaces ( think of it as gallery ) Chouls I rename it to ArtGallery or Gallery ? 
        
        //Gallery uses Elements to assemle it's art peaces
        //Elements uses operations to build it's staff
        
        

        //--
        // Procedural generation calls Order_Creator_3d
        // 
        //


        /*
        Procedural_ObjectData* pobj = new Procedural_ObjectData();

        //Proc::Opr::AddQuad(pobj);

        pobj->indices = { 0, 1, 2, 0, 3, 1, 4, 5, 6, 4, 7, 5, 8, 9, 10, 8, 11, 9,
            12, 13, 14, 12, 15, 13, 16, 17, 18, 16, 19, 17, 20, 21, 22, 20, 23, 21 };



        pobj->vertices = {
            // left face (white)
            {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
            {{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},

            // right face (yellow)
            {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .8f, .1f}},
            {{.5f, -.5f, .5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, -.5f}, {.8f, .8f, .1f}},

            // top face (orange, remember y axis points down)
            {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            {{-.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, -.5f}, {.9f, .6f, .1f}},

            // bottom face (red)
            {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .1f, .1f}},
            {{-.5f, .5f, .5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, -.5f}, {.8f, .1f, .1f}},

            // nose face (blue)
            {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
            {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
            {{-.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
            {{.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},

            // tail face (green)
            {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            {{-.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
        };
        
        Proc::Opr::vertices_randomize_positions(pobj, 0.5f);


        float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        */

        Cosmos::Data_Types::Object3d_Data* pobj = new Cosmos::Data_Types::Object3d_Data();
        
        Cosmos::Order_Creator_3d::Create(pobj);

        

       /*
        float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        pobj->position = glm::vec3(0.0f, 0.0f, 0.0f); //glm::vec3(x * 0.1, y * 0.1, 5.0f);//* 100 * 1.0f);
        
        


        //pobj.rotation = glm::vec3(0, 0, 0);

        pobj->scale = glm::vec3(1.0, 1.0, 1.0);
        */
        /*
        Proc::Opr::add_quad(pobj,
            glm::vec3(0, 0, 0), //v0
            glm::vec3(5, 0, 0), //v1
            glm::vec3(5, 5, 0), //v2
            glm::vec3(0, 5, 0), //v3
            glm::vec3(0.2, 0.5, 0.8)  //color
        );


        Proc::Opr::add_quad(pobj,
            glm::vec3(0, 0, 2), //v0
            glm::vec3(5, 0, 2), //v1
            glm::vec3(5, 5, 3), //v2
            glm::vec3(0, 5, 3), //v3
            glm::vec3(1, 1, 1)  //color
        );
        */

        /*
        Proc::Opr::add_circular(pobj,
            20,
            7.0f,
            6.0f,
            3.0f,
            glm::vec3(1, 1, 1),
            glm::vec3(0.5, 1, 0.5),
            glm::vec3(1.0, 1, 0.0),
            glm::vec3(0.0, 1, 0.2));
        */
        
        //Proc::Opr::AddRing(pobj);
        
        
       

        //Proc::Opr::vertices_randomize_positions(pobj, 0.05f);


        data.push_back(pobj);
        



    }

    Procedural_Generation::~Procedural_Generation()
    {

        for (int i = 0; i < data.size(); i++)
        {
            delete data[i];
        }

        data.clear();
    }

    /*
    void My_ProcedurallyGenerateNewObject()
    {
        std::shared_ptr<Lve_model> lveModel_2 = createCubeModel_rnd(lveDevice, glm::vec3{ 0.0f });
        auto proc_gm = LveGameObject::createGameObject();
        proc_gm.model = lveModel_2;
        float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        proc_gm.transform.translation = { x * 10, y * 10, z * 10 };
        proc_gm.transform.scale = { 0.08, 0.08, 0.08 };
        gameObjects.push_back(std::move(proc_gm));
    }
    */
}


/*
*
* Procedural_Generation::Procedural_Generation()
    {
        Procedural_ObjectData* pobj = new Procedural_ObjectData();

        pobj->indices = { 0, 1, 2, 0, 3, 1, 4, 5, 6, 4, 7, 5, 8, 9, 10, 8, 11, 9,
            12, 13, 14, 12, 15, 13, 16, 17, 18, 16, 19, 17, 20, 21, 22, 20, 23, 21 };

        pobj->vertices = {
            // left face (white)
            {{-.5f, -.5f, -.5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, .5f}, {.9f, .9f, .9f}},
            {{-.5f, -.5f, .5f}, {.9f, .9f, .9f}},
            {{-.5f, .5f, -.5f}, {.9f, .9f, .9f}},

            // right face (yellow)
            {{.5f, -.5f, -.5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .8f, .1f}},
            {{.5f, -.5f, .5f}, {.8f, .8f, .1f}},
            {{.5f, .5f, -.5f}, {.8f, .8f, .1f}},

            // top face (orange, remember y axis points down)
            {{-.5f, -.5f, -.5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            {{-.5f, -.5f, .5f}, {.9f, .6f, .1f}},
            {{.5f, -.5f, -.5f}, {.9f, .6f, .1f}},

            // bottom face (red)
            {{-.5f, .5f, -.5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, .5f}, {.8f, .1f, .1f}},
            {{-.5f, .5f, .5f}, {.8f, .1f, .1f}},
            {{.5f, .5f, -.5f}, {.8f, .1f, .1f}},

            // nose face (blue)
            {{-.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},
            {{.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
            {{-.5f, .5f, 0.5f}, {.1f, .1f, .8f}},
            {{.5f, -.5f, 0.5f}, {.1f, .1f, .8f}},

            // tail face (green)
            {{-.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            {{-.5f, .5f, -0.5f}, {.1f, .8f, .1f}},
            {{.5f, -.5f, -0.5f}, {.1f, .8f, .1f}},
        };


        for (auto& v : pobj->vertices) {

            float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
            v.position += glm::vec3{ x * 0.25f, y * 0.25f, z * 0.25f };
        }

        float x = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float y = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);
        float z = static_cast <float> (rand()) / static_cast <float> (RAND_MAX);

        pobj->position = glm::vec3(x * 5, y * 5, z * 5);

        //pobj.rotation = glm::vec3(0, 0, 0);

        pobj->scale = glm::vec3(0.25, 0.25, 0.25);

        data.push_back(pobj);




    }

*/