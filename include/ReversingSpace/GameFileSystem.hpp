/*
 * Copyright 2017-2018 ReversingSpace. See the COPYRIGHT file at the
 * top-level directory of this distribution and in the repository:
 * https://github.com/ReversingSpace/cpp-gamefilesystem
 *
 * Licensed under the Apache License, Version 2.0 <LICENSE-APACHE or
 * http://www.apache.org/licenses/LICENSE-2.0> or the MIT license
 * <LICENSE-MIT or http://opensource.org/licenses/MIT>, at your
 * option. This file may not be copied, modified, or distributed
 * except according to those terms.
**/

#ifndef REVERSINGSPACE_GAMEFILESYSTEM_HPP
#define REVERSINGSPACE_GAMEFILESYSTEM_HPP

// This is incomplete as it only provides storage access code.

// Storage (underlying code for access)
#include <ReversingSpace/Storage/File.hpp>

// GameFileSystem: actual abstraction layer that should
// generally be the use-case.
#include <ReversingSpace/GameFileSystem/StorageServer.hpp>
#include <ReversingSpace/GameFileSystem/Directory.hpp>

#endif//REVERSINGSPACE_GAMEFILESYSTEM_HPP