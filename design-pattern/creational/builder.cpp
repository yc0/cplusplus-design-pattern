//
//  builder.cpp
//  design-pattern
//
//  Created by nelson lin on 8/20/18.
//  Copyright © 2018 nelson lin. All rights reserved.
//

#include "builder.hpp"
enum PersistentType {
  File, Queue, Pathway
};

struct PersistentAttribute {
    PersistentType type;
    char value[30];
};

class DistributedWorkPackage {
public:
    void fuck() {
        std::cout << "FUCK YOU" << std::endl;
    }
private:
};

TEST(Creational,Builder) {
    DistributedWorkPackage dwp;
    dwp.fuck();
};
