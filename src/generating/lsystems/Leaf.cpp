#include "Leaf.h"
#include "Family.h"

void Leaf::process(ProcessContext& pc)  {
    static Family gen;
    ModelPtr leaf = gen.get(5)->copy(); 
    leaf->apply(pc.current.getWorldMat() * Utils::getScaleMat(0.002f));
    pc.model->add(leaf);
}