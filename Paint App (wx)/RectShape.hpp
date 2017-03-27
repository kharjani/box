//
//  RectShape.hpp
//  paint-mac
//
//  Created by Krish on 2/21/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef RectShape_hpp
#define RectShape_hpp

#include <stdio.h>

#include "Shape.h"
#include <wx/gdicmn.h>

class RectShape: public Shape
{
public:
    RectShape(const wxPoint& start);
    
    ~RectShape();
    
    virtual void Draw(wxDC& dc) const override;
    virtual void Finalize();
    
    
};


#endif /* RectShape_hpp */
