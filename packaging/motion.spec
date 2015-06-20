Name:       motion
Summary:    Tizen Native Motion Recognition API
Version:    1.1.3
Release:    1
Group:      Framework/context
License:    Apache-2.0
Source0:    %{name}-%{version}.tar.gz
BuildRequires:  cmake
BuildRequires:  pkgconfig(capi-base-common)
BuildRequires:  pkgconfig(dlog)
BuildRequires:  pkgconfig(glib-2.0)
BuildRequires:  pkgconfig(capi-system-info)
BuildRequires:  pkgconfig(sensor)
Requires(post):  /sbin/ldconfig
Requires(postun):  /sbin/ldconfig

%ifarch %{arm}
%define ARCH arm
%else
%define ARCH i586
%endif

%description
Tizen Native Motion Recognition API

%prep
%setup -q

%build
MAJORVER=`echo %{version} | awk 'BEGIN {FS="."}{print $1}'`

export   CFLAGS+=" -Werror -Wextra -Wcast-align -Wcast-qual -Wshadow -Wwrite-strings -Wswitch-default"
export CXXFLAGS+=" -Werror -Wextra -Wcast-align -Wcast-qual -Wshadow -Wwrite-strings -Wswitch-default -Wnon-virtual-dtor -Wno-c++0x-compat"

#export  CFLAGS+=" -Wno-array-bounds -Wno-ignored-qualifiers"
export   CFLAGS+=" -Wno-unused-parameter -Wno-empty-body"
export CXXFLAGS+=" -Wno-unused-parameter -Wno-empty-body"

export   CFLAGS+=" -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-strict-aliasing -fno-unroll-loops -fsigned-char -fstrict-overflow -fno-common"
export CXXFLAGS+=" -fno-omit-frame-pointer -fno-optimize-sibling-calls -fno-strict-aliasing -fno-unroll-loops -fsigned-char -fstrict-overflow"

export CFLAGS="$CFLAGS -DTIZEN_ENGINEER_MODE"
export CXXFLAGS="$CXXFLAGS -DTIZEN_ENGINEER_MODE"
export FFLAGS="$FFLAGS -DTIZEN_ENGINEER_MODE"

cmake . -DCMAKE_INSTALL_PREFIX=%{_prefix} -DARCH=%{ARCH} -DMAJORVER=${MAJORVER} -DFULLVER=%{version} -DPROFILE=%{PROFILE}
make %{?jobs:-j%jobs}

%install
rm -rf %{buildroot}
%make_install

mkdir -p %{buildroot}/usr/share/license
cp LICENSE %{buildroot}/usr/share/license/%{name}
# For backward compatibility
ln -s ./%{name}.pc %{buildroot}/%{_libdir}/pkgconfig/libcore-context-manager.pc

%post
/sbin/ldconfig

%postun
/sbin/ldconfig

%files
%manifest packaging/%{name}.manifest
%defattr(-,root,root,-)
%{_libdir}/*.so*
/usr/share/license/%{name}

%package devel
Summary:	Tizen Native Motion Recognition API (Development)
Group:		Framework/context
Requires:	%{name} = %{version}-%{release}

%description devel
Tizen Native Motion Recognition API (Development)

%post devel
/sbin/ldconfig

%postun devel
/sbin/ldconfig

%files devel
%defattr(-,root,root,-)
%{_includedir}/*/*.h
%{_libdir}/pkgconfig/*.pc
