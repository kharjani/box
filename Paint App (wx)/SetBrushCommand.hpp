//
//  SetBrushCommand.hpp
//  paint-mac
//
//  Created by Krish on 2/23/17.
//  Copyright © 2017 Sanjay Madhav. All rights reserved.
//

#ifndef SetBrushCommand_hpp
#define SetBrushCommand_hpp

#include <stdio.h>
#include "Command.h"
#include "Shape.h"
#include "PaintModel.h"

class SetBrushCommand : public Command
{
public:
    SetBrushCommand(const wxPoint& start, std::shared_ptr<Shape> shape);
    
    ~SetBrushCommand();
    
    virtual void Finalize(std::shared_ptr<PaintModel> model) override;
    
    virtual void Undo(std::shared_ptr<PaintModel> model) override;
    
    virtual void Redo(std::shared_ptr<PaintModel> model) override;
    
    virtual void Update(const wxPoint& newPoint) override;
    
    void setNewBrush(wxBrush brush);
    
private:
    
    wxBrush mOldBrush;
    wxBrush mNewBrush;
};


#endif /* SetBrushCommand_hpp */

