#include "Leaf.h"
#include "Family.h"
#include "Assets.h"
#include "Random.h"

void Leaf::process(ProcessContext& pc)  {
    if(Assets::LEAF_GENERATORS.size() == 0) {
        return;
    }
    
    ModelPtr leaf = Random::randomElement(Assets::LEAF_GENERATORS)->get()->copy(); 
    leaf->apply(pc.current.getWorldMat());
    pc.model->add(leaf);
}