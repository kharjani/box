//
//  MoveCommand.hpp
//  paint-mac
//
//  Created by Krish on 2/23/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef MoveCommand_hpp
#define MoveCommand_hpp

#include <stdio.h>
#include "Command.h"

class MoveCommand : public Command
{
public:
    MoveCommand(const wxPoint& start, std::shared_ptr<Shape> shape);
    
    ~MoveCommand();
    
    virtual void Finalize(std::shared_ptr<PaintModel> model) override;
    
    virtual void Undo(std::shared_ptr<PaintModel> model) override;
    
    virtual void Redo(std::shared_ptr<PaintModel> model) override;
    
    virtual void Update(const wxPoint& newPoint) override;
    
private:
    wxPoint mOffset;
    
    wxPoint old; // incase of undo, we need to remember where it was
    
    
};


#endif /* MoveCommand_hpp */
