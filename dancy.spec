#
# This file and all modifications and additions to the pristine
# package are under the same license as the package itself.
#

# norootforbuild

Name:           dancy
Version:	1.0a
Release:
Summary:	An augmented reality based game
Group:
License:
Url:
PreReq:
Provides:
BuildRequires:
Source:
Patch:
BuildRoot:      %{_tmppath}/%{name}-%{version}-build
AutoReqProv:    on

%description

Authors:
--------
    Zhang Wenli
    Hong Yang
    Li Wenhao
    Ye Jiabin 

%prep
%setup

%build
%configure
make %{?jobs:-j%jobs}

%install
%makeinstall

%clean
rm -rf $RPM_BUILD_ROOT

%post
%postun

%files
%defattr(-,root,root)
%doc ChangeLog README COPYING

%changelog
* Mon Aug 22 2011 yejiabin@linux-b668

