//
//  EllipseShape.hpp
//  paint-mac
//
//  Created by Krish on 2/22/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef EllipseShape_hpp
#define EllipseShape_hpp

#include <stdio.h>
#include "Shape.h"

class EllipseShape : public Shape
{
public:
    EllipseShape(const wxPoint& start);
    
    ~EllipseShape();
    
    virtual void Draw(wxDC& dc) const override;
    virtual void Finalize();
};

#endif /* EllipseShape_hpp */
