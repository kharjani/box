//
//  Line.cpp
//  paint-mac
//
//  Created by Krish on 2/22/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "Line.hpp"

Line::Line(const wxPoint& start):Shape(start)
{
    
}

Line::~Line()
{
    
}

void Line::Draw(wxDC &dc) const
{
    dc.SetPen(mPen);
    dc.SetBrush(mBrush);
    dc.DrawLine(mOffset + mStartPoint, mOffset + mEndPoint);
}

void Line::Finalize()
{
    
}
