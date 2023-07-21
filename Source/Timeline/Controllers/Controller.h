#include "../Objects/ObjectIncludes.h"
#include "../Views/ViewIncludes.h"

namespace Timeline
{

class Controller
{
public:

// this will be called from a view which will get a reference to the controller?
// call it like mController.setSelected(this);
void setSelected(Timeline::ObjectView* selectedView)
{
    mObjectViewMap[selectedView].setSelected();
}

private:
    std::map<ObjectView, Timeline::Object> mObjectViewMap;
};





}