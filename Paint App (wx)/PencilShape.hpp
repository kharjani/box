//
//  PencilShape.hpp
//  paint-mac
//
//  Created by Krish on 2/22/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef PencilShape_hpp
#define PencilShape_hpp

#include <stdio.h>
#include "Shape.h"
#include <vector>

class PencilShape : public Shape
{
public:
    PencilShape(const wxPoint& start);
    
    ~PencilShape();
    
    void Draw(wxDC& dc) const override;
    
    virtual void Update(const wxPoint& newPoint) override;

    virtual void Finalize() override;
    
private:

    std::vector<wxPoint> mPoints;
    
    
};

#endif /* PencilShape_hpp */
