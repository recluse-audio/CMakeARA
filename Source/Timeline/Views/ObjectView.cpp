
#include "ObjectView.h"

using namespace Timeline;

ObjectView::ObjectView(Timeline::ZoomState& zoomState)
: Timeline::ZoomStateListener(zoomState)
{
}

ObjectView::~ObjectView()
{
	
}

void ObjectView::updateZoomState(ZoomState *zoomState)
{
	_updateSize();
	_positionChildren();
}


//===============
void ObjectView::refresh()
{
	_updateSize();
	_createChildren();
	_positionChildren();
}
