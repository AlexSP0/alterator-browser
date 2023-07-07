Name: altcenter
Version: 1.0
Release: alt1

Summary: Revised alterator
License: GPLv2+
Group: Other
URL: https://github.com/uyraq2001/alterator-module-browser

BuildRequires(pre): rpm-macros-cmake
BuildRequires: cmake
#BuildRequires: cmake-modules
BuildRequires: gcc-c++
BuildRequires: qt5-base-devel
#BuildRequires: qt5-declarative-devel
BuildRequires: qt5-tools-devel
BuildRequires: qt5-base-common
BuildRequires: boost-devel-headers
#BuildRequires: doxygen

Source0: %name-%version.tar

%description
Alterator operating via D-Bus.

%prep
%setup

%build
%cmake
%cmake_build

%install
%cmakeinstall_std
#mkdir -p %buildroot%_alterator_datadir/backends/
#mkdir -p %buildroot%_alterator_datadir/module-info/
#mkdir -p %buildroot%_alterator_datadir/desktop-directories/
#cp backends/*.backend %buildroot%_alterator_datadir/backends/
#cp backends/script.sh %buildroot%_alterator_datadir/backends/
#cp module-info/* %buildroot%_alterator_datadir/module-info/
#cp /usr/share/alterator/desktop-directories/* %buildroot%_alterator_datadir/desktop-directories/

%files
%_bindir/altcenter
%_alterator_datadir/backends/*.backend
%_alterator_datadir/backends/script.sh
%_alterator_datadir/module-info/*
%_alterator_datadir/desktop-directories/*
%doc README.md INSTALL.md

%changelog
* Wed Jul 5 2023 Kozyrev Yuri <kozyrevid@altlinux.org> 1.0-alt1
- initial build
