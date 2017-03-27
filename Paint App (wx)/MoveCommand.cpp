//
//  MoveCommand.cpp
//  paint-mac
//
//  Created by Krish on 2/23/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "MoveCommand.hpp"



MoveCommand::MoveCommand(const wxPoint& start, std::shared_ptr<Shape> shape)
:Command(start, shape)
{
    
    old = shape->getOffset();
    
}


MoveCommand::~MoveCommand()
{
    
}

void MoveCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    mShape->setOffset(mOffset);
    mShape->Finalize();
    
}

void MoveCommand::Undo(std::shared_ptr<PaintModel> model)
{
    
    mShape->setOffset(old);
    
    mShape->Finalize();
    
    
}

void MoveCommand::Redo(std::shared_ptr<PaintModel> model)
{
    // check stack?
    mShape->setOffset(mOffset);
}

void MoveCommand::Update(const wxPoint& newPoint)
{
    
    mOffset =  (newPoint + old) - mStartPoint;
    
    mShape->setOffset(mOffset);
    
}




