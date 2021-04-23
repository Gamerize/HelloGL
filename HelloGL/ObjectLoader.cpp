#include "ObjectLoader.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

namespace ObjectLoader
{
    void LoadObject(ifstream& inFile, Obj &Obj);

    void LoadObject(ifstream& inFile, Obj& Obj)
    {
        Obj.faceCount = 0;
        string charCatch;
        while (!inFile.eof())
        {
            inFile >> charCatch;
            if (charCatch == "v")
            {
                Vertex tempVertex;
                inFile >> tempVertex.x;
                inFile >> tempVertex.y;
                inFile >> tempVertex.z;

                Obj.vertices.push_back(tempVertex);
            }

            if (charCatch == "vt")
            {
                TexCoord tempTex;
                inFile >> tempTex.u;
                inFile >> tempTex.v;

                Obj.TexCoord.push_back(tempTex);
            }

            if (charCatch == "vn")
            {
                Vector3 tempNor;
                inFile >> tempNor.x;
                inFile >> tempNor.y;
                inFile >> tempNor.z;

                Obj.Normals.push_back(tempNor);
            }

            if (charCatch == "f")
            {
                char slash;

                Obj.faceCount += 3;
                
                GLushort tempIndices;
                for (int i = 0; i < 3; i++)
                {
                    inFile >> tempIndices;
                    inFile >> slash;
                    Obj.VerIndices.push_back(tempIndices -1);
                    inFile >> tempIndices;
                    inFile >> slash;
                    Obj.TexIndices.push_back(tempIndices -1);
                    inFile >> tempIndices;
                    Obj.NorIndices.push_back(tempIndices -1);
                }
            }
        }
    }

    Obj* ObjectLoader::Load(char* path)
    {
        Obj* obj = new Obj();

        ifstream inFile;

        inFile.open(path);

        if (!inFile.good())
        {
            cerr << "Can't open texture file " << path << endl;
            return nullptr;
        }

        LoadObject(inFile, *obj);

        inFile.close();

        return obj;
    }
}


