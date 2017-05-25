#pragma once
/*!
@file Label.h
\defgroup Label Label
@{
@author arseniy899
\brief Label\n
This is for managing and rendering labels (texts). Labels are always rendered over everything (on the top)
*/
struct LabelS//!< Structure for storing labels (text)
{
   char * text;//!< This is for storing text for current label
   int id/*!< Unique id of label for */, scene;//!< scene id on which this label should be rendered
   float posX, posY;
   int r/*!< Color of text in red*/, g/*!< Color of text in green*/, b/*!< Color of text in blue*/, align/*!< horizontal align of text by allegro's align*/;
};
typedef struct LabelS Label;
/** Being called when rendering labels
*/
void renderLabelsSc();
/** Add new label
   @param x [in] postion by x in px
   @param y [in] postion by y in px
   @param red [in] color of text in red
   @param green [in] color of text in green
   @param blue [in] color of text in blue
   @param scene [in] scene id on which this label should be rendered
   @param align [in] horizontal align of text by allegro's align
   @param text [in] formatted text
   Example Usage:
   @code
         addLabel(1050, 450, 255, 90, 0, LEVEL_SCENE_PAUSE, ALLEGRO_ALIGN_CENTER, "LEFT:%i",50);
   @endcode
   @return label's id
*/
int addLabel(float x, float y, int red, int green, int blue, int scene, int align, const char *text, ...);
/** Converts char data from source to destination with memory allocation for new one (copying).
   @param labelId [in] unique id of label
   @param text [in] formatted text to be set
   Example Usage:
   @code
      changeText(countLId, "Now:%s-%i","left",50);
   @endcode
   @return 0 if label exists, -1 if not
*/
int changeText(int labelId, const char *text, ...);
/** Get label by it's id
   @param i id of labels
   @return pointer to label if label exists, null if not
   
*/
Label *getStructLabel(int i);
/** Being called when screen was resized
   @param hC [in] coefficient of resizing in horizontal
   @param vC [in] coefficient of resizing in vertical
   
*/
void recalcLabels(float hC, float vC);

/** Clearing labels for selected scenes to free memory
   @param scene scene id
*/
void clearLabels(int scene);
/**
@}
*/
