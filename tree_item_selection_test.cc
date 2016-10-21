#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

#include <yui/YUI.h>
#include <yui/YApplication.h>
#include <yui/YWidgetFactory.h>
#include <yui/YDialog.h>
#include <yui/YLayoutBox.h>
#include <yui/YAlignment.h>
#include <yui/YTree.h>
#include <yui/YPushButton.h>
#include <yui/YEvent.h>


int main( int argc, char **argv )
{
  YDialog    * dialog = YUI::widgetFactory()->createMainDialog();
  YLayoutBox * vbox   = YUI::widgetFactory()->createVBox( dialog );
  YTree* tree   = YUI::widgetFactory()->createTree( vbox, "Select:" );
  tree->setNotify( true );
  {
    YItemCollection items;
    YTreeItem *t = new YTreeItem( "Alice" );
    items.push_back( t );
    items.push_back( (t = new YTreeItem( "Other" )) );
    new YTreeItem( t, "Other 1" );
    t = new YTreeItem( t, "Other 2" );
    new YTreeItem( t, "Other 21" );
    items.push_back( (t = new YTreeItem( "Bob" )) );
    new YTreeItem( t, "Item 1" );
    new YTreeItem( t, "Item 2" );
    new YTreeItem( t, "Item 3" );
    t = new YTreeItem( t, "Dylan" );
    // comment next line to see that item2 is selected
    t->setSelected(true); // selected item
    tree->addItems( items ); // This is more efficient than repeatedly calling cbox->addItem
  }


  YPushButton* quitButton = YUI::widgetFactory()->createPushButton( vbox, "&OK" );
  while ( true )
  {
    YEvent * event = dialog->waitForEvent();
    if ( event )
    {
      // window manager "close window" button
      if ( event->eventType() == YEvent::CancelEvent || event->widget() == quitButton )
      break; // leave event loop
    }
  }

  std::ostringstream res;
  for (YItem *i : tree->selectedItems())
    res << i->label() << ",";

  dialog->destroy();

  std::ofstream out("output.txt");
  out << res.str() << std::endl;

  return 0;
}
