#
# This file and all modifications and additions to the pristine
# package are under the same license as the package itself.
#

# norootforbuild

Name:           dancy
Version:	1.0a
Release:	1%{?dist}
Summary:	An augmented reality based game
Group:		Amusements/Games/Other
License:	GPLv2+
Url:		http://pinbob.github.com/Dancy/
PreReq:		gstreamer, gstreamer-devel, freeglut
BuildRoot:      %{_tmppath}/%{name}-%{version}-build
AutoReqProv:    on

%description

Authors:
--------
    Zhang Wenli
    Hong Yang
    Li Wenhao
    Ye Jiabin 

%clean

%post
%postun

%files


