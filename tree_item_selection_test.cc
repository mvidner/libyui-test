/*
  Copyright (C) 2016 SUSE LLC
  This library is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as
  published by the Free Software Foundation; either version 2.1 of the
  License, or (at your option) version 3.0 of the License. This library
  is distributed in the hope that it will be useful, but WITHOUT ANY
  WARRANTY; without even the implied warranty of MERCHANTABILITY or
  FITNESS FOR A PARTICULAR PURPOSE. See the GNU Lesser General Public
  License for more details. You should have received a copy of the GNU
  Lesser General Public License along with this library; if not, write
  to the Free Software Foundation, Inc., 51 Franklin Street, Fifth
  Floor, Boston, MA 02110-1301 USA
*/

#include <string>
#include <iostream>
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

// test for issue https://github.com/libyui/libyui/issues/86

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


  YUI::widgetFactory()->createPushButton( vbox, "&OK" );

  std::ostringstream res;
  for (YItem *i : tree->selectedItems())
    res << i->label() << ",";

  dialog->destroy();

  std::string expected = "Dylan,";
  if (res.str() != expected)
  {
    std::cerr << "Expected: " << expected << " Get: " << res.str() << std::endl; 
    return 1;
  }

  return 0;
}
