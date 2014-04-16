
#include <YUI.h>
#include <YWidgetFactory.h>

int main( int argc, char **argv )
{
    // Initialize the UI
    YWidgetFactory * wf = YUI::widgetFactory();
    // Open two dialogs but don't close them.
    // A global cleanup routine should handle the closing, without crashing.
    /* YDialog * d1 = */ wf->createPopupDialog();
    /* YDialog * d2 = */ wf->createPopupDialog();
    return 0;
}
