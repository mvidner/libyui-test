#
# spec file for package libyui-test
#
# Copyright (c) 2014 SUSE LINUX Products GmbH, Nuernberg, Germany.
#
# All modifications and additions to the file contributed by third parties
# remain the property of their copyright owners, unless otherwise agreed
# upon. The license for this file, and modifications and additions to the
# file, is the same license as for the pristine package itself (unless the
# license for the pristine package is not an Open Source License, in which
# case the license is the MIT License). An "Open Source License" is a
# license that conforms to the Open Source Definition (Version 1.9)
# published by the Open Source Initiative.

# Please submit bugfixes or comments via http://bugs.opensuse.org/
#


Name:           libyui-test-qt
Version:        1.0.6
Release:        0
Source:         libyui-test-%{version}.tar.bz2

BuildRequires:  gcc-c++
BuildRequires:  libyui-devel
BuildRequires:  libyui-qt
BuildRequires:  make
BuildRequires:  xorg-x11-server

Url:            http://github.com/libyui/
Summary:        GUI-abstraction library
License:        LGPL-2.1 or LGPL-3.0
Group:          System/Libraries

%description
Automatic tests for libyui.

%prep
%setup -q -n libyui-test-%{version}

%build

make check CXXFLAGS="$RPM_OPT_FLAGS" TARGETS=qt

%install

%files
%defattr(-,root,root)
# none

%changelog
