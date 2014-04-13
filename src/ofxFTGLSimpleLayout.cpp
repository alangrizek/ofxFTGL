#include "ofxFTGLSimpleLayout.h"

ofxFTGLSimpleLayout::ofxFTGLSimpleLayout()
: ofxFTGLFont()
{
    layout = NULL;
}

ofxFTGLSimpleLayout::~ofxFTGLSimpleLayout()
{
//	unload();
}

void ofxFTGLSimpleLayout::unload()
{
    ofxFTGLFont::unload();
    
    if (layout != NULL) {
        delete layout;
        layout = NULL;
    }
}

bool ofxFTGLSimpleLayout::loadFont(string filename, float fontsize, float depth, bool bUsePolygons)
{
    if (ofxFTGLFont::loadFont(filename, fontsize, depth, bUsePolygons)) {
        layout = new FTSimpleLayout();
        layout->SetFont(font);
    
        return true;
    }
    
    return false;
}

float ofxFTGLSimpleLayout::getLineLength() const
{
	return layout->GetLineLength();
}

void ofxFTGLSimpleLayout::setLineLength(float length)
{
    layout->SetLineLength(length);
}

float ofxFTGLSimpleLayout::getLineSpacing() const
{
	return layout->GetLineSpacing();
}

void ofxFTGLSimpleLayout::setLineSpacing(float spacing)
{
    layout->SetLineSpacing(spacing);
}

ofxFTGLTextAlignment ofxFTGLSimpleLayout::getAlignment() const
{
    return layout->GetAlignment();
}

void ofxFTGLSimpleLayout::setAlignment(ofxFTGLTextAlignment alignment)
{
    layout->SetAlignment(alignment);
}

ofRectangle ofxFTGLSimpleLayout::getStringBoundingBox(string s, float x, float y)
{
    if (loaded) {
    	FTBBox bbox = layout->BBox(s.c_str());
	    //return ofRectangle(x + bbox.Lower().Xf(), y + bbox.Lower().Yf(), bbox.Upper().Xf(), bbox.Upper().Yf());
        return ofRectangle(x, y-getAscender(), abs(bbox.Lower().Xf()-bbox.Upper().Xf()), abs(bbox.Upper().Yf()-bbox.Lower().Yf()));
    }
	return ofRectangle();
}

ofRectangle ofxFTGLSimpleLayout::getStringBoundingBox(wstring s, float x, float y)
{
    if (loaded) {
    	FTBBox bbox = layout->BBox((wchar_t*)s.c_str());
	    return ofRectangle(x, y-getAscender(), abs(bbox.Lower().Xf()-bbox.Upper().Xf()), abs(bbox.Upper().Yf()-bbox.Lower().Yf()));
    }
	return ofRectangle();
}

void ofxFTGLSimpleLayout::drawString(string s, float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(1,-1,1);
    layout->Render(s.c_str());
    glPopMatrix();
}

void ofxFTGLSimpleLayout::drawString(wstring s, float x, float y)
{
    glPushMatrix();
    glTranslatef(x, y, 0);
    glScalef(1,-1,1);
    layout->Render((wchar_t*)s.c_str());
    glPopMatrix();
}

float ofxFTGLSimpleLayout::GetTextToPixelsHeight(string text, string font, int size, float width, float margin, float spacing){
    
    ofxFTGLSimpleLayout textLayout;
    textLayout.loadFont(font, size);
    textLayout.setLineLength(width-margin*2);
    textLayout.setLineSpacing(spacing);
    FTBBox bbox = textLayout.layout->BBox(text.c_str());
    return abs(bbox.Upper().Yf()-bbox.Lower().Yf()) + margin*2;
}

void ofxFTGLSimpleLayout::TextToPixels(ofPixels* pix, string text, string font, int size, float width, float height, float margin, float spacing, ofColor textColor, ofColor backColor, ofxFTGLTextAlignment alignment, bool shapes){
    ofFbo fbo;
    fbo.allocate(width,height,GL_RGBA);
    
    ofxFTGLSimpleLayout textLayout;
    textLayout.loadFont(font, size);
    textLayout.setLineLength(width-margin*2);
    textLayout.setLineSpacing(spacing);
    textLayout.setAlignment(alignment);
    
    fbo.begin();
    ofClear(backColor);
    glBlendFuncSeparate(GL_ONE, GL_SRC_COLOR, GL_ONE, GL_ONE_MINUS_SRC_ALPHA);
    ofSetColor(textColor);
    textLayout.drawString(text,margin,margin+textLayout.getLineHeight());
    fbo.end();
    
    fbo.readToPixels(*pix);
    return;
}
