
#include <YUI.h>
#include <YDialog.h>
#include <YWidgetFactory.h>

int main( int argc, char **argv )
{
    // Initialize the UI
    YWidgetFactory * wf = YUI::widgetFactory();

    YDialog * d1 = wf->createPopupDialog();
    d1->destroy();
    return 0;
}
