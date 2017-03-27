//
//  SetPenCommand.cpp
//  paint-mac
//
//  Created by Krish on 2/23/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "SetPenCommand.hpp"


SetPenCommand::SetPenCommand(const wxPoint& start, std::shared_ptr<Shape> shape)
:Command(start, shape)
{
    mOldPen = shape->getPen();
    mOldColor = mOldPen.GetColour();
    //mOldPen.SetColour(mOldPen.GetColour());
}


SetPenCommand::~SetPenCommand()
{
    //
}


void SetPenCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    mNewPen = model->getPen();
    mNewColor = mNewPen.GetColour();
    mShape->Finalize();
    
}

void SetPenCommand::Undo(std::shared_ptr<PaintModel> model)
{
    mShape->setPen(mOldPen);
    mShape->setPenColor(mOldColor);
    
    
}
void SetPenCommand::Redo(std::shared_ptr<PaintModel> model)
{
    
    mShape->setPen(mNewPen);
    mShape->setPenColor(mNewColor);
}



void SetPenCommand::Update(const wxPoint& newPoint)
{
    Command::Update(newPoint);
    mShape->Update(newPoint);
    
}


