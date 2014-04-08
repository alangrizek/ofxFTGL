#pragma once

#include "ofMain.h"
#include "ftgl.h"
#include "ofxFTGLFont.h"

typedef	FTGL::TextAlignment ofxFTGLTextAlignment;

#define FTGL_ALIGN_LEFT     FTGL::ALIGN_LEFT
#define FTGL_ALIGN_CENTER   FTGL::ALIGN_CENTER
#define FTGL_ALIGN_RIGHT    FTGL::ALIGN_RIGHT
#define FTGL_ALIGN_JUSTIFY  FTGL::ALIGN_JUSTIFY

class ofxFTGLSimpleLayout
: public ofxFTGLFont
{
    public:
        ofxFTGLSimpleLayout();
        ~ofxFTGLSimpleLayout();

        void unload();
        bool loadFont(string filename, float fontsize = 10, float depth = 0, bool bUsePolygons = false);

        ofRectangle getStringBoundingBox(wstring s, float x, float y);
        ofRectangle getStringBoundingBox(string s, float x, float y);
    
        void drawString(wstring s, float x, float y);
        void drawString(string s, float x, float y);

        float       getLineLength() const;
        void        setLineLength(float length);
        float       getLineSpacing() const;
        void		setLineSpacing(float spacing);

        ofxFTGLTextAlignment getAlignment() const;
        void setAlignment(ofxFTGLTextAlignment alignment);
    
    static void TextToPixels(ofPixels* pix, string text, string font, int size, float width, float height, float margin=20, float spacing=0.85f, ofColor textColor=ofColor(255,255), ofColor backColor=ofColor(0,0), ofxFTGLTextAlignment alignment=FTGL_ALIGN_JUSTIFY, bool shapes=false);
    static float GetTextToPixelsHeight(string text, string font, int size, float width, float margin=20, float spacing=0.85f);

        FTSimpleLayout* layout;
};

