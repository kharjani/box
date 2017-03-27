//
//  DNADrawPanel.cpp
//  DNAwx
//
//  Created by Sanjay Madhav on 12/27/14.
//  Copyright (c) 2014 Sanjay Madhav. All rights reserved.
//

#include "DNADrawPanel.h"
#include <wx/dcclient.h>
#include <wx/sizer.h>
#include <array>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <iostream>


BEGIN_EVENT_TABLE(DNADrawPanel, wxPanel)
	EVT_PAINT(DNADrawPanel::PaintEvent)
END_EVENT_TABLE()

DNADrawPanel::DNADrawPanel(wxFrame* parent)
: wxPanel(parent)
{
	
}

void DNADrawPanel::PaintEvent(wxPaintEvent & evt)
{
	wxPaintDC dc(this);
	Render(dc);
}

void DNADrawPanel::PaintNow()
{
	wxClientDC dc(this);
	Render(dc);
}

void DNADrawPanel::Render(wxDC& dc)
{
	// Clear
	dc.SetBackground(*wxWHITE_BRUSH);
	dc.Clear();
    
    if(!hasFile)return;
	dc.DrawText(mHeader, 50, 40);
    
	// TODO: Draw histogram, if one has been generated
    int length = 45;
    std::string strPct;
    float percentage;
    float count;
    std::string label;
    
    
    // Alanine ('A')
    dc.SetTextForeground(*wxRED);
    count = mAminoMap['A'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxRED_BRUSH);
    dc.DrawRectangle(200, 70, length* percentage, 30);
    strPct = std::to_string(percentage);
    auto round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Alanine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 80);
    
    
    // Cysteine ('C')
    dc.SetTextForeground(*wxGREEN);
    count = mAminoMap['C'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxGREEN_BRUSH);
    dc.DrawRectangle(200, 100, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Cysteine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 110);
    
    
    // Aspartic acid ('D')
    dc.SetTextForeground(*wxBLUE);
    count = mAminoMap['D'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.DrawRectangle(200, 130, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Aspartic acid: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 140);
    
    
    // Glutamic acid ('E')
    dc.SetTextForeground(*wxRED);
    count = mAminoMap['E'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxRED_BRUSH);
    dc.DrawRectangle(200, 160, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Glutamic acid: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 170);
    
    
    // Phenylalanine ('F')
    dc.SetTextForeground(*wxGREEN);
    count = mAminoMap['F'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxGREEN_BRUSH);
    dc.DrawRectangle(200, 190, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Phenylalanine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 200);
    
    
    // Glycine ('G')
    dc.SetTextForeground(*wxBLUE);
    count = mAminoMap['G'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.DrawRectangle(200, 220, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Glycine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 230);
    
    
    // Histidine ('H')
    dc.SetTextForeground(*wxRED);
    count = mAminoMap['H'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxRED_BRUSH);
    dc.DrawRectangle(200, 250, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Histidine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 260);
    
    
    // Isoleucine ('I')
    dc.SetTextForeground(*wxGREEN);
    count = mAminoMap['I'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxGREEN_BRUSH);
    dc.DrawRectangle(200, 280, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Isoleucine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 290);
    
    
    // Lysine ('K')
    dc.SetTextForeground(*wxBLUE);
    count = mAminoMap['K'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.DrawRectangle(200, 310, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Lysine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 320);
    
    
    // Leucine ('L')
    dc.SetTextForeground(*wxRED);
    count = mAminoMap['L'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxRED_BRUSH);
    dc.DrawRectangle(200, 340, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Leucine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 350);
    
    
    // Methionine ('M')
    dc.SetTextForeground(*wxGREEN);
    count = mAminoMap['M'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxGREEN_BRUSH);
    dc.DrawRectangle(200, 370, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Methionine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 380);
    
    
    // Asparagine ('N')
    dc.SetTextForeground(*wxBLUE);
    count = mAminoMap['N'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.DrawRectangle(200, 400, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Asparagine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 410);
    
    
    // Proline ('P')
    dc.SetTextForeground(*wxRED);
    count = mAminoMap['P'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxRED_BRUSH);
    dc.DrawRectangle(200, 430, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Proline: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 440);
    
    
    // Glutamine ('Q')
    dc.SetTextForeground(*wxGREEN);
    count = mAminoMap['Q'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxGREEN_BRUSH);
    dc.DrawRectangle(200, 460, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Glutamine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 470);
    
    
    // Arginine ('R')
    dc.SetTextForeground(*wxBLUE);
    count = mAminoMap['R'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.DrawRectangle(200, 490, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Arginine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 500);
    
    
    // Serine ('S')
    dc.SetTextForeground(*wxRED);
    count = mAminoMap['S'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxRED_BRUSH);
    dc.DrawRectangle(200, 520, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Serine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 530);
    
    
    // Threonine ('T')
    dc.SetTextForeground(*wxGREEN);
    count = mAminoMap['T'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxGREEN_BRUSH);
    dc.DrawRectangle(200, 550, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Threonine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 560);
    
    
    // Valine ('V')
    dc.SetTextForeground(*wxBLUE);
    count = mAminoMap['V'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxBLUE_BRUSH);
    dc.DrawRectangle(200, 580, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Valine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 590);
    
    // Tryptophan ('W')
    dc.SetTextForeground(*wxRED);
    count = mAminoMap['W'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxRED_BRUSH);
    dc.DrawRectangle(200, 610, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Tryptophan: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 620);
    
    
    // Tyrosine ('Y')
    dc.SetTextForeground(*wxGREEN);
    count = mAminoMap['Y'];
    percentage = (float) ((count / mTotalCount) * 100 );
    dc.SetBrush(*wxGREEN_BRUSH);
    dc.DrawRectangle(200, 640, length* percentage, 30);
    strPct = std::to_string(percentage);
    round = strPct.find(".");
    strPct = strPct.substr(0, round+3); // messy but works lol
    label = "Tyrosine: " +  strPct + "% " + "(" + std::to_string((int)count) + ")";
    
    dc.DrawText(label , 30, 650);
    
    
    

    
    
   
}


