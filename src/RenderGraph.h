//
// Created by theo on 14/08/23.
//

#ifndef GL_PBR_TRAINING_RENDERGRAPH_H
#define GL_PBR_TRAINING_RENDERGRAPH_H

#include <vector>

class Pass {
protected:

public:
    virtual void init(int width, int height) = 0;

    const char* m_name{};

    virtual void execute() = 0;
};

class RenderGraph {
private:
    std::vector<Pass *> m_passes;

public:
    void addPass(Pass *pass);
    void execute();
};


#endif //GL_PBR_TRAINING_RENDERGRAPH_H
