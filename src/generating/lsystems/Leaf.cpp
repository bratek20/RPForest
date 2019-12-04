#include "Leaf.h"
#include "Family.h"

void Leaf::process(ProcessContext& pc)  {
    static Family gen;
    ModelPtr leaf = gen.getRandom()->copy(); 
    leaf->apply(pc.current.getWorldMat());
    pc.model->add(leaf);
}