//
//  SetBrushCommand.cpp
//  paint-mac
//
//  Created by Krish on 2/23/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "SetBrushCommand.hpp"


SetBrushCommand::SetBrushCommand(const wxPoint& start, std::shared_ptr<Shape> shape):Command(start, shape){
    
}

SetBrushCommand::~SetBrushCommand()
{
    
}


void SetBrushCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    
    mNewBrush = model->getBrush();
    
    mShape->Finalize();
    
}

void SetBrushCommand::Undo(std::shared_ptr<PaintModel> model)
{
    mShape->setBrush(mOldBrush);
}

void SetBrushCommand::Redo(std::shared_ptr<PaintModel> model)
{
    mShape->setBrush(mNewBrush);
}



void SetBrushCommand::Update(const wxPoint& newPoint)
{
    Command::Update(newPoint);
    mShape->Update(newPoint);
    
}

void SetBrushCommand::setNewBrush(wxBrush brush)
{
    mNewBrush = brush;
}



