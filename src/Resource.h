//
// Created by theo on 15/08/23.
//

#ifndef GL_PBR_TRAINING_RESOURCE_H
#define GL_PBR_TRAINING_RESOURCE_H


class Resource {
public:
    virtual void load() = 0;

private:
    void * const m_resource_ptr;
};


#endif //GL_PBR_TRAINING_RESOURCE_H
