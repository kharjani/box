//
//  Line.hpp
//  paint-mac
//
//  Created by Krish on 2/22/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef Line_hpp
#define Line_hpp

#include <stdio.h>
#include "Shape.h"


class Line: public Shape
{
public:
    Line(const wxPoint& start);
    ~Line();
    
    virtual void Draw(wxDC& dc) const override;
    virtual void Finalize();
};
#endif /* Line_hpp */
