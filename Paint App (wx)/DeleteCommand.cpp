//
//  DeleteCommand.cpp
//  paint-mac
//
//  Created by Krish on 2/23/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "DeleteCommand.hpp"

DeleteCommand::DeleteCommand(const wxPoint& start, std::shared_ptr<Shape> shape)
:Command(start, shape)
{
    
}


DeleteCommand::~DeleteCommand()
{
    
}



void DeleteCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    
}

void DeleteCommand::Undo(std::shared_ptr<PaintModel> model)
{
    // just add it back to the top who cares
    model->AddShape(mShape);
}

void DeleteCommand::Redo(std::shared_ptr<PaintModel> model)
{
    
    model->RemoveShape(mShape);
}

void DeleteCommand::Update(const wxPoint& newPoint)
{
    //
}
