/*
  Copyright (C) 2014 SUSE LLC
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
#include <fstream>

#include <YUI.h>
#include <YUILoader.h>
#include <YDialog.h>
#include <YEvent.h>
#include <YInputField.h>
#include <YLayoutBox.h>
#include <YPushButton.h>
#include <YWidgetFactory.h>

int main( int argc, char **argv )
{
    // Initialize the UI
    YWidgetFactory * wf = YUI::widgetFactory();

    YDialog * d = wf->createPopupDialog();
    YLayoutBox * vbox = wf->createVBox(d);
    YInputField * i = wf->createInputField(vbox, "Label");
    YPushButton * b = wf->createPushButton(vbox, "&OK");

    while (true)
    {
	YEvent * event = d->waitForEvent();

	if (! event)
	    continue;

	if (event->widget() == b)
	    break;
    }
    std::string v = i->value();
    d->destroy();
    //    YUILoader::deleteUI();
    //delete YUI::ui();

    std::ofstream out("output.txt");
    out << v << std::endl;

    return 0;
}
