#include "Leaf.h"
#include "Family.h"
#include "Assets.h"

void Leaf::process(ProcessContext& pc)  {
    ModelPtr leaf = Assets::LEAF_GENERATORS[0]->get()->copy(); 
    leaf->apply(pc.current.getWorldMat());
    pc.model->add(leaf);
}