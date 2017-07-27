/*#***************************************************************************
#                         __    __   _____       _____
#   Project              |  |  |  | |     \     /  ___|
#                        |  |__|  | |  |\  \   /  /
#                        |        | |  | )  ) (  (     
#                        |   /\   | |  |/  /   \  \___
#                         \_/  \_/  |_____/     \_____|
#
# Copyright (C) 2016, The WDC Project, <designerror@yandex.ru>, et al.
#
# This software is licensed as described in the file LICENSE, which
# you should have received as part of this distribution. 
#
# You may opt to use, copy, modify, merge, publish, distribute and/or sell
# copies of the Software, and permit persons to whom the Software is
# furnished to do so, under the terms of the LICENSE file.
#
# This software is distributed on an "AS IS" basis, WITHOUT WARRANTY OF ANY
# KIND, either express or implied.
#
############################################################################*/

#ifndef WEBDAV_URN_H
#define WEBDAV_URN_H

#include <iostream>
#include <cstddef>
#include <string>
using std::string;

namespace WebDAV
{
    namespace Urn {

        class Path {

            static const string separate;

            static const string root;

            string m_path;

        public:

            Path(const string& path, bool force_dir = false);

            Path(std::nullptr_t);

            auto path() const -> string;

            auto quote(void * request) const -> string;

            auto name() const -> string;

            auto parent() const -> Path;

            auto is_directory() const -> bool;

            auto is_root() const -> bool;

            auto operator+(const std::string& rhs) const -> Path;

            auto operator==(const Path& rhs) const -> bool;
        };
    }
}

auto operator<<(std::ostream& stream, const WebDAV::Urn::Path& path) -> std::ostream&;

#endif
