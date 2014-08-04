Automatic tests for [libyui](https://github.com/libyui/libyui).

This repo combines tests for all 3 backends.

Requirements
------------

The requirements depend on what backends you want tested:

    sudo zypper install gcc-c++ make libyui-devel           # 1
    sudo zypper install libyui-gtk libyui-ncurses libyui-qt # 2
    sudo zypper install screen expect                       # 3
    sudo zypper install xorg-x11-server                     # 4

1. In any case
2. Pick any or all
3. For ncurses
4. For GTK or Qt

Usage
-----

This runs the tests using your installed packages:

    make
    make check

For continuous integration at <https://ci.opensuse.org> we use a Rakefile
that runs the above with the newest packages. For example the job
[libyui-test-qt-master](https://ci.opensuse.org/job/libyui-test-qt-master/)
uses:

    export LANG=en_US.UTF-8
    rake osc:build[libyui-test-qt.spec]

Design
------

There are 3 RPM spec files package/*.spec (
[gtk](package/libyui-test-gtk.spec)
[ncurses](package/libyui-test-ncurses.spec)
[qt](package/libyui-test-qt.spec)).
