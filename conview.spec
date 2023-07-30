Name:           conview
Version:        0.0.1
Release:        1%{?dist}
Summary:        A command-line tool to download B-Consortium projects
Group:          Development/Tools
License:        B-License
URL:            https://github.com/B-Consortium/conview
Source0: 	https://github.com/B-Consortium/conview/archive/v%{version}.tar.gz
BuildRoot:      %(mktemp -ud %{_tmppath}/%{name}-%{version}-%{release}-XXXXXX)

%description
This command-line tool is used to show running tasks in command line

%prep
%setup -q -n %{name}-%{version}

%build
make conview

%install
install -d m0755 %{buildroot}%{_bindir}
make install prefix=%{buildroot}/usr

%clean
rm -rf %{buildroot}

%files
%defattr(-,root,root,-)
%{_bindir}/conview
%{_mandir}/man6/conview.6%{ext_man}
