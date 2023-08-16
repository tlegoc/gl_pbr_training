//
// Created by theo on 14/08/23.
//

#include "RenderGraph.h"

void RenderGraph::execute() {
    for (auto pass : m_passes) {
        pass->execute();
    }
}

void RenderGraph::addPass(Pass *pass) {
    m_passes.push_back(pass);
}