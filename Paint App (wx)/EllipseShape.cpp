//
//  EllipseShape.cpp
//  paint-mac
//
//  Created by Krish on 2/22/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "EllipseShape.hpp"


EllipseShape::EllipseShape(const wxPoint& start):Shape(start)
{
   
    
}

EllipseShape::~EllipseShape()
{
    // destructor
}

void EllipseShape::Draw(wxDC &dc ) const
{
    dc.SetPen(mPen);
    dc.SetBrush(mBrush);
    dc.DrawEllipse(wxRect(mOffset + mTopLeft, mOffset + mBotRight));
}


void EllipseShape::Finalize()
{
    //
}

