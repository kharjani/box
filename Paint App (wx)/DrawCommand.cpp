//
//  DrawCommand.cpp
//  paint-mac
//
//  Created by Krish on 2/20/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#include "DrawCommand.hpp"





DrawCommand::DrawCommand(const wxPoint& start, std::shared_ptr<Shape> shape):Command(start, shape)
{

    
}

DrawCommand::~DrawCommand()
{
    
}

void DrawCommand::Finalize(std::shared_ptr<PaintModel> model)
{
    
    mShape->Finalize();
    
}

void DrawCommand::Update(const wxPoint &newPoint)
{
    Command::Update(newPoint);
    
    mShape->Update(newPoint);
}

void DrawCommand::Undo(std::shared_ptr<PaintModel> model)
{
    model->RemoveShape(mShape);
}

void DrawCommand::Redo(std::shared_ptr<PaintModel> model )
{
    model->AddShape(mShape);
}

